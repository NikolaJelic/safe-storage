//
// Created by nikola on 1/18/23.
//
#pragma once

#include <string>
#include <filesystem>
#include <vector>
#include <map>
#include "openssl.h"

class User{
public:
    User() = default;
    User(std::string username, std::string name, std::string surname, std::string password,
         std::string email, std::string country, std::string province);


    ///generate config file with user data and metadata in given destination
    void generate_config_file(std::filesystem::path const& dest);
    ///read config file and store it in the User object
    void read_config_file(std::filesystem::path const& conf_file_path);

    ///return list of all stored files
    [[nodiscard]] std::vector<std::string> list_files() const;
    ///delete file from user
    void delete_file(std::string const& filename);

    /// Add file data to the user config file
    void add_file(std::string const& filename, std::vector<std::filesystem::path> const& pahts);

    std::ostream& operator<<(std::ostream& os);

    bool validate_credentials(std::string const& username, std::string const& password);

	std::vector<std::filesystem::path> get_file_segments(const std::string& filename)const;
private:
    std::map<std::string, std::vector<std::filesystem::path>> file_index{};
    std::filesystem::path config_file{};
    std::filesystem::path vault_path{};

    Openssl openssl{config_file.parent_path()};
    std::string username{};
    std::string name{};
    std::string surname{};
    std::string password{};
    std::string email{};
    std::string country{};
    std::string province{};

};

