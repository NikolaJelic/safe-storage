//
// Created by nikola on 1/20/23.
//

#include "vault.h"

std::filesystem::path Vault::locate_directory(const std::filesystem::path &target_dir, const std::filesystem::path &start_dir){
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

