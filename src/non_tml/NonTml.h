#ifndef NON_TML
#define NON_TML

#include "src/non_tml/NonTmlAbstr.h"
#include "src/value/ValueAbstract.h"

#include <map>
#include <vector>
#include <memory>

namespace json_parser {

class STARTNonTml : public NonTmlAbstr {
public:
    STARTNonTml() : NonTmlAbstr(NonTml_t::START) {}

    ~STARTNonTml() {}
};

class OBJECTNonTml : public NonTmlAbstr {
public:
    OBJECTNonTml() : NonTmlAbstr(NonTml_t::OBJECT) {}

    ~OBJECTNonTml() {}

    void put(const std::string key, ValueAbstract *const value) { 
        pairs.emplace(key, std::make_unique<ValueAbstract>(value));
    }

private:
    std::map<std::string, std::unique_ptr<ValueAbstract>> pairs;
};

class OBJECT_NonTml : public NonTmlAbstr {
public:
    OBJECT_NonTml() : NonTmlAbstr(NonTml_t::OBJECT_) {}

    ~OBJECT_NonTml() {}
};

class ARRAYNonTml : public NonTmlAbstr {
public:
    ARRAYNonTml() : NonTmlAbstr(NonTml_t::ARRAY) {}

    ~ARRAYNonTml() {}

    void push(ValueAbstract *const value) { 
        array.push_back(std::make_unique<ValueAbstract>(value));
    }

    const ValueAbstract* operator[](std::size_t i) const {
        return array[i].get();
    }

    ValueAbstract* operator[](std::size_t i) {
        return array[i].get();
    }

private:
    std::vector<std::unique_ptr<ValueAbstract>> array;
};

class ARRAY_NonTml : public NonTmlAbstr {
public:
    ARRAY_NonTml() : NonTmlAbstr(NonTml_t::ARRAY_) {}

    ~ARRAY_NonTml() {}
};

class MEMBERSNonTml : public NonTmlAbstr {
public:
    MEMBERSNonTml() : NonTmlAbstr(NonTml_t::MEMBERS) {}

    ~MEMBERSNonTml() {}
};

class MEMBERS_NonTml : public NonTmlAbstr {
public:
    MEMBERS_NonTml() : NonTmlAbstr(NonTml_t::MEMBERS_) {}

    ~MEMBERS_NonTml() {}
};

class PAIRNonTml : public NonTmlAbstr {
public:
    PAIRNonTml() : NonTmlAbstr(NonTml_t::PAIR) {}

    ~PAIRNonTml() {}
};

class ELEMENTSNonTml : public NonTmlAbstr {
public:
    ELEMENTSNonTml() : NonTmlAbstr(NonTml_t::ELEMENTS) {}

    ~ELEMENTSNonTml() {}
};

class ELEMENTS_NonTml : public NonTmlAbstr {
public:
    ELEMENTS_NonTml() : NonTmlAbstr(NonTml_t::ELEMENTS_) {}

    ~ELEMENTS_NonTml() {}
};

class VALUENonTml : public NonTmlAbstr {
public:
    VALUENonTml() : NonTmlAbstr(NonTml_t::VALUE) {}

    ~VALUENonTml() {}
};

class COMMANonTml : public NonTmlAbstr {
public:
    COMMANonTml() : NonTmlAbstr(NonTml_t::COMMA) {}

    ~COMMANonTml() {}
};

class COLONNonTml : public NonTmlAbstr {
public:
    COLONNonTml() : NonTmlAbstr(NonTml_t::COLON) {}

    ~COLONNonTml() {}
};

class L_SBNonTml : public NonTmlAbstr {
public:
    L_SBNonTml() : NonTmlAbstr(NonTml_t::L_SB) {}

    ~L_SBNonTml() {}
};

class R_SBNonTml : public NonTmlAbstr {
public:
    R_SBNonTml() : NonTmlAbstr(NonTml_t::R_SB) {}

    ~R_SBNonTml() {}
};

class L_BRNonTml : public NonTmlAbstr {
public:
    L_BRNonTml() : NonTmlAbstr(NonTml_t::L_BR) {}

    ~L_BRNonTml() {}
};

class R_BRNonTml : public NonTmlAbstr {
public:
    R_BRNonTml() : NonTmlAbstr(NonTml_t::R_BR) {}

    ~R_BRNonTml() {}
};

class EndNonTml : public NonTmlAbstr {
public:
    EndNonTml() : NonTmlAbstr(NonTml_t::END) {}

    ~EndNonTml() {}
};

class TokenNonTml : public NonTmlAbstr {
public:
    TokenNonTml(Token_t tk_) : NonTmlAbstr(NonTml_t::Token), tk(tk_) {}

    ~TokenNonTml() {}
private:
    Token_t tk;
};

} // namespace json_parser

#endif