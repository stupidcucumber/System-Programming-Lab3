#ifndef TOKENTYPE_H
#define TOKENTYPE_H

enum TokenType
{
    NONE,
    TERMINAL,       // For Operators and Delimiters
    NONTERMINAL,    // For Identifiers, Numbers, Chars, Strings
    END             // End of token, deprecated
};

#endif