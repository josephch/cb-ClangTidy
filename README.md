# cb-ClangTidy
Code::Blocks plugin to support clang-tidy static analysis

## Description

clang-tidy is a well known static analysis tool for C++. This plugins integrates it to Code::Blocks

## Getting Started
### Getting the source
```
git clone https://github.com/josephch/cb-ClangTidy.git
```
Plugin depends on [compiler-output-parser](https://github.com/josephch/compiler-output-parser.git) which in turn depends on [compile-time-regular-expressions](https://github.com/hanickadot/compile-time-regular-expressions). They are  present as git submodules, can be fetched via
```
git submodule update --init --recursive
```

### Build using cmake
```
mkdir cmake-build
cd cmake-build
cmake ../
make
```
### Build using Code::Blocks
Build after opening project in Code::Blocks

## License

This project is licensed under the GPL V3 License - see the LICENSE file for details

## Acknowledgments
Code is copied from [Code::Blocks](https://www.codeblocks.org/) cppcheck plugin and modified. Thank you KillerBot.

Regex parsing uses [compile-time-regular-expressions](https://github.com/hanickadot/compile-time-regular-expressions)
