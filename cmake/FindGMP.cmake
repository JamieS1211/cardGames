##Add GMP for arbitary length numbers

##Setup locations
set(FIND_GMP_PATHS libaries/gmp)

find_path(GMP_INCLUDE_DIR gmp.h
        PATH_SUFFIXES include
        PATHS ${FIND_GMP_PAHTS})

find_library(GMP_LIBARY
        NAMES libgmp
        PATH_SUFFIXES lib
        PATHS ${FIND_GMP_PATHS})