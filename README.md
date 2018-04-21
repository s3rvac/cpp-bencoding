cpp-bencoding
=============

A C++ [bencoding](http://en.wikipedia.org/wiki/Bencode) library supporting
both decoding and encoding. It provides a simple API for decoding, encoding,
and pretty-printing of bencoded data. It is also extensible so you can write
your own manipulation of the decoded data.

``` cpp
#include "bencoding/bencoding.h"

// Decode data stored in a std::string.
auto decodedData = bencoding::decode(str);

// Decode data directly from a stream.
auto decodedData = bencoding::decode(stream);

// Encode the data into a std::string.
std::string encodedData = bencoding::encode(decodedData);

// Get a pretty representation of the decoded data.
std::string prettyRepr = bencoding::getPrettyRepr(decodedData);
```

The supported format is as defined in the [BitTorrent
specification](https://wiki.theory.org/BitTorrentSpecification#Bencoding).

Requirements
------------

The following software is required:
* A compiler supporting C++11, such as [GCC >= 4.9](https://gcc.gnu.org/).
* [CMake](http://www.cmake.org/) to build and install the library.

Optional:
* [Doxygen](http://www.doxygen.org/) to generate API documentation.
* [Google Test](https://code.google.com/p/googletest/) to build and run tests.
* [LCOV](http://ltp.sourceforge.net/coverage/lcov.php) to generate code
  coverage statistics.

Build and Installation
----------------------

1. Install the requirements above.
2. Clone this repository:

    ```
    git clone https://github.com/s3rvac/cpp-bencoding
    ```

3. Create a `build` directory, enter it, run `cmake ..` and `make` (possibly
   with additional parameters, see below):

    ```
    mkdir build
    cd build
    cmake ..
    make
    ```

   You can pass additional parameters to the `cmake` call:
   * `-DWITH_COVERAGE=1` to build with code coverage support (requires
     [LCOV](http://ltp.sourceforge.net/coverage/lcov.php), disabled by default).
   * `-DWITH_DOC=1` to build API documentation (requires
     [Doxygen](http://www.doxygen.org/), disabled by default).
   * `-DWITH_TESTS=1` to build tests (requires [Google
     Test](https://code.google.com/p/googletest/), disabled by defauly).
   * `-DCMAKE_BUILD_TYPE=debug` to build the library with debugging
     information, which is useful during the development. By default, the
     library is built in the `release` mode.
   * `-DCMAKE_INSTALL_PREFIX:PATH=/usr` to set a custom installation path.

   The `make` call supports standard parameters, such as:
   * `-j N` to build the library by using `N` processors.
   * `VERBOSE=1` to show verbose output when building the library.
4. Install the library:

    ```
    make install
    ```

   This will install the library into the selected installation path. If you
   did not specify the path when calling `cmake`, it will be installed to the
   `install` directory.

Usage
-----

1. Setup the build system of your project to include the path to the
   `install/include` directory above so you can include the library header
   files in the following way:

    ``` cpp
    #include "bencoding/bencoding.h"
    ```

   The header file `bencoding.h` includes all the library header files. You may
   include just some of them if you want:

    ``` cpp
    #include "bencoding/Decoder.h"
    #include "bencoding/PrettyPrinter.h"
    ```

2. Use the functionality provided by the library. A simple example:

    ``` cpp
    #include <iostream>
    #include <memory>

    #include "bencoding/bencoding.h"

    using namespace bencoding;

    int main() {
        try {
            // Read and decode input data from the standard input.
            std::shared_ptr<BItem> decodedData = decode(std::cin);

            // Print the decoded data in a readable way to the standard output.
            std::cout << getPrettyRepr(decodedData) << "\n";

            return 0;
        } catch (const DecodingError &ex) {
            // There was an error during the decoding.
            std::cerr << "error: " << ex.what() << "\n";
            return 1;
        }
    }
    ```

    For a full example, see the `sample/decoder.cpp` file.

3. Setup the build system of your project to link the
   `install/lib/libbencoding.a` library. For example, with GCC, you can either
   use `-Linstall/lib -lbencoding` or link the `install/lib/libbencoding.a`
   file directly.

Sample
------

A complete sample is available in the `sample` directory. It is a standalone
decoder that decodes data from the given file or standard input, and prints
them in a pretty format to the standard output. The decoder is built and
installed alongside with the library. To run it, execute `install/bin/decoder`
after installation. Sample input files are in the `sample/inputs` directory.

Input file (`sample/inputs/sample1.torrent`):
```
d8:announce18:http://tracker.com10:created by14:KTorrent 2.1.413:creation datei1182163277e4:infod6:lengthi6e4:name8:file.txt12:piece lengthi32768e6:pieces12:binary dataee
```

Run:
```
$ install/bin/decoder sample/inputs/sample1.torrent
```

Output:
```
{
    "announce": "http://tracker.com",
    "created by": "KTorrent 2.1.4",
    "creation date": 1182163277,
    "info": {
        "length": 6,
        "name": "file.txt",
        "piece length": 32768,
        "pieces": "binary data"
    }
}
```

For more examples, see the API documentation.

API Documentation
-----------------

The latest API documentation is available
[here](https://projects.petrzemek.net/cpp-bencoding/doc/latest/).

The API documentation can be generated by passing `-DWITH_DOC=1` when running
`cmake` (see the build instructions). When you run `make` afterwards, the
documentation is generated in the HTML format. After `make install`, it can be
viewed in your favorite web browser by opening `install/doc/index.html`. You
need to have [Doxygen](http://www.doxygen.org/) installed to generate the API
documentation.

Tests
-----

Over 99% of the library source code is covered by unit tests. To build them,
pass `-DWITH_TESTS=1` when running `cmake`. To run them after `make install`,
execute `install/bin/tester`. You need to have [Google
Test](https://code.google.com/p/googletest/) installed to build and run the
tests.

Code Coverage
-------------

The latest code coverage by tests is available
[here](https://projects.petrzemek.net/cpp-bencoding/coverage/latest/).

To generate code coverage, pass `-DWITH_COVERAGE=1` when running `cmake`. After
the library is built, run `make coverage` from the `build` directory to
generate the code coverage. It can be then viewed in a web browser by opening
`coverage/index.html`. You need to have
[LCOV](http://ltp.sourceforge.net/coverage/lcov.php) installed to generate the
code coverage.

Extending the Library
---------------------

The `BItemVisitor` class implements the [Visitor design
pattern](http://en.wikipedia.org/wiki/Visitor_pattern). You can create your own
subclass that manipulates the bencoded data in any way you want. Two examples
of using the `BItemVisitor` class are the `Encoder` and `PrettyPrinter`
classes. See [my blog
post](https://blog.petrzemek.net/2014/09/14/cpp-bencoding-new-cpp-bencoding-library/)
or their source code for more details.

Contributions
-------------

Any contributions are welcomed! Notes:
* Please, before sending a patch or a pull request, ensure that all the tests
  still pass.
* If you provide new functionality, please also provide tests for it.

License
-------

Copyright (c) 2014 Petr Zemek (<s3rvac@gmail.com>) and contributors.

Distributed under the BSD 3-clause license. See the `LICENSE` file for more
details.
