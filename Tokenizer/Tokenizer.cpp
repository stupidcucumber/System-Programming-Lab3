#include "Tokenizer.h"
#include <iostream>

Tokenizer::Tokenizer(std::string filename)
{
    mFile.open(filename);
}

Tokenizer::~Tokenizer()
{
    mFile.close();
}

std::queue<Token> Tokenizer::tokenize()
{
    std::queue<Token> tokens;

    while (!mFile.eof())
    {
        Token token = nextToken();

        tokens.push(token);

        mCurrentToken = "";
        mTokenType = TokenType::NONE;
    }
    
    return tokens;
}

Token Tokenizer::nextToken()
{
    char currentChar;
    bool end = false;

    while (!mFile.eof() && !end)
    {
        currentChar = mFile.get();

        if (mTokenType == TokenType::NONE)
        {
            end = handleNone(currentChar);
        }
        else if (mTokenType == TokenType::TERMINAL)
        {
            end = handleTerminal(currentChar);
        }
        else if (mTokenType == TokenType::NONTERMINAL)
        {
            end = handleNonterminal(currentChar);
        }
    }

    return Token(mTokenType, mCurrentToken, mMapping);
}

bool Tokenizer::handleNone(char currentChar)
{
    bool toEnd = false;

    char nextChar = mFile.peek();
    if (isalnum(currentChar) || currentChar == '_')
    {
        if (!(isalnum(nextChar) || nextChar == '_') || isDelimiter(nextChar))
        {
            mTokenType = TokenType::NONTERMINAL;
            toEnd = true;
        }
        else
        {
            mTokenType = TokenType::NONTERMINAL;
        }
    }
    else if (isDelimiter(currentChar))
    {
        mTokenType = TokenType::TERMINAL;
        toEnd = true;
    }
    else
    {
        if (isalnum(nextChar) || nextChar == '_' || isDelimiter(nextChar))
        {
            mTokenType = TokenType::TERMINAL;
            toEnd = true;
        }
        else
        {
            mTokenType  = TokenType::TERMINAL;
        }
    }
    
    mCurrentToken += currentChar;

    return toEnd;
}

bool Tokenizer::handleNonterminal(char currentChar)
{
    bool toEnd = false;

    char nextChar = mFile.peek();
    if (!(isalnum(nextChar) || nextChar == '_'))
    {
        toEnd = true;
    }
    mCurrentToken += currentChar;

    return toEnd;
}

bool Tokenizer::handleTerminal(char currentChar)
{
    bool toEnd = false;

    char nextChar = mFile.peek();
    if (isalnum(nextChar) || nextChar == '_' || isDelimiter(nextChar))
    {
        toEnd = true;
    }
    mCurrentToken += currentChar;

    return toEnd;
}

bool Tokenizer::isDelimiter(char currentChar)
{
    for (char delimiter : _delimiters)
    {
        if (delimiter == currentChar)
        {
            return true;
        }
    }

    return false;
}