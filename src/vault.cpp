//
// Created by nikola on 1/20/23.
//

#include <fstream>
#include <iostream>
#include <random>
#include "vault.h"
#include  "openssl.h"

std::filesystem::path
Vault::locate_directory(const std::filesystem::path &target_dir, const std::filesystem::path &start_dir) {
    std::filesystem::path absolute_start = std::filesystem::absolute(start_dir);
    while (!absolute_start.empty() && (absolute_start.parent_path() != absolute_start.root_directory())) {
        auto ret = absolute_start / target_dir;
        if (std::filesystem::is_directory(ret)) {
            return ret;
        }
        absolute_start = absolute_start.parent_path();
    }
    return {};
}

bool Vault::upload_file(const std::filesystem::path file_path) {
    std::fstream file_reader{file_path, std::fstream::in};
    if (!file_reader.is_open()) {
        std::cerr << "Temp file couldn't be opened\n";
    } else {
        /// get file name
        std::string file_name = file_path.stem();

        /// get file contents to string
        std::stringstream temp_stream ;
        temp_stream << file_reader.rdbuf();
        std::string buffer =  temp_stream.str();
        std::size_t  pos = 0;

        std::size_t file_size = buffer.size();
        std::size_t segment_count = get_random_in_range(4, file_size);
        std::size_t segment_size = file_size / segment_count + (file_size % segment_count != 0);
        ///Split file into segments
        for (size_t i = 0; i < segment_count ; ++i) {
            std::string segment_name = openssl.hash_string(file_name+ std::to_string(i));
            std::filesystem::path dest_dir = vault_path.concat(std::to_string(i));
            if (!is_directory(dest_dir)) {
                std::filesystem::create_directory(dest_dir);
            }
            std::ofstream segment{dest_dir.concat(segment_name)};
            if(!segment.is_open()){
                std::cerr << "Segment couldn't be generated\n";
            }else{
                    segment << buffer.substr(pos, segment_size);
                    // TODO encrypt and sign segment
                    pos += segment_size;
            }
        }
    }
}



std::size_t Vault::get_random_in_range(std::size_t min, std::size_t max) {
    static std::default_random_engine eng(std::random_device{}());
    std::uniform_int_distribution<std::size_t> dist(min, max);
    return dist(eng);
}



