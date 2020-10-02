#ifndef TOKEN
#define TOKEN

#include "TokenAbstract.h"

namespace json_parser {

class StringToken : public TokenAbstract {
public:
    StringToken(const std::string &str) : TokenAbstract(str, Token_t::STRING) {}

    const bool get_token_data(TkData &data_) const override {
        data_.str = data.str;
        return true;
    }

    const bool operator==(const TokenAbstract &ta) const override {
        if (token_t != ta.get_token_type()) {
            return false;
        }

        TkData tk_data;
        ta.get_token_data(tk_data);

        if (tk_data.str == data.str) {
            return true;
        }

        return false;
    }
};

class NumberToken : public TokenAbstract {
public:
    NumberToken(const long num) : TokenAbstract(num, Token_t::NUMBER) {}

    const bool get_token_data(TkData &data_) const override {
        data_.num = data.num;
        return true;
    }

    const bool operator==(const TokenAbstract &ta) const override {
        if (token_t != ta.get_token_type()) {
            return false;
        }

        TkData tk_data;
        ta.get_token_data(tk_data);

        if (tk_data.num == data.num) {
            return true;
        }

        return false;
    }
};

class BoolToken : public TokenAbstract {
public:
    BoolToken(const bool b) : TokenAbstract(b, Token_t::BOOL) {}

    const bool get_token_data(TkData &data_) const override {
        data_.b = data.b;
        return true;
    }

    const bool operator==(const TokenAbstract &ta) const override {
        if (token_t != ta.get_token_type()) {
            return false;
        }

        TkData tk_data;
        ta.get_token_data(tk_data);

        if (tk_data.b == data.b) {
            return true;
        }
        
        return false;
    }      
};

class NullToken : public TokenAbstract {
public:
    NullToken() : TokenAbstract(Token_t::NULL_) {}

    const bool get_token_data(TkData &data_) const override {
        return false;
    }

    const bool operator==(const TokenAbstract &ta) const override {
        if (token_t != ta.get_token_type()) {
            return false;
        }
        return true;
    }
};

class LeftBraceToken : public TokenAbstract {
public:
    LeftBraceToken() : TokenAbstract(Token_t::LEFT_BRACE) {}

    const bool get_token_data(TkData &data_) const override {
        return false;
    }

    const bool operator==(const TokenAbstract &ta) const override {
        if (token_t != ta.get_token_type()) {
            return false;
        }
        return true;
    }
};

class RightBraceToken : public TokenAbstract {
public:
    RightBraceToken() : TokenAbstract(Token_t::RIGHT_BRACE) {}

    const bool get_token_data(TkData &data_) const override {
        return false;
    }

    const bool operator==(const TokenAbstract &ta) const override {
        if (token_t != ta.get_token_type()) {
            return false;
        }
        return true;
    }
};

class LeftSBToken : public TokenAbstract {
public:
    LeftSBToken() : TokenAbstract(Token_t::LEFT_SB) {}

    const bool get_token_data(TkData &data_) const override {
        return false;
    }

    const bool operator==(const TokenAbstract &ta) const override {
        if (token_t != ta.get_token_type()) {
            return false;
        }
        return true;
    }
};

class RightSBToken : public TokenAbstract {
public:
    RightSBToken() : TokenAbstract(Token_t::RIGHT_SB) {}

    const bool get_token_data(TkData &data_) const override {
        return false;
    }

    const bool operator==(const TokenAbstract &ta) const override {
        if (token_t != ta.get_token_type()) {
            return false;
        }
        return true;
    }
};

class CommaToken : public TokenAbstract {
public:
    CommaToken() : TokenAbstract(Token_t::COMMA) {}

    const bool get_token_data(TkData &data_) const override {
        return false;
    }

    const bool operator==(const TokenAbstract &ta) const override {
        if (token_t != ta.get_token_type()) {
            return false;
        }
        return true;
    }
};

class ColonToken : public TokenAbstract {
public:
    ColonToken() : TokenAbstract(Token_t::COLON) {}

    const bool get_token_data(TkData &data_) const override {
        return false;
    }

    const bool operator==(const TokenAbstract &ta) const override {
        if (token_t != ta.get_token_type()) {
            return false;
        }
        return true;
    }
};

class EpsToken : public TokenAbstract {
public:
    EpsToken() : TokenAbstract(Token_t::EPS) {}

    const bool get_token_data(TkData &data_) const override {
        return false;
    }

    const bool operator==(const TokenAbstract &ta) const override {
        if (token_t != ta.get_token_type()) {
            return false;
        }
        return true;
    }
};

class EndToken : public TokenAbstract {
public:
    EndToken() : TokenAbstract(Token_t::END) {}

    const bool get_token_data(TkData &data_) const override {
        return false;
    }

    const bool operator==(const TokenAbstract &ta) const override {
        if (token_t != ta.get_token_type()) {
            return false;
        }
        return true;
    }
};

} // namespace json_parser

#endif