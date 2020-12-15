#include "threadsort.hpp"

#include <cstddef>
#include <sstream>
#include <string>
#include <vector>
#include <thread>
#include <mutex>
#include <fstream>
#include <algorithm>
#include <functional>
#include <queue>
#include <iostream>



void merge_files(std::vector<std::string> &fnames, std::string &res_fname)
{
    if (fnames.size() < 1) {
        std::cout << "error((" << std::endl;
        return;
    }
    using val_fn = std::pair<uint64_t, size_t>;
    std::priority_queue<val_fn, std::vector<val_fn>, std::greater<val_fn>> sort_conv;
    std::ofstream result(res_fname, std::ios::binary/* | std::ios::out*/);
    std::vector<std::ifstream> files;
    files.reserve(fnames.size());
    for (size_t fn = 0; fn < fnames.size(); ++fn) {
        files.emplace_back(fnames[fn], std::ios::binary/* | std::ios::in*/);
        uint64_t val;
        if (files[fn].read((char *)&val, sizeof(val))) {
            sort_conv.push(std::make_pair(val, fn));
        }
    }
    
    while(!sort_conv.empty()) {
        uint64_t val;
        size_t fn;
        std::tie(val, fn) = sort_conv.top();
        sort_conv.pop();
        std::cout << "Write to " << res_fname << ": " << val << std::endl;
        result.write((char *)&val, sizeof(val));
        if (files[fn].read((char *)&val, sizeof(val))) {
            sort_conv.push(val_fn(val, fn));
        } else {
            files[fn].close();
        }
    }
    result.close();
}


void threadsort_worker(std::string &&thr_name, std::ifstream &file, 
                       std::mutex &read_mutex)
{
    {
        std::lock_guard<std::mutex> lock(read_mutex);
        std::cout << thr_name << " just started " << std::endl;
    }
    constexpr size_t CHUNK_CNT = CHUNK_SIZE / sizeof(uint64_t);
    constexpr size_t BUF_SIZE = CHUNK_SIZE * MAX_CHUNKS;
    constexpr size_t BUF_CNT = CHUNK_CNT * MAX_CHUNKS;
    
    uint64_t *buf = new uint64_t[BUF_CNT];
    bool should_read{true};
    size_t part_cnt{0};
    std::vector<std::string> tmp_fnames;
    {
        std::lock_guard<std::mutex> lock(read_mutex);
        std::cout << thr_name << " started " << std::endl;
    }
    while(should_read) {
        for (size_t ch_num = 0; ch_num < MAX_CHUNKS; ++ch_num) {
            std::lock_guard<std::mutex> lock(read_mutex);
            if (file.is_open()) {
                if (!file.read((char *)(buf) + ch_num * CHUNK_SIZE, CHUNK_SIZE)) {
                    file.close();
                }
                std::cout << thr_name << " read " << ch_num << std::endl;
            } else {
                should_read = false;
                break;
            }
        }
        
        std::sort(buf, buf + BUF_CNT);
        for (size_t i = 0; i < BUF_CNT; ++i) {
            std::cout << "SORTED: " << buf[i] << std::endl;
        }
        std::stringstream tmp_name;
        tmp_name << thr_name << "_p" << part_cnt++ << ".bin";
        std::ofstream sorted_part(tmp_name.str(), /*std::ios::out | */std::ios::binary);
        sorted_part.write((char *)(buf), BUF_SIZE);
        sorted_part.close();
        tmp_fnames.push_back(tmp_name.str());
    }
    delete[] buf;
    std::string thr_res_fname = thr_name + "_res.bin";
    merge_files(tmp_fnames, thr_res_fname);
}

std::string threadsort(const char *filename, size_t n_threads = 2)
{
    std::mutex read_mutex;
    
    std::ifstream file(filename,/* std::ios::in | */std::ios::binary);
    
    std::vector<std::thread> workers(n_threads);
    std::vector<std::string> threads_res_fnames;
    std::cout << "work start" << std::endl;
    /*
    for (size_t thr_id = 0; thr_id < n_threads; ++thr_id) {
        std::stringstream s_thr_name;
        s_thr_name << "t" << thr_id;
        std::string thr_name = s_thr_name.str();
        threads_res_fnames.push_back(thr_name);
        workers.emplace_back(threadsort_worker, std::move(thr_name),
                             std::ref(file), std::ref(read_mutex));
        {
            std::lock_guard<std::mutex> lock(read_mutex);
            std::cout << thr_name << " is set" << std::endl;
        }
    }
    
    for (auto &w : workers) {
        w.join();
    }*/
    size_t thr_id = 0;
    std::stringstream s_thr_name;
    s_thr_name << "t" << thr_id;
    std::string thr_name = s_thr_name.str();
    threads_res_fnames.push_back(thr_name);
    threadsort_worker(std::move(thr_name), std::ref(file), std::ref(read_mutex));
    file.close();
    std::cout << "workers done" << std::endl;
    std::string res_filename = std::string(filename) + "_res.bin";
    merge_files(threads_res_fnames, res_filename);
        std::cout << 'Q' + res_filename << std::endl;
    return res_filename;
}

int main()
{
    std::string filename = "check.bin";
    std::ofstream file("check.bin", std::ios::binary /*| std::ios::out*/);
    for (uint64_t i = 32; i > 0; --i) {
        file.write((char *)&i, sizeof(i));
    }
    file.close();

    threadsort("check.bin", 1);
    
    std::ifstream file2("check.bin_res.bin", std::ios::binary/* | std::ios::in*/);
    for (uint64_t i = 32; i > 0; --i) {
        uint64_t tmp;
        file2.read((char *)&tmp, sizeof(tmp));
        std::cout << tmp << "  ";
    }
    std::cout << std::endl;
    return 0;
}

