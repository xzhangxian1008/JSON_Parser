#ifndef JSON_PARSER
#define JSON_PARSER

#include <string>
#include <vector>
#include <deque>
#include <stack>
#include <memory>
#include <iostream>

#include "src/token/Token.h"
#include "src/token/TokenAbstract.h"
#include "src/non_tml/NonTmlAbstr.h"
#include "src/value/Value.h"

namespace json_parser {

/**
 * NOTICE we parse the json string and ensure the validity first. filename done later
 */
class JSONParser {
public:
    JSONParser(const std::string &parse_target_, bool str_or_file_);
    
    // parse result: 
    //   true: success
    //   false: fail
    bool parse();

    JSONParser(const JSONParser &j) = delete;

protected:
    // NOTICE function only for test
    std::deque<std::unique_ptr<TokenAbstract>>& get_token_deque() { return token_deque; }

private:
    bool parse_file();
    bool parse_string();
    bool lexical_analyze();
    bool semantic_analysis();

    /** search unsuccessfully if it returns false. And it implies an invalid JSON */
    bool search_string(std::string &str, size_t &index);
    bool search_null(size_t &index);
    bool search_bool(size_t &index, bool &val);
    bool search_num(size_t &index, long &val);

    // store the parse target. json string or filename. It depends on str_or_file
    std::string parse_target;

    // the length of parse_target
    size_t pt_length;

    /**
     * true: parse string
     * false: parse file
     */
    bool str_or_file;

    // store tokens
    std::deque<std::unique_ptr<TokenAbstract>> token_deque;

    // store non-terminal
    std::stack<std::unique_ptr<NonTmlAbstr>> non_tml_stack;

    /**
     * object_locate_stack:
     *   store index where we should pop the object_stack
     * 
     * array_locate_stack:
     *   store index where we should pop the array_stack
     */
    std::stack<OBJECTNonTml*> object_stk;
    std::stack<std::size_t> object_lct_stk;
    std::stack<ARRAYNonTml*> array_stk;
    std::stack<std::size_t> array_lct_stk;

    
};

} // namespace json_parser

#endif