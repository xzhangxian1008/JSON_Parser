#include <gtest/gtest.h>
#include "../src/JSONParser.h"

namespace json_parser {

class LexicalAnalyzerTest : public JSONParser {
public:
    LexicalAnalyzerTest(const std::string &parse_target_, bool str_or_file_) 
        : JSONParser(parse_target_, str_or_file_), token_deque(get_token_deque()) {}
    
    std::deque<std::unique_ptr<TokenAbstract>>& get_token_dq() { return token_deque; }
    bool parse() {
        if (get_str_or_file()) {
            if (!parse_string()) {
                return false;
            }
            return true;
        }

        if (!parse_file()) {
            return false;
        }
        return true;
    }

    void print_all_tokens() { print_all_tokens_(); }
private:
    std::deque<std::unique_ptr<TokenAbstract>> &token_deque;
};

TEST(LexicalAnalyzer, DISABLED_valid) {
    std::string json1("{\"name\" : \"xzx\",\"bool\" : true,\"null\" : null,\"num\" : 123,\"obj\" : {\"bool\" : false,\"num\" : -123},\"list\" : [true, null, 1, \"str\", { \"book\" : \"cpp\" }]}");
    LexicalAnalyzerTest jpt1(json1, true);
    ASSERT_EQ(true, jpt1.parse());
    std::deque<std::unique_ptr<TokenAbstract>> &token_deque = jpt1.get_token_dq();

    size_t token_num = 0;
    for (auto &token : token_deque) {
        ++token_num;
        // Token_t tk = token->get_token_type();
        // print(tktype_2_str(tk));
    }
    ASSERT_EQ(48, token_num);
    EXPECT_EQ(Token_t::LEFT_BRACE, token_deque[0]->get_token_type());
    EXPECT_EQ(Token_t::STRING, token_deque[1]->get_token_type());
    EXPECT_EQ(Token_t::COLON, token_deque[2]->get_token_type());
    EXPECT_EQ(Token_t::STRING, token_deque[3]->get_token_type());
    EXPECT_EQ(Token_t::COMMA, token_deque[4]->get_token_type());
    EXPECT_EQ(Token_t::STRING, token_deque[5]->get_token_type());
    EXPECT_EQ(Token_t::COLON, token_deque[6]->get_token_type());
    EXPECT_EQ(Token_t::BOOL, token_deque[7]->get_token_type());
    EXPECT_EQ(Token_t::COMMA, token_deque[8]->get_token_type());
    EXPECT_EQ(Token_t::STRING, token_deque[9]->get_token_type());
    EXPECT_EQ(Token_t::COLON, token_deque[10]->get_token_type());
    EXPECT_EQ(Token_t::NULL_, token_deque[11]->get_token_type());
    EXPECT_EQ(Token_t::COMMA, token_deque[12]->get_token_type());
    EXPECT_EQ(Token_t::STRING, token_deque[13]->get_token_type());
    EXPECT_EQ(Token_t::COLON, token_deque[14]->get_token_type());
    EXPECT_EQ(Token_t::NUMBER, token_deque[15]->get_token_type());
    EXPECT_EQ(Token_t::COMMA, token_deque[16]->get_token_type());
    EXPECT_EQ(Token_t::STRING, token_deque[17]->get_token_type());
    EXPECT_EQ(Token_t::COLON, token_deque[18]->get_token_type());
    EXPECT_EQ(Token_t::LEFT_BRACE, token_deque[19]->get_token_type());
    EXPECT_EQ(Token_t::STRING, token_deque[20]->get_token_type());
    EXPECT_EQ(Token_t::COLON, token_deque[21]->get_token_type());
    EXPECT_EQ(Token_t::BOOL, token_deque[22]->get_token_type());
    EXPECT_EQ(Token_t::COMMA, token_deque[23]->get_token_type());
    EXPECT_EQ(Token_t::STRING, token_deque[24]->get_token_type());
    EXPECT_EQ(Token_t::COLON, token_deque[25]->get_token_type());
    EXPECT_EQ(Token_t::NUMBER, token_deque[26]->get_token_type());
    EXPECT_EQ(Token_t::RIGHT_BRACE, token_deque[27]->get_token_type());
    EXPECT_EQ(Token_t::COMMA, token_deque[28]->get_token_type());
    EXPECT_EQ(Token_t::STRING, token_deque[29]->get_token_type());
    EXPECT_EQ(Token_t::COLON, token_deque[30]->get_token_type());
    EXPECT_EQ(Token_t::LEFT_SB, token_deque[31]->get_token_type());
    EXPECT_EQ(Token_t::BOOL, token_deque[32]->get_token_type());
    EXPECT_EQ(Token_t::COMMA, token_deque[33]->get_token_type());
    EXPECT_EQ(Token_t::NULL_, token_deque[34]->get_token_type());
    EXPECT_EQ(Token_t::COMMA, token_deque[35]->get_token_type());
    EXPECT_EQ(Token_t::NUMBER, token_deque[36]->get_token_type());
    EXPECT_EQ(Token_t::COMMA, token_deque[37]->get_token_type());
    EXPECT_EQ(Token_t::STRING, token_deque[38]->get_token_type());
    EXPECT_EQ(Token_t::COMMA, token_deque[39]->get_token_type());
    EXPECT_EQ(Token_t::LEFT_BRACE, token_deque[40]->get_token_type());
    EXPECT_EQ(Token_t::STRING, token_deque[41]->get_token_type());
    EXPECT_EQ(Token_t::COLON, token_deque[42]->get_token_type());
    EXPECT_EQ(Token_t::STRING, token_deque[43]->get_token_type());
    EXPECT_EQ(Token_t::RIGHT_BRACE, token_deque[44]->get_token_type());
    EXPECT_EQ(Token_t::RIGHT_SB, token_deque[45]->get_token_type());
    EXPECT_EQ(Token_t::RIGHT_BRACE, token_deque[46]->get_token_type());
    EXPECT_EQ(Token_t::END, token_deque[47]->get_token_type());
}

TEST(LexicalAnalyzer, DISABLED_invalid) {
    {
        std::string json("{asd : asd}");
        LexicalAnalyzerTest jpt(json, true);
        EXPECT_EQ(false, jpt.parse());
    }
    
    {
        std::string json("{\"asd\" : 123b1}");
        LexicalAnalyzerTest jpt(json, true);
        EXPECT_EQ(false, jpt.parse());
    }

    {    
        std::string json("{\"a\" : nul}");
        LexicalAnalyzerTest jpt(json, true);
        EXPECT_EQ(false, jpt.parse());
    }

    {
        std::string json("{\"a : 1}");
        LexicalAnalyzerTest jpt(json, true);
        EXPECT_EQ(false, jpt.parse());
    }

    {
        std::string json("{\"a\" : tru}");
        LexicalAnalyzerTest jpt(json, true);
        EXPECT_EQ(false, jpt.parse());
    }

    {
        std::string json("{\"a\" : fa}");
        LexicalAnalyzerTest jpt(json, true);
        EXPECT_EQ(false, jpt.parse());
    }

    {
        std::string json("{\"a\" ' : \"c\"}");
        LexicalAnalyzerTest jpt(json, true);
        EXPECT_EQ(false, jpt.parse());
    }

}

} // json_parser

int main(int argc, char** argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}