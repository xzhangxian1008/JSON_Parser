#include <gtest/gtest.h>
#include "../src/JSONParser.h"
#include "../src/value/Value.h"

namespace json_parser {

std::string get_string_val(const ValueAbstract *value) {
    const StringValue *string_value = dynamic_cast<const StringValue*>(value);
    return string_value->get_value();
}

long get_num_val(const ValueAbstract *value) {
    const NumberValue *number_value = dynamic_cast<const NumberValue*>(value);
    return number_value->get_value();;
}

bool get_bool_val(const ValueAbstract *value) {
    const BoolValue *bool_value = dynamic_cast<const BoolValue*>(value);
    return bool_value->get_value();
}

const ARRAYNonTml* get_list_val(const ValueAbstract *value) {
    const ArrayValue *array_value = dynamic_cast<const ArrayValue*>(value);
    return array_value->get_value();
}

TEST(PARSER, DISABLED_non_nested_valid_test) {
    {
        std::string json = "{\"name\" : \"xzx\"}";
        JSONParser jp(json, true);
        bool result = jp.parse();
        ASSERT_EQ(true, result);
        const ValueAbstract *value_abstr = jp.get("name");
        ASSERT_NE(nullptr, value_abstr);
        ASSERT_EQ(typeid(const StringValue), typeid(*value_abstr));
        std::string value = get_string_val(value_abstr);
        EXPECT_EQ(std::string("xzx"), value);
    }

    {
        std::string json = "{\"name\" : \"xzx\",\"age\" : 23,\"null\" : null,\"true\" : true,\"false\" : false}";
        JSONParser jp(json, true);
        bool result = jp.parse();
        ASSERT_EQ(true, result);

        /** get name */
        const ValueAbstract *name_abstr = jp.get("name");
        ASSERT_NE(nullptr, name_abstr);
        ASSERT_EQ(typeid(const StringValue), typeid(*name_abstr));
        std::string value = get_string_val(name_abstr);
        EXPECT_EQ(std::string("xzx"), value);

        /** get age */
        const ValueAbstract *number_abstr = jp.get("age");
        long num = get_num_val(number_abstr);
        EXPECT_EQ(23, num);

        /** get null */
        const ValueAbstract *null_abstr = jp.get("null");
        Value_t null_type = null_abstr->get_value_t();
        EXPECT_EQ(Value_t::NULL_, null_type);

        /** get true */
        const ValueAbstract *true_abstr = jp.get("true");
        bool true_ = get_bool_val(true_abstr);
        EXPECT_EQ(true, true_);

        /** get false */
        const ValueAbstract *false_abstr = jp.get("false");
        bool false_ = get_bool_val(false_abstr);
        EXPECT_EQ(false, false_);
    }
} 

TEST(PARSER, nested_valid_test) {
    {
        /** simple nested */
        std::string json = "{\"name\" : \"xzx\",\"list\" : [123, \"str\", true, false]}";
        JSONParser jp(json, true);
        bool result = jp.parse();
        ASSERT_EQ(true, result);

        /** get name */
        const ValueAbstract *value_abstr = jp.get("name");
        ASSERT_NE(nullptr, value_abstr);
        ASSERT_EQ(typeid(const StringValue), typeid(*value_abstr));
        std::string value = get_string_val(value_abstr);
        EXPECT_EQ(std::string("xzx"), value);

        /** get list */
        const ValueAbstract *list_abstr = jp.get("name");
        ASSERT_NE(nullptr, list_abstr);
        ASSERT_EQ(typeid(const ArrayValue), typeid(*list_abstr));
        const ARRAYNonTml* parray = get_list_val(list_abstr);
        ASSERT_NE(nullptr, parray);

        /** check the validation of the elements in list */
        const ARRAYNonTml &array = *parray;
        ASSERT_EQ(5, array.size());

        const ValueAbstract *num_abstr = array[0];
        long num = get_num_val(num_abstr);
        EXPECT_EQ(123, num);

        const ValueAbstract *str_abstr = array[1];
        std::string str = get_string_val(str_abstr);
        EXPECT_EQ(std::string("str"), str);

        const ValueAbstract *true_abstr = array[2];
        bool true_ = get_bool_val(true_abstr);
        EXPECT_EQ(true, true_);

        const ValueAbstract *false_abstr = array[3];
        bool false_ = get_bool_val(false_abstr);
        EXPECT_EQ(false, false_);

        const ValueAbstract *null_abstr = array[3];
        Value_t type = null_abstr->get_value_t();
        EXPECT_EQ(Value_t::NULL_, type);
    }
}

}// namespace json_parser


int main(int argc, char** argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
