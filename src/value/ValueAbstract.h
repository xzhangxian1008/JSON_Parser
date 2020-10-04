#ifndef VALUE_ABSTRACT
#define VALUE_ABSTRACT

#include "src/types.h"

namespace json_parser {

class ValueAbstract {
public:
    ValueAbstract(const std::string &str, const Value_t vt_) : value(str), vt(vt_) {}

    ValueAbstract(const long num_, const Value_t vt_) : value(num_), vt(vt_) {}

    ValueAbstract(const bool b_, const Value_t vt_) : value(b_), vt(vt_) {}

    ValueAbstract(const Value_t vt_) : value(), vt(vt_) {}
    
    virtual ~ValueAbstract() = default;

    virtual const Value_t get_value_t() const = 0;

    virtual void set_value_t(Value_t vt_) = 0;

private:
    Values value;

    Value_t vt;
};

} // json_parser

#endif