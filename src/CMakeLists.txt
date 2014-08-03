##
## Project:   cpp-bencoding
## Copyright: (c) 2014 by Petr Zemek <s3rvac@gmail.com> and contributors
## License:   BSD, see the LICENSE file for more details
##
## CMake configuration file for the library source files.
##

set(BENCODING_SOURCES
	BDictionary.cpp
	BInteger.cpp
	BItem.cpp
	BList.cpp
	BString.cpp
	Decoder.cpp
	Encoder.cpp
)

add_library(bencoding ${BENCODING_SOURCES})

install(TARGETS bencoding DESTINATION "${INSTALL_LIB_DIR}")
