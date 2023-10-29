#ifndef TOKEN_H
#define TOKEN_H

#include "TokenType.h"
#include <string>
#include <ostream>
#include <unordered_map>

class Token
{
    friend std::ostream& operator<<(std::ostream& stream, const Token& token);
    private:
        TokenType mType;
        std::string mContent;
        const std::unordered_map<TokenType, std::string>& _type_mapping;

    public:
        Token(TokenType type, std::string content, const std::unordered_map<TokenType, std::string>& mapping) : mType(type), mContent(content), _type_mapping(mapping)
        {}

        std::string getContent() const;
        TokenType getType() const;
};


#endif