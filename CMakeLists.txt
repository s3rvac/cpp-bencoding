##
## Project:   cpp-bencoding
## Copyright: (c) 2014 by Petr Zemek <s3rvac@gmail.com> and contributors
## License:   BSD, see the LICENSE file for more details
##
## The project's main CMake configuration file.
##

cmake_minimum_required(VERSION 2.8)
project(cpp-bencoding CXX)

##
## Options.
##

option(WITH_DOC "Build API documentation (requires Doxygen)." ON)
option(WITH_TESTS "Build tests (requires Google Test)." ON)

##
## Paths.
##

set(CMAKE_INSTALL_PREFIX "${CMAKE_SOURCE_DIR}/install")
set(INSTALL_BIN_DIR "${CMAKE_INSTALL_PREFIX}/bin")
set(INSTALL_DOC_DIR "${CMAKE_INSTALL_PREFIX}/doc")
set(INSTALL_INCLUDE_DIR "${CMAKE_INSTALL_PREFIX}/include")
set(INSTALL_LIB_DIR "${CMAKE_INSTALL_PREFIX}/lib")

##
## Includes.
##

include_directories(include)

##
## Compiler options.
##

# C++11 is required.
set(CMAKE_CXX_FLAGS "-std=c++11 -pedantic")

# Abort compilation upon the first error.
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wfatal-errors")

# Standard warning parameters.
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Wextra")

# Enable additional warnings that are not included in -Wall and -Wextra
# (according to `man gcc`).
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wcast-align")
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wcast-qual")
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wfloat-equal")
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wold-style-cast")
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wswitch-default")
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wuninitialized")
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wuseless-cast")

##
## Subdirectories.
##

add_subdirectory(doc)
add_subdirectory(include)
add_subdirectory(src)
add_subdirectory(tests)
