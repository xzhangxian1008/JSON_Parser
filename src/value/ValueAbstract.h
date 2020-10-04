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
    ~Values() {
        // WARNING delete!!!
    }
};

class ValueAbstract {
public:
    ValueAbstract(const std::string &str, const Value_t vt_) : value(str), vt(vt_) {}

    ValueAbstract(const long num_, const Value_t vt_) : value(num_), vt(vt_) {}

    ValueAbstract(const bool b_, const Value_t vt_) : value(b_), vt(vt_) {}

    ValueAbstract(OBJECTNonTml *const object, const Value_t vt_) : value(object), vt(vt_) {}

    ValueAbstract(ARRAYNonTml *const array, const Value_t vt_) : value(array), vt(vt_) {}

    ValueAbstract(const Value_t vt_) : value(), vt(vt_) {}
    
    virtual ~ValueAbstract();

    const Value_t get_value_t() const { return vt; }
protected:
    const Values& get_value_() const { return value; }
private:
    Values value;

    Value_t vt;
};

} // json_parser

#endif