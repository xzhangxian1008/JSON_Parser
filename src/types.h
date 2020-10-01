#ifndef TYPES
#define TYPES

namespace json_parser {

// Token == terminal
enum class Token {
    STRING,
    NUMBER,
    BOOL,
    NULL_,
    LEFT_BRACE,
    RIGHT_BRACE,
    LEFT_SB, // SB square bracket
    RIGHT_SB,
    COMMA,
    COLON,
    EPS, // epsilon
    END // $
};

// non-terminal
enum class NonTml {
    START,
    OBJECT,
    OBJECT_,
    MEMBERS,
    MEMBERS,
    PAIR,
    ARRAY,
    ARRAY_,
    ELEMENTS,
    ELEMENTS_,
    VALUE,
    COMMA,
    COLON,
    L_SB,
    R_SB,
    L_BR,
    R_BR,
    END // $
};

}

#endif