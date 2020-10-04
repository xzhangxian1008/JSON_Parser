#ifndef VALUE
#define VALUE

#include "src/value/ValueAbstract.h"

namespace json_parser {

class StringValue : public ValueAbstract {
public:
    StringValue(const std::string &str, const Value_t vt) : ValueAbstract(str, vt) {}

};

class NumberValue : public ValueAbstract {
public:
    NumberValue(const long num, const Value_t vt) : ValueAbstract(num, vt) {}

};

class BoolValue : public ValueAbstract {
public:
    BoolValue(const bool b, const Value_t vt) : ValueAbstract(b, vt) {}

};

class NullValue : public ValueAbstract {
public:
    NullValue(const Value_t vt) : ValueAbstract(vt) {}

};

class ObjectValue : public ValueAbstract {
public:


};

class ArrayValue : public ValueAbstract {
public:


};

} // json_parser

#endif