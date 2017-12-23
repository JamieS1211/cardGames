cmake_minimum_required(VERSION 3.8)
project(blackJack)

set(CMAKE_C_STANDARD 99)

set(SOURCE_FILES blackJack/game/playBlackJack.c blackJack/blackJackCard.c cardAPI/stack.c cardAPI/player.c cardAPI/utilityFunctions.c blackJack/blackJackPlayer.c blackJack/blackJack.h)
add_executable(blackJack ${SOURCE_FILES})