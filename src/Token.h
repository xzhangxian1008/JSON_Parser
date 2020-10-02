#ifndef TOKEN
#define TOKEN

#include "TokenAbstract.h"

namespace json_parser {

class StringToken : public TokenAbstract {

};

class NumberToken : public TokenAbstract {

};

class BoolToken : public TokenAbstract {

};

class NullToken : public TokenAbstract {

};

class LeftBraceToken : public TokenAbstract {

};

class RightBraceToken : public TokenAbstract {

};

class LeftSQToken : public TokenAbstract {

};

class RightSQToken : public TokenAbstract {

};

class CommaToken : public TokenAbstract {

};

class ColonToken : public TokenAbstract {

};

class EpsToken : public TokenAbstract {

};

} // namespace json_parser

#endif