cmake_minimum_required(VERSION 3.24)
project(safe_storage)

set(CMAKE_CXX_STANDARD 23)

add_executable(safe_storage src/main.cpp src/user.cpp src/user.h src/openssl.cpp src/openssl.h src/vault.cpp src/vault.h)
