##
## Project:   cpp-bencoding
## Copyright: (c) 2014 by Petr Zemek <s3rvac@gmail.com> and contributors
## License:   BSD, see the LICENSE file for more details
##
## CMake configuration file for the tests of the library.
##

if(NOT WITH_TESTS)
	return()
endif()

find_package(GTest REQUIRED)

set(TESTER_SOURCES
	BDictionaryTests.cpp
	BIntegerTests.cpp
	BListTests.cpp
	BStringTests.cpp
	DecoderTests.cpp
	EncoderTests.cpp
	PrettyPrinterTests.cpp
	TestUtils.cpp
	UtilsTests.cpp
)

add_executable(tester ${TESTER_SOURCES})

target_link_libraries(tester bencoding gtest gtest_main)

install(TARGETS tester DESTINATION "${INSTALL_BIN_DIR}")
