#Generated by CBProjectExporter : https://github.com/josephch/CBProjectExporter 
cmake_minimum_required(VERSION 3.24.0) 

project("default")
set(TARGET_OUTPUTNAME "CbClangTidy")
# Include CMakePrintHelpers module:
include(CMakePrintHelpers)

# -------------------------------------------------------------------------------------------------

# Compiler Include paths:
include_directories("${CMAKE_SOURCE_DIR}/compiler-output-parser/compile-time-regular-expressions/include"
                    )

# Compiler flags:
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++20")
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -fPIC")
find_package(PkgConfig REQUIRED)
pkg_check_modules(CODEBLOCKS REQUIRED codeblocks)
include_directories("${CODEBLOCKS_INCLUDE_DIRS}")
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} ${CODEBLOCKS_CFLAGS_OTHER}")
find_package(wxWidgets REQUIRED)
include(${wxWidgets_USE_FILE})
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -g")
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall")

# -------------------------------------------------------------------------------------------------

# Source files to compile:
FILE(GLOB SOURCE_FILES
            "CbClangTidy.cpp"
            "CbClangTidyConfigPanel.cpp"
            "CbClangTidyListLog.cpp"

            "CbClangTidy.h"
            "CbClangTidyConfigPanel.h"
            "CbClangTidyListLog.h"
            "compiler-output-parser/compiler_output_parser.hpp"
    )

# Target type: ttDynamicLib - DLL
add_library(${TARGET_OUTPUTNAME} SHARED ${SOURCE_FILES})

# Set the target output directory:
set_target_properties(${TARGET_OUTPUTNAME} PROPERTIES LIBRARY_OUTPUT_DIRECTORY "${CMAKE_SOURCE_DIR}/")
set_target_properties(${TARGET_OUTPUTNAME} PROPERTIES  OUTPUT_NAME "CbClangTidy"  PREFIX ""  RUNTIME_OUTPUT_DIRECTORY "${CMAKE_SOURCE_DIR}/")

unset(SOURCE_FILES)

# -------------------------------------------------------------------------------------------------

# Linker options:
set(LINKER_OPTIONS_LIST)
list(APPEND LINKER_OPTIONS_LIST "-Wl,--no-undefined")
list(APPEND LINKER_OPTIONS_LIST "${CODEBLOCKS_LINK_LIBRARIES}")
list(APPEND LINKER_OPTIONS_LIST "${wxWidgets_LIBRARIES}")
target_link_libraries(${TARGET_OUTPUTNAME} PRIVATE ${LINKER_OPTIONS_LIST})
unset(LINKER_OPTIONS_LIST)

# Target after commands:
# zip -j9 CbClangTidy.zip resources/manifest.xml
add_custom_command(
                   TARGET ${TARGET_OUTPUTNAME}
                   POST_BUILD COMMAND zip -j9 CbClangTidy.zip resources/manifest.xml
                   WORKING_DIRECTORY ${CMAKE_SOURCE_DIR}
                  )

# zip -j9 CbClangTidy.cbplugin CbClangTidy.so CbClangTidy.zip
add_custom_command(
                   TARGET ${TARGET_OUTPUTNAME}
                   POST_BUILD COMMAND zip -j9 CbClangTidy.cbplugin CbClangTidy.so CbClangTidy.zip
                   WORKING_DIRECTORY ${CMAKE_SOURCE_DIR}
                  )


unset(TARGET_OUTPUTNAME)
# -------------------------------------------------------------------------------------------------

