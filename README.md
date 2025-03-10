# cb-ClangTidy
Code::Blocks plugin to support clang-tidy static analysis

## Description

clang-tidy is a well known static analysis tool for C++. This plugins integrates it to Code::Blocks.

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

### Installation and Setup
Install the plugin by clicking ```Install New``` in ```Plugins->Manage Plugin``` menu and selecting CbClangTidy.cbplugin.  
clang-tidy should be installed before this plugin can be used.  
Navigate to Settings->Environment->CbClangTidy and verify or enter the location of the clang-tidy executable in the box labeled ```clang-tidy application:```.

## Run clang-tidy
Navigate to ```Plugins``` menu and click on ```cbClangTidy```

## License

This project is licensed under the GPL V3 License - see the LICENSE file for details

## Limitations

If this is not used along with clangd_client, compile_commands.json has to be added to project's root directory manually.  
This plugin requires compiler supporting c++20 as dependencies require it.  
wxsmith files are not updated as I'm not familiar with wxsmith, also not much comfortable with UI designing.

## Acknowledgments
Code is copied from [Code::Blocks](https://www.codeblocks.org/) CppCheck plugin and modified. Thank you KillerBot.  
Regex parsing uses [compile-time-regular-expressions](https://github.com/hanickadot/compile-time-regular-expressions)
