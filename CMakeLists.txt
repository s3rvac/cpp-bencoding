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

option(WITH_COVERAGE "Build with code coverage support (requires lcov and build with tests)." OFF)
option(WITH_DOC "Build API documentation (requires Doxygen)." OFF)
option(WITH_TESTS "Build tests (requires Google Test)." OFF)

if(${WITH_COVERAGE})
	set(WITH_TESTS ON)
endif()

##
## Paths.
##

if(CMAKE_INSTALL_PREFIX_INITIALIZED_TO_DEFAULT)
    set(CMAKE_INSTALL_PREFIX "${CMAKE_SOURCE_DIR}/install" CACHE PATH "default install path" FORCE)
endif()
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
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11 -pedantic")

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
## Code coverage.
##

if(WITH_COVERAGE)
	# Enable code coverage.
	set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} --coverage")

	# Build with debugging information to make the output meaningful.
	set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -g")

	# Disable optimizations to get the most accurate results.
	set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -O0")

	# Add a custom target to generate the code coverage.
	add_custom_target(coverage
		COMMENT "Running the tests and generating code coverage"
		COMMAND "${PROJECT_BINARY_DIR}/tests/tester"
		COMMAND mkdir -p coverage
		COMMAND lcov --capture --directory include --directory src
			--directory tests --directory "${PROJECT_BINARY_DIR}"
			--no-external --output-file coverage/coverage.info
		COMMAND genhtml --show-details --num-spaces 4 --demangle-cpp
			--legend --title "cpp-bencoding code coverage"
			coverage/coverage.info --output-directory coverage
		WORKING_DIRECTORY "${PROJECT_SOURCE_DIR}")
endif()

##
## Subdirectories.
##

add_subdirectory(doc)
add_subdirectory(include)
add_subdirectory(src)
add_subdirectory(sample)
add_subdirectory(tests)
