cmake_minimum_required(VERSION 3.8)
project(blackJack)

set(CMAKE_C_STANDARD 99)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

list(APPEND CMAKE_MODULE_PATH "${CMAKE_CURRENT_LIST_DIR}/cmake")

##Add OpenMP for multithreading
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -fopenmp")

OPTION (USE_OpenMP "Use OpenMP" ON)
IF(USE_OpenMP)
    FIND_PACKAGE(OpenMP)
    IF(OPENMP_FOUND)
        SET(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} ${OpenMP_C_FLAGS}")
        SET(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} ${OpenMP_CXX_FLAGS}")
    ENDIF()
ENDIF()
##Finished OpenMP inclusion


##Add source files
set(GENERAL_API_SOURCE_FILES
        generalAPI/userInput.h generalAPI/userInput.c
        )

set(CARD_API_SOURCE_FILES
        cardAPI/api.h cardAPI/api.c
        cardAPI/deckStack.h cardAPI/deckStack.c
        cardAPI/player.h cardAPI/player.c
        cardAPI/simpleStack.h cardAPI/simpleStack.c
        cardAPI/utilityFunctions.h cardAPI/utilityFunctions.c
        )

set(BLACK_JACK_API_SOURCE_FILES
        blackJack/blackJackAPI/blackJack.h
        blackJack/blackJackAPI/blackJackCard.h blackJack/blackJackAPI/blackJackCard.c
        blackJack/blackJackAPI/blackJackPlayer.h blackJack/blackJackAPI/blackJackPlayer.c
        blackJack/blackJackAPI/calculateBet.h blackJack/blackJackAPI/calculateBet.c

        blackJack/cardCount/cardCountBlackJack.h blackJack/cardCount/cardCountBlackJack.c
        blackJack/cardCount/probabilityCalculator.h blackJack/cardCount/probabilityCalculator.c

        blackJack/game/automateBlackJack.h blackJack/game/automateBlackJack.c
        blackJack/game/playBlackJack.h blackJack/game/playBlackJack.c

        blackJack/mapping.h blackJack/mapping.c
        )

add_executable(blackJack
        main.c
        ${GENERAL_API_SOURCE_FILES}
        ${CARD_API_SOURCE_FILES}
        ${BLACK_JACK_API_SOURCE_FILES}
        )


##Include GMP
include(FindPkgConfig)
find_package(GMP REQUIRED)
include_directories(${GMP_INCLUDE_DIR})
target_link_libraries(blackJack ${GMP_LIBARY})