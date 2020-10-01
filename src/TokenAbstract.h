#ifndef TOKEN_ABSTRACT
#define TOKEN_ABSTRACT

#include "types.h"

namespace json_parser {

// TODO complete it
class TokenAbstract {
public:
    virtual ~TokenAbstract() = default;

    virtual const Token get_token_type() = 0;
};

}

#endif
