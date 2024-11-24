cmake_minimum_required(VERSION 3.29)
project(essaie C)

set(CMAKE_C_STANDARD 11)

add_executable(essaie main.c
        game_play.c
        game_play.h
        sauvegarde.c
        sauvegarde.h
        historique.c
        historique.h)
