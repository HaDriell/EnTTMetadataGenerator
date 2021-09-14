#include <cstdio>
#include <filesystem>
#include <fstream>
#include <iostream>
#include <string>

#include "Parser.h"

void LoadFile(const std::filesystem::path& filepath, std::string& content);

int main()
{
    std::string sources;
    LoadFile("Example.h", sources);

    Parser parser;
    parser.Parse(sources);
    parser.GetGlobalScope().Bake(std::cout);
}



// IO Function

void LoadFile(const std::filesystem::path& filepath, std::string& content)
{
    std::ifstream file(filepath.u8string().c_str());
    content = std::string(std::istreambuf_iterator<char>(file), std::istreambuf_iterator<char>());
}