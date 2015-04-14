##
## Project:   cpp-bencoding
## Copyright: (c) 2014 by Petr Zemek <s3rvac@gmail.com> and contributors
## License:   BSD, see the LICENSE file for more details
##
## CMake configuration file for the API documentation.
##

if(NOT WITH_DOC)
	return()
endif()

find_package(Doxygen REQUIRED)

set(DOXYGEN_CFG_IN "doxygen.in")
set(DOXYGEN_CFG "${CMAKE_CURRENT_BINARY_DIR}/doxygen.cfg")
# The trailing '/' after html is significant (otherwise, the files would be
# installed into ${INSTALL_DOC_DIR}/html instead of ${INSTALL_DOC_DIR}).
set(DOXYGEN_OUTPUT_DIR "${CMAKE_CURRENT_BINARY_DIR}/html/")

# We need to set proper paths in the input Doxygen configuration file.
configure_file("${DOXYGEN_CFG_IN}" "${DOXYGEN_CFG}" @ONLY)

# Add a target to generate the documentation by running Doxygen.
add_custom_target(doc ALL
	COMMAND ${DOXYGEN_EXECUTABLE} "${DOXYGEN_CFG}"
	SOURCES "${DOXYGEN_CFG}"
	WORKING_DIRECTORY "${CMAKE_CURRENT_BINARY_DIR}"
	COMMENT "Generating API documentation with Doxygen" VERBATIM
)

# Cleanup.
set_directory_properties(PROPERTIES ADDITIONAL_MAKE_CLEAN_FILES "${DOXYGEN_OUTPUT_DIR}")

install(DIRECTORY "${DOXYGEN_OUTPUT_DIR}" DESTINATION "${INSTALL_DOC_DIR}")
