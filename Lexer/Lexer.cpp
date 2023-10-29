#include "Lexer.h"
#include <regex>
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

    while (mTokens.size() != 0)
    {
        bool pushed = false;
        content = nextContent(mTokens);

        std::regex regBlank("\\s*");

        if (std::regex_match(content, regBlank))
        {
            continue;
        }

        std::regex regString("\".*\"");
        std::regex regRegularChar("\'[^\\\\]?\'");
        std::regex regEscapeChar(R"(\'\\\S{1}\')");
        std::regex regWhole("^[0-9]+$");
        std::regex regFloat("[+-]?([0-9]+([.][0-9]*)?|[.][0-9]+)");
        std::regex regHex("0[xX][0-9a-fA-F]+");

        std::regex regCommentInline("^//.*");
        std::regex regCommentBlock("^/\\*[\\S\\n\\s]*\\*/");
        std::regex regPreprocessor("^#.*");
        std::regex regIdentifier("[a-zA-Z_][a-zA-Z0-9_]*");

        std::regex regOperator("==|-=|\\+=|/=|\\*=|&=|>=|<=|<<|>>|!|::|\\.|=|\\+|\\*|-|<|>");
        std::regex regDelimiter(";|\\{|\\}|\\(|\\)|\\[|\\]|\\s|,");

        if (std::regex_match(content, regString))
        {
            Lexem lexem(LexemType::String, content);

            result.push_back(lexem);
            pushed = true;
        }

        if (std::regex_match(content, regRegularChar) || std::regex_match(content, regEscapeChar))
        {
            Lexem lexem(LexemType::Char, content);
            result.push_back(lexem);
            pushed = true;
        }

        if (std::regex_match(content, regHex))
        {
            Lexem lexem(LexemType::Hexadecimal, content);

            result.push_back(lexem);
            pushed = true;
        }        
        
        if (std::regex_match(content, regWhole))
        {
            Lexem lexem(LexemType::Whole, content);

            result.push_back(lexem);
            pushed = true;
        }

        if (std::regex_match(content, regFloat))
        {
            Lexem lexem(LexemType::Float, content);

            result.push_back(lexem);
            pushed = true;
        }

        if (std::regex_match(content, regIdentifier))
        {
            Lexem lexem(LexemType::Identifier, content);

            result.push_back(lexem);
            pushed = true;
        }

        if (std::regex_match(content, regCommentInline) || std::regex_match(content, regCommentBlock))
        {
            Lexem lexem(LexemType::Comment, content);

            result.push_back(lexem);
            pushed = true;
        }

        if (std::regex_match(content, regPreprocessor))
        {
            Lexem lexem(LexemType::Preprocessor, content);

            result.push_back(lexem);
            pushed = true;
        }

        if (std::regex_match(content, regOperator))
        {
            Lexem lexem(LexemType::Operator, content);

            result.push_back(lexem);
            pushed = true;
        }

        if (std::regex_match(content, regDelimiter))
        {
            Lexem lexem(LexemType::Delimiter, content);

            result.push_back(lexem);
            pushed = true;
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