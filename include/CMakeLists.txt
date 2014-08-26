##
## Project:   cpp-bencoding
## Copyright: (c) 2014 by Petr Zemek <s3rvac@gmail.com> and contributors
## License:   BSD, see the LICENSE file for more details
##
## CMake configuration file for the library include files.
##

set(INCLUDES
	bencoding.h
	BDictionary.h
	BInteger.h
	BItem.h
	BItemVisitor.h
	BList.h
	BString.h
	Decoder.h
	Encoder.h
	PrettyPrinter.h
	Utils.h
)

install(FILES ${INCLUDES} DESTINATION "${INSTALL_INCLUDE_DIR}/bencoding")
