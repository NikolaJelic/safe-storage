//
// Created by nikola on 1/20/23.
//

#pragma once

#include <filesystem>
#include <vector>
#include "user.h"
#include "openssl.h"

class Vault {
    ///path to the vault directory
    std::filesystem::path vault_path{};
    /// path to the directory with the CA, CRL and other sensitive info
    std::filesystem::path config_path{};
    ///path to the CA certificate
    std::filesystem::path ca_cert{};
    ///Path to the user directory with all the user details
    std::filesystem::path usr_dir{};
    Openssl openssl;
    User current_user;

     const size_t min_directory_count = 4;
     const size_t max_directory_count = 200;

public:
    ///locates the vault location using the name of the vault directory so that it can be ran from anywhere
    std::filesystem::path
    locate_directory(const std::filesystem::path &target_dir, std::filesystem::path const &start_dir);

    ///when passed a User object, generate the proper folders, config file and certificate
    User setup_new_user(User const &user);

    ///load user certificate and check if it is among the approved ones
    bool check_user_cert(std::filesystem::path const &usr_cert) const;

    /// if cert is valid, check if the username and password are also valid in the user config files and init the User if they are
    ///, init current_user
    bool check_user_data(std::string const &username, std::string const &password) const;

    ///user login, first enter certificate, then user credentials
    User login() const;

    /// get the file with the given filename, reconstruct and copy it and return the path to the generated copy
    std::filesystem::path get_file(std::string const &filename);

    /// upload file to vault
    bool upload_file(std::filesystem::path const& file_path);

    ///delete file from vault and config files
    void delete_file(std::string const &filename);


private:
    ///fragment files and store the fragment paths in a vector
    std::vector<std::filesystem::path> fragment_file(std::fstream const &file);

    ///collect fragments into a vector
    std::vector<std::filesystem::path> collect_fragments(std::string const &filename);

    /// encrypt fragment
    //fragment will need to be stored in a temp file before encryption and then deleted after it is finished
    std::fstream encrypt_fragment();


    std::size_t get_random_in_range(std::size_t min, std::size_t max);

};