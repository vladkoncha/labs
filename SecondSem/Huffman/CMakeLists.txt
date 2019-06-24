cmake_minimum_required(VERSION 3.14)
project(Huffman C)

set(CMAKE_C_STANDARD 99)

add_executable(Huffman main.c Encode.c Encode.h Convert.c Convert.h Decode.c Decode.h)