#include "JSONParser.h"

namespace json_parser {

bool JSONParser::parse() {
    if (str_or_file) {
        return parse_string();
    }
    return parse_file();
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
        c = parse_target[index];
        std::string str;
        switch (c) {
            case '{':
                token_deque.emplace_back(std::unique_ptr<TokenAbstract>(new LeftBraceToken()));
                break;
            case '}':
                token_deque.emplace_back(std::unique_ptr<TokenAbstract>(new RightBraceToken()));
                break;
            case '[':
                token_deque.emplace_back(std::unique_ptr<TokenAbstract>(new LeftSBToken()));
                break;
            case ']':
                token_deque.emplace_back(std::unique_ptr<TokenAbstract>(new RightSBToken()));
                break;
            case ',':
                token_deque.emplace_back(std::unique_ptr<TokenAbstract>(new CommaToken()));
                break;
            case ':':
                token_deque.emplace_back(std::unique_ptr<TokenAbstract>(new ColonToken()));
                break;
            case '"':
                /** string */
                if (!search_string(str, ++index)) {
                    std::cout << "INVALID JSON" << std::endl;
                    return false;
                }
                token_deque.emplace_back(std::unique_ptr<TokenAbstract>(new StringToken(str)));
                break;
            case 'n':
                /** null */
                
                break;
            case 't':
                /** true */
                break;
            case 'f':
                /** false */
                break;
            default:
                break;
        }

        // number
        if (c >= '0' && c <= '9') {

        }
    }
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
            index++;
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
        index += 4;
        return true;
    }

    return false;
}

bool JSONParser::search_true(size_t &index) {

}

bool JSONParser::search_false(size_t &index) {

}

bool JSONParser::parse_file() {
    
    return true;
}

} // namespace json_parser
