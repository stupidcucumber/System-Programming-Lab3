#include "Lexer.h"
#include <iostream>

int main(int argnum, const char** args)
{   
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

    std::vector<Lexem> lexems = lexer.parse(filename);

    for (auto lexem : lexems)
    {
        std::cout << lexem << std::endl;
    }

    return 0;
}