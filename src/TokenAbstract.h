#ifndef TOKEN_ABSTRACT
#define TOKEN_ABSTRACT

#include <string>

#include "types.h"

namespace json_parser {

class TokenAbstract {
public:
    TokenAbstract(const std::string &str, Token_t tk) : data(str), token_t(tk) {}

    TokenAbstract(const long num_, Token_t tk) : data(num_), token_t(tk) {}

    TokenAbstract(const bool b_, Token_t tk) : data(b_), token_t(tk) {}

    TokenAbstract(Token_t tk) : data(), token_t(tk) {}

    virtual ~TokenAbstract() = default;

    virtual const Token_t get_token_type() = 0;
private:
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
    
    TkData data;

    Token_t token_t;
};

} // namespace json_parser

#endif
