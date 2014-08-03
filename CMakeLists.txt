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
## Subdirectories.
##

add_subdirectory(doc)
add_subdirectory(include)
add_subdirectory(src)
add_subdirectory(tests)
