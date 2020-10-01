#ifndef JSON_PARSER
#define JSON_PARSER

#include <string>
#include <vector>
#include "TokenAbstract.h"

namespace json_parser {

// TODO complete it
/**
 * NOTICE we parse the json string and ensure the validity first. filename done later
 */
class JSONParser {
public:
    JSONParser(const std::string &parse_target_, bool str_or_file_) 
        : parse_target(parse_target_), str_or_file(str_or_file_) {}

private:
    // store the parse target. json string or filename. It depends on str_or_file
    std::string parse_target;

    /**
     * true: parse string
     * false: parse file
     */
    bool str_or_file;

    // store tokens
    std::vector<TokenAbstract *> token_stack;
};
}

#endif