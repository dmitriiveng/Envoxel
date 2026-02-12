#include <gtest/gtest.h>

#include "serde/deserialization/template_function/default/dsrlz/str_deserializers.hpp"
#include "serde/type_erasure/VoidPtrAny.hpp"
#include "serde/deserialization/functions_generator/SimpleDsrlzFuncGenerator.hpp"

using namespace serde::dsrlz;

namespace {
    TEST(GenerateSimpleTypeDsrlzFunctionTest, IntSpecialization) {
        const auto func = generate_simple_type_dsrlz_function<std::string, int>();

        VoidPtrAny result = func("42");
        EXPECT_EQ(result.get_value<int>(), 42);
    }

    TEST(GenerateSimpleTypeDsrlzFunctionTest, FloatSpecialization) {
        auto func = generate_simple_type_dsrlz_function<std::string, float>();

        VoidPtrAny result = func("3.5");
        EXPECT_FLOAT_EQ(result.get_value<float>(), 3.5f);
    }

    TEST(GenerateSimpleTypeDsrlzFunctionTest, DoubleSpecialization) {
        const auto func = generate_simple_type_dsrlz_function<std::string, double>();

        VoidPtrAny result = func("2.25");
        EXPECT_DOUBLE_EQ(result.get_value<double>(), 2.25);
    }

    TEST(GenerateSimpleTypeDsrlzFunctionTest, StringSpecialization) {
        const auto func = generate_simple_type_dsrlz_function<std::string, std::string>();

        VoidPtrAny result = func("\"abc\"");
        EXPECT_EQ(result.get_value<std::string>(), "abc");
    }

    TEST(GenerateSimpleTypeDsrlzFunctionTest, VectorSpecialization) {
        const auto func = generate_simple_type_dsrlz_function<std::string, std::vector<std::vector<int>>>();

        VoidPtrAny result = func("[[1][2]], [[3][4]], [[5][6]]");
        EXPECT_EQ(result.get_value<std::vector<std::vector<int>>>(), std::vector<std::vector<int>>({
            std::vector<int>({1, 2}),
            std::vector<int>({3, 4}),
            std::vector<int>({5, 6})}));
    }

    TEST(GenerateSimpleTypeDsrlzFunctionTest, MapSpecialization) {
        const auto func = generate_simple_type_dsrlz_function<std::string, std::map<int, std::vector<int>>>();

        VoidPtrAny result = func(
            "[[1]; [[2][2]]], "
                "[[3]; [[4][4]]], "
                "[[5]; [[6][6]]]"
                );
        const std::map<int, std::vector<int>> expected{
        {1, {2, 2}},
        {3, {4, 4}},
        {5, {6, 6}}
        };

        const auto res = result.get_value<std::map<int, std::vector<int>>>();

        EXPECT_EQ(
            res,
            expected
        );
    }
}

struct SingleTypeDeserializerTestData final{
    int a;
};

template<>
struct serde::dsrlz::func::Deserializer<std::string, SingleTypeDeserializerTestData> {
    static SingleTypeDeserializerTestData deserialize(const std::string& input) {
        return SingleTypeDeserializerTestData(std::stoi(input));
    }
};

TEST(GenerateSimpleTypeDsrlzFunctionTest, CustomBoolSpecialization) {
    const auto func = generate_simple_type_dsrlz_function<std::string, SingleTypeDeserializerTestData>();

    VoidPtrAny result = func("2");

    EXPECT_TRUE(result.get_value<SingleTypeDeserializerTestData>().a == 2);
}