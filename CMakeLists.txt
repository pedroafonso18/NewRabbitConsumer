cmake_minimum_required(VERSION 3.31)
project(ConsumirRabbitCpp)

set(CMAKE_CXX_STANDARD 17)

add_executable(ConsumirRabbitCpp src/main.cpp
        include/Config.h
        lib/dotenv.h
        src/Config.cpp
        include/Database.h
        include/D_Insert.h
        include/D_Fetch.h
        src/D_Fetch.cpp
        src/D_Insert.cpp
        include/InsertTypes.h)
