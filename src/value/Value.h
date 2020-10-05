#ifndef _VALUE_
#define _VALUE_

#include "src/value/ValueAbstract.h"

namespace json_parser {

class StringValue : public ValueAbstract {
public:
    StringValue(const std::string &str) : ValueAbstract(str) {}

    std::string get_value() const {
        return get_value_().str;
    }
};

class NumberValue : public ValueAbstract {
public:
    NumberValue(const long num) : ValueAbstract(num) {}

    long get_value() const {
        return get_value_().num;
    }
};

class BoolValue : public ValueAbstract {
public:
    BoolValue(const bool b) : ValueAbstract(b) {}

    bool get_value() const {
        return get_value_().b;
    }
};

class NullValue : public ValueAbstract {
public:
    NullValue() : ValueAbstract() {}
};

class ObjectValue : public ValueAbstract {
public:
    ObjectValue(OBJECTNonTml *const object) : ValueAbstract(object) {}

    const OBJECTNonTml* get_value() const {
        return get_value_().object;
    }
};

class ArrayValue : public ValueAbstract {
public:
    ArrayValue(ARRAYNonTml *const array) : ValueAbstract(array) {}

    const ARRAYNonTml* get_value() const {
        return get_value_().array;
    }
};

} // json_parser

#endif