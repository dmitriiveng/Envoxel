#include <gtest/gtest.h>
#include "serde/deserialization/mapper/StringDeserializationFunctionsMapper.hpp"

namespace {

    std::any func_int(const std::string& s) {
        return std::stoi(s);
    }

    std::any func_double(const std::string& s) {
        return std::stod(s);
    }

}

TEST(StringDeserializationFunctionsMapper, AddGetFunction) {
    StringDeserializationFunctionsMapper mapper;

    mapper.add_function(typeid(int), func_int);
    mapper.add_function(typeid(double), func_double);

    std::string s_int = "42";
    std::string s_double = "3.14";

    auto f_int = mapper.get_function(typeid(int));
    auto f_double = mapper.get_function(typeid(double));

    EXPECT_EQ(std::any_cast<int>(f_int(s_int)), 42);
    EXPECT_DOUBLE_EQ(std::any_cast<double>(f_double(s_double)), 3.14);
}

TEST(StringDeserializationFunctionsMapper, AddSameTypeException) {
    StringDeserializationFunctionsMapper mapper;

    mapper.add_function(typeid(int), func_int);

    EXPECT_THROW(mapper.add_function(typeid(int), func_int), std::logic_error);
}

TEST(StringDeserializationFunctionsMapper, GetUnknownTypeException) {
    StringDeserializationFunctionsMapper mapper;

    EXPECT_THROW(mapper.get_function(typeid(float)), std::logic_error);
}
