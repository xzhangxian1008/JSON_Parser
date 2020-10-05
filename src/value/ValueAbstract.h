#ifndef VALUE_ABSTRACT
#define VALUE_ABSTRACT

#include "src/types.h"

namespace json_parser {

class OBJECTNonTml;
class ARRAYNonTml;

union Values {
    std::string str;
    long num;
    bool b;
    OBJECTNonTml *object;
    ARRAYNonTml *array;
    Values() { object = nullptr; array = nullptr; }
    Values(const std::string &s) : str(s) { object = nullptr; array = nullptr; }
    Values(const long num_) : num(num_) { object = nullptr; array = nullptr; }
    Values(const bool b_) : b(b_)  { object = nullptr; array = nullptr; }
    Values(OBJECTNonTml *const object_) : object(object_) { array = nullptr; }
    Values(ARRAYNonTml *const array_) : array(array_) { object = nullptr; }
    ~Values() {}
};

class ValueAbstract {
public:
    ValueAbstract(const std::string &str) : value(str), vt(Value_t::STRING) {}

    ValueAbstract(const long num_) : value(num_), vt(Value_t::NUMBER) {}

    ValueAbstract(const bool b_) : value(b_), vt(Value_t::BOOL) {}

    ValueAbstract(OBJECTNonTml *const object) : value(object), vt(Value_t::OBJECT) {}

    ValueAbstract(ARRAYNonTml *const array) : value(array), vt(Value_t::ARRAY) {}

    ValueAbstract() : value(), vt(Value_t::NULL_) {}
    
    virtual ~ValueAbstract() {}

    const Value_t get_value_t() const { return vt; }
protected:
    const Values& get_value_() const { return value; }
private:
    Values value;

    Value_t vt;
};

} // json_parser

#endif