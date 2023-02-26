//
// Created by nikola on 1/18/23.
//

#include <fstream>
#include "user.h"
#include <iostream>
#include <utility>

User::User(std::string username, std::string name, std::string surname,
           std::string password, std::string email, std::string country,
           std::string province) : username(std::move(username)), name(std::move(name)), surname(std::move(surname)), password(std::move(password)),
                                          email(std::move(email)), country(std::move(country)), province(std::move(province)) {}

void User::generate_config_file(const std::filesystem::path &dest) {
    std::fstream out{dest, std::fstream::out};
    if (!out.is_open()) {
        std::cerr << "File " << dest << " couldn't be opened\n";
    } else {
        out << this;
    }
}

void User::read_config_file(const std::filesystem::path &conf_file_path) {
    std::fstream in{conf_file_path, std::fstream::in};
    if (!in.is_open()) {
        std::cerr << "Config file " << conf_file_path << " couldn't be opened\n";
    } else {
        std::getline(in, username);
        std::getline(in, password);
        std::getline(in, name);
        std::getline(in, surname);
        std::getline(in, email);
        std::getline(in, country);
        std::getline(in, province);
        std::string temp{};
        //read map
        while (std::getline(in, temp)) {
            std::string file_name = temp.substr(0, temp.find('|'));
            std::string paths = temp.substr(temp.find('|') + 1, temp.size());
            std::vector<std::filesystem::path> path_vector{};
            std::size_t pos{};
            while ((pos = paths.find(',')) != std::string::npos) {
                path_vector.emplace_back(paths.substr(0, pos));
                paths.erase(0, pos + 1);
            }
            file_index.emplace(file_name, path_vector);
        }
    }

}

std::ostream &User::operator<<(std::ostream &os) {
    os << username << '\n';
    os << openssl.hash_string(password) << '\n';
    os << name << '\n' << surname << '\n' << email << '\n' << country << '\n' << province << '\n';
    for (auto const &[key, value]: file_index) {
        os << key << '|';
        for (auto const &path: value) {
            os << path << ',';
        }
        os << '\n';
    }
    return os;
}

bool User::validate_credentials(const std::string &username, const std::string &password) {
    return (this->username == username && openssl.hash_string(password) == this->password);
}

void User::add_file(const std::string &filename, const std::vector<std::filesystem::path> &pahts) {
    file_index.emplace(filename, pahts);
    generate_config_file(config_file);
}

void User::delete_file(const std::string &filename) {
    file_index.erase(file_index.find(filename));
    generate_config_file(config_file);
}

std::vector<std::string> User::list_files() const {
    std::vector<std::string> ret{};
    for(auto  [key, value] : file_index){
        ret.push_back(key);
    }
    return ret;
}
