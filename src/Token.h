#ifndef TOKEN
#define TOKEN

#include "TokenAbstract.h"

namespace json_parser {

class StringToken : public TokenAbstract {
public:
    StringToken(const std::string &str, Token_t tk) : TokenAbstract(str, tk) {}

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
    NumberToken(const long num, Token_t tk) : TokenAbstract(num, tk) {}

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
    BoolToken(const bool b, Token_t tk) : TokenAbstract(b, tk) {}

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
    NullToken(Token_t tk) : TokenAbstract(tk) {}

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
    LeftBraceToken(Token_t tk) : TokenAbstract(tk) {}

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
    RightBraceToken(Token_t tk) : TokenAbstract(tk) {}

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

class LeftSQToken : public TokenAbstract {
public:
    LeftSQToken(Token_t tk) : TokenAbstract(tk) {}

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

class RightSQToken : public TokenAbstract {
public:
    RightSQToken(Token_t tk) : TokenAbstract(tk) {}

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
    CommaToken(Token_t tk) : TokenAbstract(tk) {}

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
    ColonToken(Token_t tk) : TokenAbstract(tk) {}

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
    EpsToken(Token_t tk) : TokenAbstract(tk) {}

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