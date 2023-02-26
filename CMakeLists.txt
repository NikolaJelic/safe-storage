cmake_minimum_required(VERSION 3.24)
project(safe_storage)

set(CMAKE_CXX_STANDARD 23)

add_executable(safe_storage main.cpp user.cpp user.h openssl.cpp openssl.h vault.cpp vault.h)
