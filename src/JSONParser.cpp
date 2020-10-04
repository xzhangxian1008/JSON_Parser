#include "JSONParser.h"
#include "src/non_tml/NonTml.h"

namespace json_parser {

JSONParser::JSONParser(const std::string &parse_target_, bool str_or_file_) 
    : parse_target(parse_target_), str_or_file(str_or_file_), pt_length(parse_target.size()) {
    non_tml_stack.push(std::unique_ptr<EndNonTml>());
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

bool JSONParser::semantic_analysis() {
    while (non_tml_stack.size()) {
        NonTml_t nt = non_tml_stack.top()->get_non_tml_type();
        if (nt == NonTml_t::Token) {
            // TODO compare Token_t
        }

        
    }
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
