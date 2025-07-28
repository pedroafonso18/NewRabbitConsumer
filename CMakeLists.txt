cmake_minimum_required(VERSION 3.31)
project(ConsumirRabbitCpp)

set(CMAKE_CXX_STANDARD 17)

add_executable(ConsumirRabbitCpp src/main.cpp
        include/Config.h
        lib/dotenv.h)
