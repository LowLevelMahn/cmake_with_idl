cmake_minimum_required (VERSION 3.14)

project (idl_user1)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_executable(idl_user1 "main.cpp")

# we need the generator
add_dependencies(idl_user1 "generator")

# custom target/command
# generator ../idls/A.idl .
