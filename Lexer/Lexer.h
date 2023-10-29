#ifndef LEXER_H
#define LEXER_H

#include "Lexem.h"
#include "Tokenizer.h"
#include <regex>

class Lexer
{
    private:
        std::queue<Token> mTokens;
        std::vector<std::string> _basic_operators = {"-", "+", "/", "*", "=", "&", ">", "<", "!"};
        std::vector<std::string> _keywords;

        std::unordered_map<LexemType, std::regex> _registered_regexes;
        
        bool isOperator(std::string seq);
        bool isKeyword(std::string seq);
        std::string nextContent(std::queue<Token>& tokens);

    public:
        std::vector<Lexem> parse(std::string filename);
        void registerRegex(LexemType type, std::regex);
        void registerKeyword(std::string keyword);
};

#endif