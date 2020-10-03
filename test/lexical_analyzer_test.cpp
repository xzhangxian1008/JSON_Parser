#include <gtest/gtest.h>
#include "../src/JSONParser.h"

namespace json_parser {

template<typename T>
inline void print(const T &t) {
    std::cout << t << std::endl;
}

class JSONParserTest : public JSONParser {
public:
    JSONParserTest(const std::string &parse_target_, bool str_or_file_) 
        : JSONParser(parse_target_, str_or_file_), token_deque(get_token_deque()) {}
    
    std::deque<std::unique_ptr<TokenAbstract>>& get_token_dq() { return token_deque; }
private:
    std::deque<std::unique_ptr<TokenAbstract>> &token_deque;
};

TEST(LexicalAnalyzer, valid) {
    std::string json1("{\"name\" : \"xzx\",\"age\" : 23,\"cool\" : true,\"bad\" : null,\"sss\" : -123, \"aaa\":\"bbb\"}");
    JSONParserTest jpt1(json1, true);
    EXPECT_EQ(true, jpt1.parse());
    std::deque<std::unique_ptr<TokenAbstract>> &token_deque = jpt1.get_token_dq();

    size_t token_num = 0;
    for (auto &token : token_deque) {
        ++token_num;
        // Token_t tk = token->get_token_type();
        // print(tktype_2_str(tk));
    }
    ASSERT_EQ(26, token_num);

    EXPECT_EQ();
    
}

TEST(LexicalAnalyzer, DISABLED_invalid) {
    
}

} // json_parser

int main(int argc, char** argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}