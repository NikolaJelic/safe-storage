//
// Created by nikola on 1/18/23.
//

#pragma once

#include <string>
#include <filesystem>
#include "user.h"

class Openssl {
    std::filesystem::path vault_dir{};

public:
    Openssl(std::filesystem::path const &vault_dir): vault_dir(vault_dir) {}


    /// get hash of a string using the default algorithm
    std::string hash_string(std::string const &text);



    std::filesystem::path generate_certificate(User const &user, std::filesystem::path const &target_dir);

private:
    std::string return_output(std::string input) const;
};