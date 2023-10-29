#include "Lexer.h"
#include <iostream>
#include "yaml-cpp/yaml.h"

int main(int argnum, const char** args)
{
    YAML::Node configLexer = YAML::LoadFile("lexer.yaml")["lexer"];
    std::unordered_map<std::string, LexemType> converter = {
        {
            "String", LexemType::String
        },
        {
            "Char", LexemType::Char
        },
        {
            "Whole", LexemType::Whole
        },
        {
            "Float", LexemType::Float
        },
        {
            "Preprocessor", LexemType::Preprocessor 
        },
        {
            "Reserved", LexemType::Reserved
        },
        {
            "Operator", LexemType::Operator
        },
        {
            "Delimiter", LexemType::Delimiter
        },
        {
            "Identifier", LexemType::Identifier
        },
        {
            "Hexadecimal", LexemType::Hexadecimal
        },
        {
            "Comment", LexemType::Comment
        }
    };

    if (argnum > 2)
    {
        std::cout << "Too many CLI arguments passed!" << std::endl;

        return -1;
    }

    if (argnum < 2)
    {
        std::cout << "You need to specify filename!" << std::endl;

        return 1;
    }

    std::string filename(args[1]);
    Lexer lexer;
    for (auto it = configLexer["regex"].begin(); it != configLexer["regex"].end(); ++it)
    {
        std::string type = (*it).first.as<std::string>();
        std::string rawRegex = (*it).second.as<std::string>();

        lexer.registerRegex(converter.at(type), std::regex(rawRegex));
    }


    std::vector<Lexem> lexems = lexer.parse(filename);

    for (auto lexem : lexems)
    {
        std::cout << lexem << std::endl;
    }

    return 0;
}