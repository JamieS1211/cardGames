cmake_minimum_required(VERSION 3.8)
project(blackJack)

set(CMAKE_C_STANDARD 99)

set(SOURCE_FILES blackJack/cardCount/cardCountBlackJack.c blackJack/game/playBlackJack.c blackJack/blackJackCard.c cardAPI/deckStack.c cardAPI/player.c cardAPI/utilityFunctions.c blackJack/blackJackPlayer.c blackJack/blackJack.h generalAPI/userInput.c blackJack/cardCount/probabilityCalculator.c main.c cardAPI/simpleStack.c cardAPI/largeNumber.c)
add_executable(blackJack ${SOURCE_FILES})