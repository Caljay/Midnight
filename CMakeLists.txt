cmake_minimum_required(VERSION 3.31)
project(Midnight C)

set(CMAKE_C_STANDARD 99)

add_executable(Midnight main.c
        Player.h
        game.c
        game.h
        Stocks.h
        Stocks.c
        Player.c
        News.c
        News.h)

target_link_libraries(Midnight -lncurses m)
