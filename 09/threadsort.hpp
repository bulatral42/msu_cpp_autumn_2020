#pragma once

#include <cstdint>
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



constexpr size_t MAX_CHUNKS = 512;
constexpr size_t CHUNK_CNT = 128;

constexpr size_t CHUNK_SIZE = CHUNK_CNT * sizeof(uint64_t);

constexpr size_t BUF_SIZE = CHUNK_SIZE * MAX_CHUNKS;
constexpr size_t BUF_CNT = CHUNK_CNT * MAX_CHUNKS;


void merge_files(const std::vector<std::string> &fnames, 
                 const std::string &res_fname);
void threadsort_worker(std::string thr_name, std::ifstream &file,
                       std::mutex &read_mutex);
std::string threadsort(const char *filename, size_t n_threads);
