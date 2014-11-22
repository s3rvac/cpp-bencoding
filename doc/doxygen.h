/**
* @file      doxygen.h
* @copyright (c) 2014 by Petr Zemek (s3rvac@gmail.com) and contributors
* @license   BSD, see the @c LICENSE file for more details
* @brief     Documentation of the main page and the used namespace.
*/

/**
* @mainpage
*
* This is an automatically generated API documentation for the <a
* href="https://github.com/s3rvac/cpp-bencoding">cpp-bencoding project</a>.
*
* @par Namespaces
*
* The base namespace is @ref bencoding. All the classes and functions provided
* by the library are part of this namespace. Unit tests are placed in the @c
* bencoding::tests namespace, which is not included in this API documentation.
*
* @par Directories
*
* The project files are situated in five directories:
* - @c doc - Contains @c doxygen.h, which includes the text of this page.
* - @c include - Header files to be included by client code.
* - @c src - Source files of the library.
* - @c sample - Source files of the sample (decoding of bencoded files). Not
*   included in this API documentation.
* - @c tests - Unit tests. Not included in this API documentation.
*
* For a more detailed list, see the @c Files tab in this page's header.
*
* @par Main Classes
*
* - @ref bencoding::BItem - Base class for all items (integers, strings, etc.).
* - @ref bencoding::BDictionary - Representation of a dictionary.
* - @ref bencoding::BInteger - Representation of an integer.
* - @ref bencoding::BList - Representation of a list.
* - @ref bencoding::BString - Representation of a string.
* - @ref bencoding::Decoder - Decoder of bencoded data.
* - @ref bencoding::Encoder - Data encoder.
* - @ref bencoding::PrettyPrinter - Pretty printer of data.
* - @ref bencoding::BItemVisitor - Base class for all visitors of the @c BItem
*   subclasses.
*
* For a more detailed list, see the @c Classes tab in this page's header.
*
* @par API Usage Example
*
* @code
* #include <iostream>         // std::cin, std::cout
* #include <memory>           // std::shared_ptr<>
*
* #include "Decoder.h"        // decode(), DecodingError
* #include "PrettyPrinter.h"  // getPrettyRepr()
*
* using namespace bencoding;
*
* int main() {
*     try {
*         // Read and decode input data from the standard input.
*         std::shared_ptr<BItem> decodedData = decode(std::cin);
*
*         // Print the decoded data in a readable way to the standard output.
*         std::cout << getPrettyRepr(decodedData) << "\n";
*
*         return 0;
*     } catch (const DecodingError &ex) {
*         // There was an error during the decoding.
*         std::cerr << "error: " << ex.what() << "\n";
*         return 1;
*     }
* }
* @endcode
*
* See the @c sample/decoder.cpp file for a complete example. Also, see the unit
* tests in the @c tests directory for additional example of using the API.
*/

// Document the bencoding namespace (there is no better place).
/// @namespace bencoding Main namespace of the bencoding library.
