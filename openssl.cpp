//
// Created by nikola on 1/18/23.
//

#include <fstream>
#include "openssl.h"
#include <iostream>


std::string Openssl::hash_string(const std::string &text) {
    std::string command = "openssl passwd " + text + " > temp.txt";
    std::system(command.c_str());
    return return_output("temp.txt");
}


std::string Openssl::return_output(std::string input) const {
    std::string ret{};
    std::fstream reader{input, std::fstream::in};
    if(!reader.is_open()){
        std::cerr << "Temp file couldn't be opened\n";
    }else{
        std::stringstream  temp;
        temp << reader.rdbuf();
        ret = temp.str();
    }
    std::remove(input.c_str());
    return  ret;
}
