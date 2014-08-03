##
## Project:   cpp-bencoding
## Copyright: (c) 2014 by Petr Zemek <s3rvac@gmail.com> and contributors
## License:   BSD, see the LICENSE file for more details
##
## CMake configuration file for the tests of the library.
##

find_package(GTest REQUIRED)

set(TESTS_SOURCES
	BDictionaryTests.cpp
	BIntegerTests.cpp
	BListTests.cpp
	BStringTests.cpp
	DecoderTests.cpp
	EncoderTests.cpp
)

add_executable(tests ${TESTS_SOURCES})

target_link_libraries(tests bencoding gtest gtest_main)

install(TARGETS tests DESTINATION "${INSTALL_BIN_DIR}")
