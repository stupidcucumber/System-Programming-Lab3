#ifndef TOKENIZER_H
#define TOKENIZER_H

#include "Token.h"
#include <fstream>
#include <queue>

class Tokenizer
{
    private:
        std::ifstream mFile;
        std::unordered_map<TokenType, std::string> mMapping = {
            {
                TokenType::NONE, "None"
            },
            {
                TokenType::TERMINAL, "Terminal"
            },
            {
                TokenType::NONTERMINAL, "Nonterminal"
            },
            {
                TokenType::END, "End"
            }
        };

        std::vector<char> _delimiters = {'(', ')', '{', '}', ';', '\n', '<', '>', '"', '\'', ',', ' '};

        std::string mCurrentToken;
        TokenType mTokenType = TokenType::NONE;        

        bool handleNone(char currentChar);
        bool handleNonterminal(char currentChar);
        bool handleTerminal(char currentChar);

        bool isDelimiter(char currentChar);

    public:
        Tokenizer(std::string filename);
        
        std::queue<Token> tokenize();
        Token nextToken();

        ~Tokenizer();
};

#endif