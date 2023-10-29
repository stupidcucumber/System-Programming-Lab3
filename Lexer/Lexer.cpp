#include "Lexer.h"
#include <iostream>

bool Lexer::isOperator(std::string seq)
{
    for (std::string a : _basic_operators)
    {
        if (a == seq)
        {
            return true;
        }
    }

    return false;
}

std::vector<Lexem> Lexer::parse(std::string filename)
{
    std::vector<Lexem> result;
    Tokenizer tokenizer(filename);
    mTokens = tokenizer.tokenize();
    
    std::string content = "";
    std::regex regBlank("\\s*");
    bool pushed;

    while (mTokens.size() != 0)
    {
        pushed = false;
        content = nextContent(mTokens);

        if (std::regex_match(content, regBlank))
        {
            continue;
        }

        for (auto it = _registered_regexes.begin(); it != _registered_regexes.end() && !pushed; ++it)
        {
            LexemType currentType = (*it).first;
            std::regex currentRegex = (*it).second;

            if (std::regex_match(content, currentRegex))
            {
                Lexem lexem(currentType, content);
                result.push_back(lexem);

                pushed = true;
            }
        }

        if (!pushed)
        {
            Lexem lexem(LexemType::Error, content);

            result.push_back(lexem); 
        }
    }

    return result;
}

std::string Lexer::nextContent(std::queue<Token>& tokens)
{
    std::string result;
    
    if (tokens.size() > 0)
    {
        std::string currentToken = tokens.front().getContent();
        result += currentToken;
        tokens.pop();

        if (isOperator(currentToken))
        {
            while (tokens.size() > 0)
            {
                if (!isOperator(tokens.front().getContent()))
                {
                    break;
                }

                currentToken = tokens.front().getContent();
                tokens.pop();
                result += currentToken;
            }

            return result;
        }

        if (currentToken == "\"")
        {
            while (tokens.size() > 0)
            {
                currentToken = tokens.front().getContent();
                tokens.pop();

                if (currentToken == "\"" && result.back() != '\\')
                {
                    result += currentToken;
                    break;
                }

                result += currentToken;
            }

            return result;
        }

        if (currentToken == "\'")
        {
            while (tokens.size() > 0)
            {
                currentToken = tokens.front().getContent();
                tokens.pop();

                if (currentToken == "\'" && result.back() != '\\')
                {
                    result += currentToken;
                    break;
                }

                result += currentToken;
            }

            return result;
        }

        if (currentToken == "#")
        {
            while (tokens.size() > 0)
            {
                currentToken = tokens.front().getContent();
                tokens.pop();

                if (currentToken == "\n")
                {
                    break;
                }

                result += currentToken;
            }

            return result;
        }

        if (currentToken == "/*")
        {
            while (tokens.size() > 0)
            {
                currentToken = tokens.front().getContent();
                tokens.pop();
                result += currentToken;

                if (currentToken == "*/")
                {
                    break;
                }
            }

            return result;
        }

        if (currentToken == "//")
        {
            std::cout << "I am here!" << std::endl;
            while (tokens.size() > 0)
            {
                currentToken = tokens.front().getContent();
                tokens.pop();
                if (currentToken == "\n")
                {
                    break;
                }
                result += currentToken;
            }

            return result;
        }
    }

    return result;
}