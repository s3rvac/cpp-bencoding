/**
* @file      decoder.cpp
* @copyright (c) 2014 by Petr Zemek (s3rvac@gmail.com) and contributors
* @license   BSD, see the @c LICENSE file for more details
* @brief     A sample application: decoding of bencoded files.
*/

#include <fstream>
#include <iostream>
#include <memory>
#include <string>

#include "Decoder.h"
#include "PrettyPrinter.h"

using namespace bencoding;

namespace {

/**
* @brief Checks if help was requested.
*/
bool helpIsRequested(int argc, char **argv) {
	if (argc != 2) {
		return false;
	}

	std::string firstArg(argv[1]);
	if (firstArg == "-h" || firstArg == "--help") {
		return true;
	}

	return false;
}

/**
* @brief Prints help to the standard output.
*/
void printHelp(const std::string &prog) {
	std::cout
		<< "A decoder of bencoded files.\n"
		<< "\n"
		<< "Usage: " << prog << " [FILE]\n"
		<< "\n"
		<< "If FILE is not given, the data are read from the standard input.\n"
		<< "The decoded data are printed to the standard output.\n";
}

} // anonymous namespace

int main(int argc, char **argv) {
	if (helpIsRequested(argc, argv)) {
		printHelp(argv[0]);
		return 0;
	}

	// Decoding.
	std::shared_ptr<BItem> decodedData;
	try {
		if (argc > 1) {
			std::ifstream input(argv[1]);
			decodedData = decode(input);
		} else {
			decodedData = decode(std::cin);
		}
	} catch (const DecodingError &ex) {
		std::cerr << "error: " << ex.what() << "\n";
		return 1;
	}

	// Printing.
	std::cout << getPrettyRepr(decodedData) << "\n";

	return 0;
}
