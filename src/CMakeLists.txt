file(GLOB_RECURSE SOURCES "${EnTTMetadataGenerator_SOURCE_DIR}/src/*.cpp")


add_executable(EnTTMetadataGenerator ${SOURCES})
target_include_directories(EnTTMetadataGenerator PUBLIC "${EnTTMetadataGenerator_SOURCE_DIR}/src/")
target_compile_features(EnTTMetadataGenerator PUBLIC cxx_std_17)

target_link_libraries(EnTTMetadataGenerator HeaderParserLib)
