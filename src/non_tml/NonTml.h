#ifndef NON_TML
#define NON_TML

#include "src/non_tml/NonTmlAbstr.h"
#include "src/value/ValueAbstract.h"

#include <map>
#include <vector>
#include <memory>

namespace json_parser {

class OBJECTNonTml : public NonTmlAbstr {
public:
    OBJECTNonTml() : NonTmlAbstr(NonTml_t::OBJECT) {}

    ~OBJECTNonTml() override {}

    void put(const std::string key, ValueAbstract *const value) { 
        pairs.emplace(key, std::unique_ptr<ValueAbstract>(value));
    }

    const ValueAbstract* get(const std::string key) const {
        auto iter = pairs.find(key);
        if (iter == pairs.end()) {
            return nullptr;
        }

        return iter->second.get();
    }

private:
    std::map<std::string, std::unique_ptr<ValueAbstract>> pairs;
};

class OBJECT_NonTml : public NonTmlAbstr {
public:
    OBJECT_NonTml() : NonTmlAbstr(NonTml_t::OBJECT_) {}
};

class ARRAYNonTml : public NonTmlAbstr {
public:
    ARRAYNonTml() : NonTmlAbstr(NonTml_t::ARRAY) {}

    ~ARRAYNonTml() override {}

    void push(ValueAbstract *const value) { 
        array.push_back(std::unique_ptr<ValueAbstract>(value));
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
};

class MEMBERSNonTml : public NonTmlAbstr {
public:
    MEMBERSNonTml() : NonTmlAbstr(NonTml_t::MEMBERS) {}
};

class MEMBERS_NonTml : public NonTmlAbstr {
public:
    MEMBERS_NonTml() : NonTmlAbstr(NonTml_t::MEMBERS_) {}
};

class PAIRNonTml : public NonTmlAbstr {
public:
    PAIRNonTml() : NonTmlAbstr(NonTml_t::PAIR) {}
};

class ELEMENTSNonTml : public NonTmlAbstr {
public:
    ELEMENTSNonTml() : NonTmlAbstr(NonTml_t::ELEMENTS) {}
};

class ELEMENTS_NonTml : public NonTmlAbstr {
public:
    ELEMENTS_NonTml() : NonTmlAbstr(NonTml_t::ELEMENTS_) {}
};

class VALUENonTml : public NonTmlAbstr {
public:
    VALUENonTml() : NonTmlAbstr(NonTml_t::VALUE) {}
};

class COMMANonTml : public NonTmlAbstr {
public:
    COMMANonTml() : NonTmlAbstr(NonTml_t::COMMA) {}
};

class COLONNonTml : public NonTmlAbstr {
public:
    COLONNonTml() : NonTmlAbstr(NonTml_t::COLON) {}
};

class L_SBNonTml : public NonTmlAbstr {
public:
    L_SBNonTml() : NonTmlAbstr(NonTml_t::L_SB) {}
};

class R_SBNonTml : public NonTmlAbstr {
public:
    R_SBNonTml() : NonTmlAbstr(NonTml_t::R_SB) {}
};

class L_BRNonTml : public NonTmlAbstr {
public:
    L_BRNonTml() : NonTmlAbstr(NonTml_t::L_BR) {}
};

class R_BRNonTml : public NonTmlAbstr {
public:
    R_BRNonTml() : NonTmlAbstr(NonTml_t::R_BR) {}
};

class EndNonTml : public NonTmlAbstr {
public:
    EndNonTml() : NonTmlAbstr(NonTml_t::END) {}
};

class TokenNonTml : public NonTmlAbstr {
public:
    TokenNonTml(Token_t tk_) : NonTmlAbstr(NonTml_t::Token), tk(tk_) {}

    const Token_t get_token_t() { return tk;  }
private:
    Token_t tk;
};

} // namespace json_parser

#endif