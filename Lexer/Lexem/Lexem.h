#ifndef LEXEM_H
#define LEXEM_H

#include "LexemType.h"
#include <string>
#include <unordered_map>
#include <ostream>

class Lexem
{
    friend std::ostream& operator<<(std::ostream& stream, const Lexem& lexem);

    private:
        std::string mContent;
        LexemType mType;

        std::unordered_map<LexemType, std::string> _type_mapping = {
            {
                LexemType::Char, "Char"
            },
            {
                LexemType::Comment, "Comment"
            },
            {
                LexemType::Delimiter, "Delimiter"
            },
            {
                LexemType::Error, "Error"
            },
            {
                LexemType::String, "String"
            },
            {
                LexemType::Float, "Float"
            },
            {
                LexemType::Hexadecimal, "Hexadecimal"
            },
            {
                LexemType::Whole, "Whole"
            },
            {
                LexemType::Reserved, "Reserved"
            },
            {
                LexemType::Identifier, "Identifier"
            },
            {
                LexemType::Operator, "Operator"
            },
            {
                LexemType::Preprocessor, "Preprocessor"
            }
        };

    public:
        Lexem(LexemType type, std::string content) : mType(type), mContent(content)
        {}

        std::string getContent() const;
        LexemType getType() const;
};

#endif