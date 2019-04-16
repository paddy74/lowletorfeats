[![License: MIT](https://img.shields.io/badge/License-MIT-yellow.svg)](https://opensource.org/licenses/MIT)

# Learning-To-Rank Low-Level Feature Library

A library for the collection of common low-level features used in learning-to-rank algorithms. These features are calculated using well-defined algorithms.

If you feel there are additional features that might be added to this library, create a [new issue](issues/new) or submit a pull request.

High level features created using machine learning based methods can be found or added to my [highletorfeats library](https://github.com/paddy74/highletorfeats/).

## Features

The following categories of low-level features are collected using this library:

- TF-IDF
- Okapi BM25
- LMIR (TODO)

## Getting started

### Adding to your project

The recommended way to add this library to you project is by including the following to your CMakeLists.txt:

```cmake
cmake_minimum_required(VERSION 3.13)
project(myProject)

include_directories("path/to/lowletorfeats/include")
add_subdirectory("path/to/lowletorfeats")

add_executable(myProject myProject_SOURCES)
# or `add_library(myProject myProject_SOURCES)`

target_link_libraries(myProject lowletorfeats)
```

### Usage

The library has can be included in your source files with the following:

```cpp
#include <lowletorfeats/FeatureCollector.hpp>
```

An example case can be found in [tests/src/main.cpp](tests/src/main.cpp).

## Versioning

We use [SemVer](http://semver.org/) for versioning. For the versions available, see the [tags on this repository](tags).

## Authors

- **Patrick Cox** - [paddy74](https://github.com/paddy74)

## License

This project is licensed under the MIT License - see the [LICENSE.md](LICENSE.md) file for details.
