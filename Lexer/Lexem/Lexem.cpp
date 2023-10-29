#include "Lexem.h"

std::string Lexem::getContent() const
{
    return mContent;
}

LexemType Lexem::getType() const
{
    return mType;
}

std::ostream& operator<<(std::ostream& stream, const Lexem& lexem)
{
    return stream << "Lexem content: " << lexem.getContent() << " Lexem type: " << lexem._type_mapping.at(lexem.getType());
}