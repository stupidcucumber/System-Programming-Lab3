#include "Lexer.h"
#include <iostream>

int main(int argnum, const char** args)
{
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

    std::regex regString("\".*\"");
    std::regex regRegularChar("\'[^\\\\]?\'");
    std::regex regEscapeChar(R"(\'\\\S{1}\')");
    std::regex regWhole("^[0-9]+$");
    std::regex regFloat("[+-]?([0-9]+([.][0-9]*)?|[.][0-9]+)");
    std::regex regHex("0[xX][0-9a-fA-F]+");

    std::regex regCommentInline("^//.*");
    std::regex regCommentBlock("^/\*[\S\n\s]*\*/");
    std::regex regPreprocessor("^#.*");
    std::regex regIdentifier("[a-zA-Z_][a-zA-Z0-9_]*");

    std::regex regOperator("==|-=|\\+=|/=|\\*=|&=|>=|<=|<<|>>|!|::|\\.|\\=|\\+|\\*|-|<|>");
    std::regex regDelimiter(";|\\{|\\}|\\(|\\)|\\[|\\]|\\s|,");

    std::vector<Lexem> lexems = lexer.parse(filename);

    for (auto lexem : lexems)
    {
        std::cout << lexem << std::endl;
    }

    return 0;
}