##
## Project:   cpp-bencoding
## Copyright: (c) 2014 by Petr Zemek <s3rvac@gmail.com> and contributors
## License:   BSD, see the LICENSE file for more details
##
## CMake configuration file for the sample application source files.
##

set(DECODER_SOURCES
	decoder.cpp
)

add_executable(decoder ${DECODER_SOURCES})
target_link_libraries(decoder bencoding)

install(TARGETS decoder DESTINATION "${INSTALL_BIN_DIR}")
