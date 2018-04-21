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
* @par Example: Creating Data
*
* @code
* // To create an integer:
* auto i = bencoding::BInteger::create(5);
*
* // To create a string:
* auto s = bencoding::BString::create("test");
*
* // To create a list:
* auto l = bencoding::BList::create();
* l->push_back(bencoding::BInteger::create(1));
* l->push_back(bencoding::BInteger::create(2));
*
* // To create a dictionary:
* auto d = bencoding::BDictionary::create();
* (*d)[bencoding::BString::create("a")] = bencoding::BInteger::create(1);
* (*d)[bencoding::BString::create("b")] = bencoding::BInteger::create(2);
* @endcode

* @par Example: Encoding
*
* @code
* std::string encodedData = bencoding::encode(data);
* @endcode
*
* @par Example: Decoding
*
* @code
* auto data = bencoding::decode(stream);
* if (auto i = data->as<bencoding::BInteger>()) {
*     std::cout << i->value() << "\n";
* } else if (auto s = data->as<bencoding::BString>()) {
*     std::cout << s->value() << "\n";
* } else if (auto l = data->as<bencoding::BList>()) {
*     for (auto e : l) {
*         // ...
*     }
* } else if (auto d = data->as<bencoding::BDictionary>()) {
*     for (auto e : d) {
*         // ...
*     }
* }
* @endcode
*
* A better way of traversing the decoded data is to use @ref
* bencoding::BItemVisitor. For an example, see the implementation of @ref
* bencoding::PrettyPrinter.
*
* @par Example: Pretty Printing
*
* @code
* auto data = bencoding::decode(stream);
* std::string repr = bencoding::getPrettyRepr(data);
* std::cout << repr << "\n";
* @endcode
*/

// Document the bencoding namespace (there is no better place).
/// @namespace bencoding Main namespace of the bencoding library.
