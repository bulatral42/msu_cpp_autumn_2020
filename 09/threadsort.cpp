#include "threadsort.hpp"


void merge_files(const std::vector<std::string> &fnames, 
                 const std::string &res_fname)
{
    using val_fn = std::pair<uint64_t, size_t>;
    std::priority_queue<val_fn, std::vector<val_fn>, 
                        std::greater<val_fn>> sort_conv;
    std::ofstream result(res_fname, std::ios::binary);
    std::vector<std::ifstream> files;
    files.reserve(fnames.size());
    for (size_t fn = 0; fn < fnames.size(); ++fn) {
        files.emplace_back(fnames[fn], std::ios::binary);
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
        result.write((char *)&val, sizeof(val));
        if (files[fn].read((char *)&val, sizeof(val))) {
            sort_conv.push(val_fn(val, fn));
        } else {
            files[fn].close();
        }
    }
    result.close();
}


void threadsort_worker(std::string thr_name, std::ifstream &file, 
                       std::mutex &read_mutex)
{
    uint64_t *buf = new uint64_t[BUF_CNT];
    bool should_read{true};
    size_t part_cnt{0}, red_cnt{0}, red_size{0};
    std::vector<std::string> tmp_fnames;
    while(should_read) {
        for (size_t ch_num = red_size = 0; ch_num < MAX_CHUNKS; ++ch_num) {
            std::lock_guard<std::mutex> lock(read_mutex);
            if (file.is_open()) {
                file.read((char *)buf + ch_num * CHUNK_SIZE, CHUNK_SIZE);
                if (file.gcount() == 0) {    
                    file.close();
                    should_read = false;
                    break;
                } else {
                    red_size += file.gcount();
                }
            } else {
                should_read = false;
                break;
            }
        }
        red_cnt = red_size / sizeof(uint64_t);
        if (red_cnt == 0) {
            break;
        }
        std::sort(buf, buf + red_cnt);

        std::stringstream tmp_name;
        tmp_name << thr_name << "_p" << part_cnt++ << ".bin";
        std::ofstream sorted_part(tmp_name.str(), std::ios::binary);
        sorted_part.write((char *)(buf), red_size);
        sorted_part.close();
        tmp_fnames.push_back(tmp_name.str());
    }
    delete[] buf;
    std::string thr_res_fname = thr_name + "_res.bin";
    merge_files(tmp_fnames, thr_res_fname);
    for (const auto &fname : tmp_fnames) {
        remove(fname.c_str());
    }
}


std::string threadsort(const char *filename, size_t n_threads = 2)
{
    std::mutex read_mutex;
    
    std::ifstream file(filename, std::ios::binary);
    
    std::vector<std::thread> workers(n_threads);
    std::vector<std::string> threads_res_fnames;

    for (size_t thr_id = 0; thr_id < n_threads; ++thr_id) {
        std::stringstream s_thr_name;
        s_thr_name << "t" << thr_id;
        std::string thr_name = s_thr_name.str();
        threads_res_fnames.push_back(thr_name + "_res.bin");
        workers.emplace_back(threadsort_worker, thr_name,
                             std::ref(file), std::ref(read_mutex));
    }
    for (size_t i = 0; i < workers.size(); ++i) {
        if (workers[i].joinable()) {
            workers[i].join();
        }
    }
    file.close();
    std::string res_filename = std::string(filename) + "_res.bin";
    merge_files(threads_res_fnames, res_filename);
    for (const auto &fname : threads_res_fnames) {
        remove(fname.c_str());
    }
    return res_filename;
}

