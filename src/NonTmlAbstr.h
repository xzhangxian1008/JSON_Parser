#ifndef NON_TML_ABSTR
#define NON_TML_ABSTR

#include "types.h"

namespace json_parser {

// TODO complete it
// NonTerminalAbstract
class NonTmlAbstr {
public:
    virtual ~NonTmlAbstr() = default;

    virtual const NonTml_t get_non_tml_type() = 0;
private:
};

} // namespace json_parser

#endif