cmake_minimum_required(VERSION 3.27)
project(COMP2034CW_C__)

set(CMAKE_CXX_STANDARD 14)

add_executable(COMP2034CW_C__ src/main.cpp
        src/Block.cpp
        headers/Block.h
        src/Information.cpp
        headers/Information.h
        src/BlockChain.cpp
        headers/BlockChain.h
        library/sha256.cpp
        library/sha256.h
        src/Order.cpp
        headers/Order.h
        src/Request.cpp
        headers/Request.h
        src/Transport.cpp
        headers/Transport.h
        src/Receive.cpp
        headers/Receive.h
        src/Sale.cpp
        headers/Sale.h)


