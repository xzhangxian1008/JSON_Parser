#ifndef TYPES
#define TYPES

namespace json_parser {

union TkData {
    std::string str;
    long num;
    bool b;
    TkData() {}
    TkData(const std::string &s) : str(s) {}
    TkData(const long num_) : num(num_) {}
    TkData(const bool b_) : b(b_)  {}
    ~TkData() {}
};

// Token == terminal
enum class Token_t {
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
enum class NonTml_t {
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

} // namespace json_parser

#endif