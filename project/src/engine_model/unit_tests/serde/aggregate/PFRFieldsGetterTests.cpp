#include <gtest/gtest.h>
#include "serde/aggregate/PfrFieldsGetter.hpp"

#include <string>
#include <tuple>

struct TestStruct {
    int a;
    double b;
    std::string c;
};

TEST(PfrFieldsGetterTest, FieldCount) {
    EXPECT_EQ(PfrFieldsGetter::field_count<TestStruct>(), 3);
}

TEST(PfrFieldsGetterTest, ForEachField) {
    TestStruct obj{42, 3.14, "hello"};
    int intSum = 0;
    double doubleSum = 0.0;
    std::string concatenated;

    PfrFieldsGetter::for_each_field(obj, [&](auto& field) {
        if constexpr (std::is_same_v<decltype(field), int&>) {
            intSum += field;
        } else if constexpr (std::is_same_v<decltype(field), double&>) {
            doubleSum += field;
        } else if constexpr (std::is_same_v<decltype(field), std::string&>) {
            concatenated += field;
        }
    });

    EXPECT_EQ(intSum, 42);
    EXPECT_DOUBLE_EQ(doubleSum, 3.14);
    EXPECT_EQ(concatenated, "hello");
}

TEST(PfrFieldsGetterTest, TupleType) {
    const TestStruct obj{1, 2.5, "abc"};

    using TupleType = PfrFieldsGetter::tuple_type<TestStruct>;
    const TupleType tuple = boost::pfr::structure_to_tuple(obj);

    EXPECT_EQ(std::get<0>(tuple), 1);
    EXPECT_DOUBLE_EQ(std::get<1>(tuple), 2.5);
    EXPECT_EQ(std::get<2>(tuple), "abc");
}

