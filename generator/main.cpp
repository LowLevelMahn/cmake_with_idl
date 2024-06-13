#include <cstdio>
#include <string>
#include <vector>
#include <fstream>
#include <cassert>
#include <regex>
#include <filesystem>

std::string trim(const std::string& str)
{
    std::regex pattern("\\s+");
    return std::regex_replace(str, pattern, " ");
}

int main(int argc, char* argv[])
{
    // idl, output_path
    if (argc != 3)
    {
        printf("generator idl-file output-dir\n");
        return 1;
    }

    std::filesystem::path idl_file = argv[1];
    assert(std::filesystem::exists(idl_file));

    std::filesystem::path output_dir = argv[2];
    assert(std::filesystem::exists(output_dir));

    // read idl info
    std::vector<std::string> lines;
    {
        std::ifstream ifs(idl_file);
        assert(ifs);
        for (std::string line; std::getline(ifs, line); /**/)
        {
            if (trim(line) != "")
            {
                lines.push_back(line);
            }
        }
    }

    // generate some stuff
    std::string generated;
    {
        for (auto& type : lines)
        {
            generated += "class " + type + "{};\n";
        }
    }

    {
        std::string output_filename = idl_file.filename().string() + ".hpp";
        std::filesystem::path generated_filename = output_dir / output_filename;
        std::ofstream out(generated_filename);
        out << generated;
    }

    return 0;
}
