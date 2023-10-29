#ifndef LEXEMTYPE_H 
#define LEXEMTYPE_H

enum LexemType
{
    Whole,          
    Float,
    Hexadecimal,    
    String,         
    Char,           
    Preprocessor,   
    Comment,        
    Reserved,
    Operator,
    Delimiter,
    Identifier,
    Error
};

#endif