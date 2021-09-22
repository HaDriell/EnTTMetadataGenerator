#include <cstdio>
#include <filesystem>
#include <fstream>
#include <iostream>
#include <string>

#include "HeaderParserLib/Parser.h"

void LoadFile(const std::filesystem::path& filepath, std::string& content);
void DebugNamespace(const Namespace& ns, size_t depth);
void DebugClass(const Class& clazz, size_t depth);
void DebugMetadata(const Metadata& metadata, size_t depth);


int main()
{
    std::string sources;
    LoadFile("Example.h", sources);

    Parser parser;
    parser.Parse(sources);
    DebugNamespace(parser.GetGblobalNamespace(), 0);
}


// IO Function

void LoadFile(const std::filesystem::path& filepath, std::string& content)
{
    std::ifstream file(filepath.u8string().c_str());
    content = std::string(std::istreambuf_iterator<char>(file), std::istreambuf_iterator<char>());
}


void DebugNamespace(const Namespace& ns, size_t depth)
{
    std::string prefix(4 * depth, ' ');
    std::cout << prefix << "namespace " << ns.GetName() << std::endl;
    std::cout << prefix << "{" << std::endl;
    for (const auto& [name, clazz] : ns.GetClasses())
    {
        DebugClass(clazz, depth + 1);
    }
    std::cout << prefix << "}" << std::endl;
}


void DebugClass(const Class& clazz, size_t depth)
{
    std::string prefix(4 * depth, ' ');
    std::cout << prefix << "class " << clazz.GetName() << std::endl;
    std::cout << prefix << "{" << std::endl;
    DebugMetadata(clazz.GetMetadata(), depth);
    for (const Field& field : clazz.GetFields())
    {
        std::cout << prefix << field.GetType() << " " << field.GetName() << std::endl;
    }
    std::cout << prefix << "}" << std::endl;
}


void DebugMetadata(const Metadata& metadata, size_t depth)
{
    std::string prefix(4 * depth, ' ');
    std::cout << prefix << "Metadata( ";

    bool first = true;
    for (const auto& kv : metadata.All())
    {
        if (first) first = false;
        else std::cout << ", ";
        std::cout << kv.first << " = " << kv.second;
    }

    std::cout << std::endl;
}