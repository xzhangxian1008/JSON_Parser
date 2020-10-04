#ifndef _VALUE_
#define _VALUE_

#include "src/value/ValueAbstract.h"

namespace json_parser {

class StringValue : public ValueAbstract {
public:
    StringValue(const std::string &str, const Value_t vt) : ValueAbstract(str, vt) {}

    std::string get_value() const {
        return get_value_().str;
    }
};

class NumberValue : public ValueAbstract {
public:
    NumberValue(const long num, const Value_t vt) : ValueAbstract(num, vt) {}

    long get_value() const {
        return get_value_().num;
    }
};

class BoolValue : public ValueAbstract {
public:
    BoolValue(const bool b, const Value_t vt) : ValueAbstract(b, vt) {}

    bool get_value() const {
        return get_value_().b;
    }
};

class NullValue : public ValueAbstract {
public:
    NullValue(const Value_t vt) : ValueAbstract(vt) {}
};

class ObjectValue : public ValueAbstract {
public:
    ObjectValue(OBJECTNonTml *const object, const Value_t vt) : ValueAbstract(object, vt) {}

    const OBJECTNonTml* get_value() const {
        return get_value_().object;
    }
};

class ArrayValue : public ValueAbstract {
public:
    ArrayValue(ARRAYNonTml *const array, const Value_t vt) : ValueAbstract(array, vt) {}

    const ARRAYNonTml* get_value() const {
        return get_value_().array;
    }
};

} // json_parser

#endif