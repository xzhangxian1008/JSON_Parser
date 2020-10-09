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

const OBJECTNonTml* get_obj_val(const ValueAbstract *value) {
    const ObjectValue *object_value = dynamic_cast<const ObjectValue*>(value);
    return object_value->get_value();
}

const ARRAYNonTml* get_list_val(const ValueAbstract *value) {
    const ArrayValue *array_value = dynamic_cast<const ArrayValue*>(value);
    return array_value->get_value();
}

TEST(PARSER, non_nested_valid_test) {
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
        std::string json = "{\"name\" : \"xzx\",\"list\" : [123, \"str\", true, false, null]}";
        JSONParser jp(json, true);
        bool result = jp.parse();
        ASSERT_EQ(true, result);

        /** get "name" */
        const ValueAbstract *value_abstr = jp.get("name");
        ASSERT_NE(nullptr, value_abstr);
        ASSERT_EQ(typeid(const StringValue), typeid(*value_abstr));
        std::string value = get_string_val(value_abstr);
        EXPECT_EQ(std::string("xzx"), value);

        /** get "list" */
        const ValueAbstract *list_abstr = jp.get("list");
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

        const ValueAbstract *null_abstr = array[4];
        Value_t type = null_abstr->get_value_t();
        EXPECT_EQ(Value_t::NULL_, type);
    }

    {
        std::string json = "{\"obj\" : {\"name\" : \"xzx\",\"list\" : [123, null],\"obj2\" : {\"aaa\" : \"bbb\",\"null\" : null}},\"list\" : [false,{\"books\":\"c++\"},[321, \"str\"]]}";
        JSONParser jp(json, true);
        bool result = jp.parse();
        ASSERT_EQ(true, result);

        {
            /** get "obj" from root object */
            const ValueAbstract *value_abstr = jp.get("obj");
            ASSERT_NE(nullptr, value_abstr);
            ASSERT_EQ(typeid(const ObjectValue), typeid(*value_abstr));
            const OBJECTNonTml *obj = get_obj_val(value_abstr);
            ASSERT_NE(nullptr, obj); // check obj

            {
                /** get "name" from obj */
                const ValueAbstract *name_abstr = obj->get("name");
                ASSERT_NE(nullptr, name_abstr);
                ASSERT_EQ(typeid(const StringValue), typeid(*name_abstr));
                std::string value = get_string_val(name_abstr);
                EXPECT_EQ(std::string("xzx"), value);
            }

            {
                /** get "list" from obj */
                const ValueAbstract *array_abstr = obj->get("list");
                ASSERT_NE(nullptr, array_abstr);
                ASSERT_EQ(typeid(const ArrayValue), typeid(*array_abstr));
                const ARRAYNonTml *parray = get_list_val(array_abstr);
                ASSERT_NE(nullptr, parray);

                /** check the validation of the elements in list */
                const ARRAYNonTml &array = *parray;
                ASSERT_EQ(2, array.size());

                const ValueAbstract *num_abstr = array[0];
                long num = get_num_val(num_abstr);
                EXPECT_EQ(123, num);

                const ValueAbstract *null_abstr = array[1];
                Value_t type = null_abstr->get_value_t();
                EXPECT_EQ(Value_t::NULL_, type);
                
            } // get "list" from obj

            {
                /** get "obj2" from obj */
                const ValueAbstract *obj2_abstr = obj->get("obj2");
                ASSERT_NE(nullptr, obj2_abstr);
                ASSERT_EQ(typeid(const ObjectValue), typeid(*value_abstr));
                const OBJECTNonTml *obj2 = get_obj_val(obj2_abstr);
                ASSERT_NE(nullptr, obj2);

                {
                    const ValueAbstract *str_abstr = obj2->get("aaa");
                    ASSERT_NE(nullptr, str_abstr);
                    ASSERT_EQ(typeid(const StringValue), typeid(*str_abstr));
                    std::string str = get_string_val(str_abstr);
                    ASSERT_EQ(std::string("bbb"), str);
                }

                {
                    const ValueAbstract *null_abstr = obj2->get("null");
                    ASSERT_NE(nullptr, null_abstr);
                    ASSERT_EQ(typeid(const NullValue), typeid(*null_abstr));
                    Value_t type = null_abstr->get_value_t();
                    EXPECT_EQ(Value_t::NULL_, type);
                }

            } // get "obj2" from obj

        } // get "obj" from root object

        {
            /** get "list" from obj */
            const ValueAbstract *list_abstr = jp.get("list");
            ASSERT_NE(nullptr, list_abstr);
            ASSERT_EQ(typeid(const ArrayValue), typeid(*list_abstr));
            const ARRAYNonTml *plist = get_list_val(list_abstr);
            ASSERT_NE(nullptr, plist); // check list

            const ARRAYNonTml &list = *plist;
            ASSERT_EQ(3, list.size());

            const ValueAbstract *bool_abstr = list[0];
            ASSERT_NE(nullptr, bool_abstr);
            ASSERT_EQ(typeid(const BoolValue), typeid(*bool_abstr));
            bool b = get_bool_val(bool_abstr);
            EXPECT_EQ(false, b);

            {
                /** get sub-object from list */
                const ValueAbstract *sub_obj_abstr = list[1];
                ASSERT_NE(nullptr, sub_obj_abstr);
                ASSERT_EQ(typeid(const ObjectValue), typeid(*sub_obj_abstr));
                const OBJECTNonTml *sub_obj = get_obj_val(sub_obj_abstr);
                ASSERT_NE(nullptr, sub_obj); // check sub_obj

                const ValueAbstract *str_abstr = sub_obj->get("books");
                ASSERT_NE(nullptr, str_abstr);
                ASSERT_EQ(typeid(const StringValue), typeid(*str_abstr));
                std::string str = get_string_val(str_abstr);
                EXPECT_EQ(std::string("c++"), str);

            } // get sub-object from list

            {
                /** get sub_list from list */
                const ValueAbstract *sub_list_abstr = list[2];
                ASSERT_NE(nullptr, sub_list_abstr);
                ASSERT_EQ(typeid(const ArrayValue), typeid(*sub_list_abstr));
                const ARRAYNonTml *psub_list = get_list_val(sub_list_abstr);
                ASSERT_NE(nullptr, psub_list);

                const ARRAYNonTml &sub_list = *psub_list;
                ASSERT_EQ(2, sub_list.size());

                const ValueAbstract *num_abstr = sub_list[0];
                ASSERT_NE(nullptr, num_abstr);
                ASSERT_EQ(typeid(const NumberValue), typeid(*num_abstr));
                long num = get_num_val(num_abstr);
                EXPECT_EQ(321, num);

                const ValueAbstract *str_abstr = sub_list[1];
                ASSERT_NE(nullptr, str_abstr);
                ASSERT_EQ(typeid(const StringValue), typeid(*str_abstr));
                std::string str = get_string_val(str_abstr);
                EXPECT_EQ(std::string("str"), str);

            } // get sub_list from list

        } // get "list" from obj
    }
}

}// namespace json_parser


int main(int argc, char** argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
