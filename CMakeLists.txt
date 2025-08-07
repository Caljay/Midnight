cmake_minimum_required(VERSION 3.31)
project(Midnight C)

set(CMAKE_C_STANDARD 99)

add_executable(Midnight src/main.c
        src/Player.h
        src/game.c
        src/game.h
        src/Stocks.h
        src/Stocks.c
        src/Player.c
        src/News.c
        src/News.h)

target_link_libraries(Midnight -lncurses m)
