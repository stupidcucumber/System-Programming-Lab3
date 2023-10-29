#include "Token.h"

std::string Token::getContent() const
{
    return mContent;
}

TokenType Token::getType() const
{
    return mType;
}

std::ostream& operator<<(std::ostream& os, const Token& token)
{
    std::string content = token.getContent() == "\n" ? "\\n" : token.getContent();
    return os << "Content of the token: " << content << " Type of the token: " << token._type_mapping.at(token.getType());
}