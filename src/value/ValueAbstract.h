#ifndef VALUE_ABSTRACT
#define VALUE_ABSTRACT

#include "src/types.h"

namespace json_parser {

class OBJECTNonTml;
class ARRAYNonTml;

/**
 * a strange bug:
 *   At the beginning, I put the std::string in the union Values to store string.
 *   There is no problem when cout string in union's constructor, but it will come across
 *   error when I cout the value.str int ValueAbstract's constructor where initialize
 *   the union.
 */
union Values {
    // std::string str // puzzling problem
    long num;
    bool b;
    OBJECTNonTml *object;
    ARRAYNonTml *array;
};

class ValueAbstract {
public:
    ValueAbstract(const std::string &str_) : str(str_), vt(Value_t::STRING) {}

    ValueAbstract(const long num_) : vt(Value_t::NUMBER) { value.num = num_; }

    ValueAbstract(const bool b_) : vt(Value_t::BOOL) { value.b = b_; }

    ValueAbstract(OBJECTNonTml *const object) : vt(Value_t::OBJECT) { value.object = object; }

    ValueAbstract(ARRAYNonTml *const array) : vt(Value_t::ARRAY) { value.array = array; }

    ValueAbstract() : value(), vt(Value_t::NULL_) {}
    
    virtual ~ValueAbstract() {}

    const Value_t get_value_t() const { return vt; }
protected:
    const Values* get_value_() const { return &value; }
    const std::string get_str() const { return str; }
private:
    Values value;
    std::string str;
    Value_t vt;
};

} // json_parser

#endif