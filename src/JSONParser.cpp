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


    return true;
}

bool JSONParser::parse_file() {
    
    return true;
}

} // namespace json_parser
