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
    STRING, // 0
    NUMBER, // 1
    BOOL, // 2
    NULL_, // 3
    LEFT_BRACE, // 4
    RIGHT_BRACE, // 5
    LEFT_SB, // 6 SB square bracket
    RIGHT_SB, // 7
    COMMA, // 8
    COLON, // 9
    EPS, // 10 epsilon
    END // 11 $
};

// non-terminal
enum class NonTml_t {
    START, // 0
    OBJECT, // 1
    OBJECT_, // 2
    MEMBERS, // 3
    MEMBERS_, // 4
    PAIR, // 5
    ARRAY ,// 6
    ARRAY_, // 7
    ELEMENTS, //8 
    ELEMENTS_, //9 
    VALUE, // 10
    COMMA, // 11
    COLON, // 12
    L_SB, // 13
    R_SB, // 14
    L_BR, // 15
    R_BR, // 16
    END // $ 17
};

inline std::string tktype_2_str(Token_t tk) {
    switch (tk) {
        case Token_t::STRING:
            return "STRING";
        case Token_t::NUMBER:
            return "NUMBER";
        case Token_t::BOOL:
            return "BOOL";
        case Token_t::NULL_:
            return "NULL_";
        case Token_t::LEFT_BRACE:
            return "LEFT_BRACE";
        case Token_t::RIGHT_BRACE:
            return "RIGHT_BRACE";
        case Token_t::LEFT_SB:
            return "LEFT_SB";
        case Token_t::RIGHT_SB:
            return "RIGHT_SB";
        case Token_t::COMMA:
            return "COMMA";
        case Token_t::COLON:
            return "COLON";
        case Token_t::EPS:
            return "EPS";
        case Token_t::END:
            return "END";
    }

    return "INVALID";
}

inline std::string nontml_2_str(NonTml_t nt) {
    switch (nt) {
        case NonTml_t::START:
            return "START";
        case NonTml_t::OBJECT:
            return "OBJECT";
        case NonTml_t::OBJECT_:
            return "OBJECT_";
        case NonTml_t::MEMBERS:
            return "MEMBERS";
        case NonTml_t::MEMBERS_:
            return "MEMBERS_";
        case NonTml_t::PAIR:
            return "PAIR";
        case NonTml_t::ARRAY:
            return "ARRAY";
        case NonTml_t::ARRAY_:
            return "ARRAY_";
        case NonTml_t::ELEMENTS:
            return "ELEMENTS";
        case NonTml_t::ELEMENTS_:
            return "ELEMENTS_";
        case NonTml_t::VALUE:
            return "VALUE";
        case NonTml_t::COMMA:
            return "COMMA";
        case NonTml_t::COLON:
            return "COLON";
        case NonTml_t::L_SB:
            return "L_SB";
        case NonTml_t::R_SB:
            return "R_SB";
        case NonTml_t::L_BR:
            return "L_BR";
        case NonTml_t::R_BR:
            return "R_BR";
        case NonTml_t::END:
            return "END";
    }

    return "INVALID";
}

} // namespace json_parser

#endif