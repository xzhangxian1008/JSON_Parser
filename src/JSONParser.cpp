#include "JSONParser.h"
#include "src/non_tml/NonTml.h"

// TODO don't forget object_stk and array_stk when pop NonTmls!
// NOTICE code push operation firstly, then it's pop's turn

namespace json_parser {

JSONParser::JSONParser(const std::string &parse_target_, bool str_or_file_) 
    : parse_target(parse_target_), str_or_file(str_or_file_), pt_length(parse_target.size()) {
    non_tml_stack.push(std::unique_ptr<EndNonTml>());
    non_tml_stack.push(std::unique_ptr<OBJECTNonTml>());
}

bool JSONParser::semantic_analysis() {
    while (non_tml_stack.size()) {
        NonTmlAbstr *non_tml = non_tml_stack.top().get();
        NonTml_t nt = non_tml->get_non_tml_type();
        if (nt == NonTml_t::Token) {
            TokenNonTml *tnt;
            if (typeid(TokenNonTml) == typeid(*non_tml)) {
                // ensure the type is right
                tnt = dynamic_cast<TokenNonTml*>(non_tml);
            } else {
                std::cout << "TYPE INVALID!!!" << std::endl;
                exit(-1);
            }
            
            // compare
            if (tnt->get_token_t() != token_deque.front()->get_token_type()) {
                return false;
            }

            token_deque.pop_front();
            non_tml_stack.pop();
            continue;
        }

        do_production();
    }
}

/**
 * do production according to the production table
 */
bool JSONParser::do_production() {
    NonTml_t nt = non_tml_stack.top()->get_non_tml_type();

    switch (nt) {
        case NonTml_t::START:
            return do_START();
        case NonTml_t::OBJECT:
            return do_OBJECT();
        case NonTml_t::OBJECT_:
            return do_OBJECT_();
        case NonTml_t::MEMBERS:
            return do_MEMBERS();
        case NonTml_t::MEMBERS_:
            return do_MEMBERS_();
        case NonTml_t::PAIR:
            return do_PAIR();
        case NonTml_t::ARRAY:
            return do_ARRAY();
        case NonTml_t::ARRAY_:
            return do_ARRAY_();
        case NonTml_t::ELEMENTS:
            return do_ELEMENTS();
        case NonTml_t::ELEMENTS_:
            return do_ELEMENTS_();
        case NonTml_t::VALUE:
            return do_VALUE();
        case NonTml_t::COMMA:
            return do_COMMA();
        case NonTml_t::COLON:
            return do_COLON();
        case NonTml_t::L_SB:
            return do_L_SB();
        case NonTml_t::R_SB:
            return do_R_SB();
        case NonTml_t::L_BR:
            return do_L_BR();
        case NonTml_t::R_BR:
            return do_R_BR();
        case NonTml_t::END:
            return do_END();
        default:
            return false;
    }
}

bool JSONParser::do_START() {
    non_tml_stack.pop();
    non_tml_stack.push(std::unique_ptr<NonTmlAbstr>(new OBJECTNonTml));
    return true;
}

bool JSONParser::do_OBJECT() {
    Token_t tk = token_deque.front()->get_token_type();
    if (tk != Token_t::LEFT_BRACE) {
        return false;
    }

    non_tml_stack.pop();
    non_tml_stack.push(std::unique_ptr<NonTmlAbstr>(new OBJECT_NonTml));
    non_tml_stack.push(std::unique_ptr<NonTmlAbstr>(new L_BRNonTml));
    return true;
}

bool JSONParser::do_OBJECT_() {
    Token_t tk = token_deque.front()->get_token_type();

    switch (tk) {
        case Token_t::STRING:
            non_tml_stack.pop();
            non_tml_stack.push(std::unique_ptr<NonTmlAbstr>(new R_BRNonTml));
            if (object_stk.size() == 0) { object_stk.push(new OBJECTNonTml); }
            // object_lct_stk.push(non_tml_stack.size());
            sel_stk.push(true);
            non_tml_stack.push(std::unique_ptr<NonTmlAbstr>(new MEMBERSNonTml));
            return true;
        case Token_t::RIGHT_BRACE:
            non_tml_stack.pop();
            non_tml_stack.push(std::unique_ptr<NonTmlAbstr>(new R_BRNonTml));
            return true;
    }

    return false;
}

bool JSONParser::do_MEMBERS() {
    Token_t tk = token_deque.front()->get_token_type();
    if (tk != Token_t::STRING) {
        return false;
    }

    non_tml_stack.pop();
    non_tml_stack.push(std::unique_ptr<NonTmlAbstr>(new MEMBERS_NonTml));
    non_tml_stack.push(std::unique_ptr<NonTmlAbstr>(new PAIRNonTml));
    return true;
}

bool JSONParser::do_MEMBERS_() {
    Token_t tk = token_deque.front()->get_token_type();

    switch (tk) {
        case Token_t::RIGHT_BRACE:
            non_tml_stack.pop();
            return true;
        case Token_t::COMMA:
            non_tml_stack.pop();
            non_tml_stack.push(std::unique_ptr<NonTmlAbstr>(new MEMBERSNonTml));
            non_tml_stack.push(std::unique_ptr<NonTmlAbstr>(new COMMANonTml));
            return true;
    }

    return false;
}

bool JSONParser::do_PAIR() {
    Token_t tk = token_deque.front()->get_token_type();

    if (tk != Token_t::STRING) {
        return false;
    }

    non_tml_stack.pop();
    non_tml_stack.push(std::unique_ptr<NonTmlAbstr>(new VALUENonTml));
    non_tml_stack.push(std::unique_ptr<NonTmlAbstr>(new COLONNonTml));
    non_tml_stack.push(std::unique_ptr<NonTmlAbstr>(new TokenNonTml(Token_t::STRING)));
    return true;
}

bool JSONParser::do_ARRAY() {
    Token_t tk = token_deque.front()->get_token_type();

    if (tk != Token_t::LEFT_SB) {
        return false;
    }

    non_tml_stack.pop();
    non_tml_stack.push(std::unique_ptr<NonTmlAbstr>(new ARRAY_NonTml));
    non_tml_stack.push(std::unique_ptr<NonTmlAbstr>(new L_SBNonTml));
    return true;
}

bool JSONParser::do_ARRAY_() {
    Token_t tk = token_deque.front()->get_token_type();

    if (tk == Token_t::STRING || tk == Token_t::NUMBER || tk == Token_t::BOOL ||
        tk == Token_t::NULL_ || tk == Token_t::LEFT_SB || tk == Token_t::LEFT_BRACE) {
        non_tml_stack.pop();
        non_tml_stack.push(std::unique_ptr<NonTmlAbstr>(new R_SBNonTml));
        // array_lct_stk.push(array_stk.size());
        sel_stk.push(false);
        non_tml_stack.push(std::unique_ptr<NonTmlAbstr>(new ELEMENTSNonTml));
        return true;
    } else if (tk == Token_t::RIGHT_SB) {
        non_tml_stack.pop();
        non_tml_stack.push(std::unique_ptr<NonTmlAbstr>(new R_SBNonTml));
        return true;
    }

    return false;
}

bool JSONParser::do_ELEMENTS() {
    Token_t tk = token_deque.front()->get_token_type();
    if (tk == Token_t::STRING || tk == Token_t::NUMBER || tk == Token_t::BOOL ||
        tk == Token_t::NULL_ || tk == Token_t::LEFT_SB || tk == Token_t::LEFT_BRACE) {
        non_tml_stack.pop();
        non_tml_stack.push(std::unique_ptr<NonTmlAbstr>(new ELEMENTS_NonTml));
        non_tml_stack.push(std::unique_ptr<NonTmlAbstr>(new VALUENonTml));
        return true;
    }

    return false;
}

bool JSONParser::do_ELEMENTS_() {
    Token_t tk = token_deque.front()->get_token_type();
    if (tk == Token_t::RIGHT_SB) {
        non_tml_stack.pop();
        return true;
    } else if (tk == Token_t::COMMA) {
        non_tml_stack.pop();
        non_tml_stack.push(std::unique_ptr<NonTmlAbstr>(new ELEMENTSNonTml));
        non_tml_stack.push(std::unique_ptr<NonTmlAbstr>(new COMMANonTml));
        return true;
    }

    return false;
}

bool JSONParser::do_VALUE() {
    bool sel = sel_stk.top();
    OBJECTNonTml *object = object_stk.top();
    ARRAYNonTml *array = array_stk.top();
    TokenAbstract *tka = token_deque.front().get();
    Token_t tk = tka->get_token_type();
    TkData data;

    // pop VALUE non-terminal
    non_tml_stack.pop();
    
    switch (tk) {
        case Token_t::STRING:
            if (!tka->get_token_data(data)) { return false; }
            if (sel) { object->put(tmp_str, new StringValue(data.str)); } 
            else { array->push(new StringValue(data.str)); }
        case Token_t::NUMBER:
            if (!tka->get_token_data(data)) { return false; }
            if (sel) { object->put(tmp_str, new NumberValue(data.num)); } 
            else { array->push(new NumberValue(data.num)); }
        case Token_t::BOOL:
            if (!tka->get_token_data(data)) { return false; }
            if (sel) { object->put(tmp_str, new BoolValue(data.b)); } 
            else { array->push(new BoolValue(data.b)); }
        case Token_t::NULL_:
            if (sel) { object->put(tmp_str, new NullValue()); }
            else { array->push(new NullValue()); }
        case Token_t::LEFT_BRACE:
            if (sel) {
                OBJECTNonTml *obj = new OBJECTNonTml();
                object_stk.push(obj);
                object->put(tmp_str, new ObjectValue(obj));
            } else {
                ARRAYNonTml *ary = new ARRAYNonTml();
                array_stk.push(ary);
                array->push(new ArrayValue(ary));
            }
            non_tml_stack.push(std::unique_ptr<NonTmlAbstr>(new OBJECTNonTml));
        case Token_t::LEFT_SB:
            if (sel) {
                OBJECTNonTml *obj = new OBJECTNonTml();
                object_stk.push(obj);
                object->put(tmp_str, new ObjectValue(obj));
            } else {
                ARRAYNonTml *ary = new ARRAYNonTml();
                array_stk.push(ary);
                array->push(new ArrayValue(ary));
            }
            non_tml_stack.push(std::unique_ptr<NonTmlAbstr>(new ARRAYNonTml));
        default:
            return false;
    }

    token_deque.pop_front();
    return true;
}

bool JSONParser::do_COMMA() {
    Token_t tk = token_deque.front()->get_token_type();
    if (tk != Token_t::COMMA) {
        return false;
    }

    non_tml_stack.pop();
    non_tml_stack.push(std::unique_ptr<NonTmlAbstr>(new TokenNonTml(Token_t::COMMA)));
    return true;
}

bool JSONParser::do_COLON() {
    Token_t tk = token_deque.front()->get_token_type();
    if (tk != Token_t::COLON) {
        return false;
    }

    non_tml_stack.pop();
    non_tml_stack.push(std::unique_ptr<NonTmlAbstr>(new TokenNonTml(Token_t::COLON)));
    return true;
}

bool JSONParser::do_L_SB() {
    Token_t tk = token_deque.front()->get_token_type();
    if (tk != Token_t::LEFT_SB) {
        return false;
    }

    non_tml_stack.pop();
    non_tml_stack.push(std::unique_ptr<NonTmlAbstr>(new TokenNonTml(Token_t::LEFT_SB)));
    return true;
}

bool JSONParser::do_R_SB() {
    Token_t tk = token_deque.front()->get_token_type();
    if (tk != Token_t::RIGHT_SB) {
        return false;
    }

    // NOTICE *for debug*
    if (sel_stk.top() != false) {
        std::cout << "INVALID IN do_R_SB" << std::endl;
        exit(-1);
    }

    sel_stk.pop();
    ap_dq.push_back(array_stk.top());
    array_stk.pop();

    non_tml_stack.pop();
    non_tml_stack.push(std::unique_ptr<NonTmlAbstr>(new TokenNonTml(Token_t::RIGHT_SB)));
    return true;
}

bool JSONParser::do_L_BR() {
    Token_t tk = token_deque.front()->get_token_type();
    if (tk != Token_t::LEFT_BRACE) {
        return false;
    }

    non_tml_stack.pop();
    non_tml_stack.push(std::unique_ptr<NonTmlAbstr>(new TokenNonTml(Token_t::LEFT_BRACE)));
    return true;
}

bool JSONParser::do_R_BR() {
    Token_t tk = token_deque.front()->get_token_type();
    if (tk != Token_t::RIGHT_BRACE) {
        return false;
    }

    // NOTICE *for debug*
    if (sel_stk.top() != true) {
        std::cout << "INVALID IN do_R_BR" << std::endl;
        exit(-1);
    }

    sel_stk.pop();
    root_obj = object_stk.top();
    object_stk.pop();
    op_dq.push_back(root_obj);

    non_tml_stack.pop();
    non_tml_stack.push(std::unique_ptr<NonTmlAbstr>(new TokenNonTml(Token_t::RIGHT_BRACE)));
    return true;
}

bool JSONParser::do_END() {
    Token_t tk = token_deque.front()->get_token_type();
    if (tk != Token_t::END) {
        return false;
    }

    non_tml_stack.pop();
    non_tml_stack.push(std::unique_ptr<NonTmlAbstr>(new TokenNonTml(Token_t::END)));
    return true;
}

bool JSONParser::parse() {
    if (str_or_file) {
        if (!parse_string() || !semantic_analysis()) {
            return false;
        }

        return true;
    }

    if (!parse_file() || !semantic_analysis()) {
        return false;
    }
    return true;
}

bool JSONParser::parse_string() {
    /** do lexical analysis first */
    if (!lexical_analyze()) {
        return false;
    }

    return true;
}

bool JSONParser::lexical_analyze() {
    size_t index = 0;
    char c;
    
    for (; index < pt_length; ++index) {
        std::string str;
        c = parse_target[index];
        switch (c) {
            case '{':
                token_deque.emplace_back(std::unique_ptr<TokenAbstract>(new LeftBraceToken()));
                continue;
            case '}':
                token_deque.emplace_back(std::unique_ptr<TokenAbstract>(new RightBraceToken()));
                continue;
            case '[':
                token_deque.emplace_back(std::unique_ptr<TokenAbstract>(new LeftSBToken()));
                continue;
            case ']':
                token_deque.emplace_back(std::unique_ptr<TokenAbstract>(new RightSBToken()));
                continue;
            case ',':
                token_deque.emplace_back(std::unique_ptr<TokenAbstract>(new CommaToken()));
                continue;
            case ':':
                token_deque.emplace_back(std::unique_ptr<TokenAbstract>(new ColonToken()));
                continue;
            case '"':
                /** string */
                if (!search_string(str, ++index)) {
                    // std::cout << "INVALID JSON" << std::endl;
                    return false;
                }
                token_deque.emplace_back(std::unique_ptr<TokenAbstract>(new StringToken(str)));
                continue;
            case 'n':
                /** null */
                if (!search_null(index)) {
                    // std::cout << "INVALID JSON" << std::endl;
                    return false;
                }
                token_deque.emplace_back(std::unique_ptr<TokenAbstract>(new NullToken()));
                continue;
            default:
                break;
        }

        // number
        if (c >= '0' && c <= '9' || c == '-') {
            long val = 0;
            if (!search_num(index, val)) {
                // std::cout << "INVALID JSON" << std::endl;
                return false;
            }
            token_deque.emplace_back(std::unique_ptr<TokenAbstract>(new NumberToken(val)));
            continue;         
        }

        // bool
        if (c == 't' || c == 'f') {
            bool val;
            if (!search_bool(index, val)) {
                // std::cout << "INVALID JSON" << std::endl;
                return false;
            }
            token_deque.emplace_back(std::unique_ptr<TokenAbstract>(new BoolToken(val)));
            continue;
        }

        // ignore the blank, carriage return and line feed
        if (c == 10 || c == 13 || c == 32) {
            continue;
        }

        // std::cout << "INVALID JSON" << std::endl;
        return false;
    }

    // put the end notation
    token_deque.emplace_back(std::unique_ptr<TokenAbstract>(new EndToken()));
    return true;
}

// not support " in a string e.g. "str"ing"
// not support \\ in a string e.g. "s\\tr\"ing"
bool JSONParser::search_string(std::string &str, size_t &index) {
    // an empty string or single '"' at the end is invalid
    if (index >= pt_length || parse_target[index] == '"') {
        return false;
    }

    char c;
    while (index < pt_length) {
        c = parse_target[index];
        if (c == '"') {
            return true;
        }

        str += c;
        index++;
    }

    if (index >= pt_length) {
        return false;
    }
}

bool JSONParser::search_null(size_t &index) {
    if (index + 3 >= pt_length) {
        return false;
    }

    if (parse_target[index] == 'n' && parse_target[index + 1] == 'u' &&
        parse_target[index + 2] == 'l' && parse_target[index + 3] == 'l') {
        index += 3;
        return true;
    }

    return false;
}

bool JSONParser::search_bool(size_t &index, bool &val) {
    char c = parse_target[index];
    if (c == 't') {
        /** search true */
        if (index + 3 >= pt_length) {
            return false;
        }

        if (parse_target[index + 1] == 'r' && parse_target[index + 2] == 'u' &&
            parse_target[index + 3] == 'e') {
            index += 3;
            val = true;
            return true;
        }
    } else if (c == 'f') {
        /** search false */
        if (index + 4 >= pt_length) {
            return false;
        }

        if (parse_target[index + 1] == 'a' && parse_target[index + 2] == 'l' &&
            parse_target[index + 3] == 's' && parse_target[index + 4] == 'e') {
            index += 4;
            val = false;
            return true;
        }
    }

    return false;
}

// not support float so far, just integer.
bool JSONParser::search_num(size_t &index, long &val) {
    // used for the sign of the number
    long sign = 1;
    char c = parse_target[index];
    if (c == '-') {
        if (++index >= pt_length) {
            return false;
        }
        sign = -1;
        c = parse_target[index];
    }

    while (c >= '0' && c <= '9') {
        val = val * (sign*10) + sign * (c-48);
        ++index;
        if (index >= pt_length) {
            return false;
        }
        c = parse_target[index];
    }

    // relocate to the end of the number
    index--;

    return true;
}

bool JSONParser::parse_file() {
    
    return true;
}

} // namespace json_parser
