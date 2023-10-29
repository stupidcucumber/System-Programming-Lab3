#ifndef LEXER_H
#define LEXER_H

#include "Lexem.h"
#include "Tokenizer.h"

class Lexer
{
    private:
        std::queue<Token> mTokens;
        std::vector<std::string> _basic_operators = {"-", "+", "/", "*", "=", "&", ">", "<", "!"};
        
        bool isOperator(std::string seq);
        std::string nextContent(std::queue<Token>& tokens);
    public:
        std::vector<Lexem> parse(std::string filename);
};

#endif