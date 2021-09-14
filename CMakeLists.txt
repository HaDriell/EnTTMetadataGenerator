cmake_minimum_required(VERSION 3.10)
project(
    EnTTMetadataGenerator
    VERSION 1.0
)

#Dependencies
add_subdirectory(deps/HeaderParserLib)

#Project
add_subdirectory(src)