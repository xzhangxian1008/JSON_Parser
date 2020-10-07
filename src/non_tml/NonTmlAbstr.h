#ifndef NON_TML_ABSTR
#define NON_TML_ABSTR

#include "src/types.h"

namespace json_parser {

// NonTerminalAbstract
class NonTmlAbstr { 
public:
    NonTmlAbstr(const NonTml_t nt_) : nt(nt_) {}

    virtual ~NonTmlAbstr() = default;

    const NonTml_t get_non_tml_type() { return nt; }

private:
    NonTml_t nt;
};

} // namespace json_parser

#endif