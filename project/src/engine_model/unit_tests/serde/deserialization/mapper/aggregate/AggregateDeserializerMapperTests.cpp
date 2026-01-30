#include "serde/deserialization/mapper/aggregate/AggregateDeserializerMapper.hpp"

#include <gtest/gtest.h>

namespace {
    struct A final {
        int a;
        int b;
    };

    struct B final {
        double a;
        int b;
    };

    struct FieldsGetter {
        template <typename Aggregate, typename Func>
        void for_each_field(Aggregate& aggr, Func&& f) const {
            boost::pfr::for_each_field(aggr, std::forward<Func>(f));
        }
    };

    class DeserializationFunctionsMapper final : public IDeserializationFunctionsMapper<std::string, std::type_info>
    {
        std::unordered_map<std::type_index, std::function<std::any(const std::string& input)>> data;

    public:
        std::function<std::any(const std::string& input)> get_function(
            const std::type_info& type_info_v
            ) const override
        {
            const std::type_index type_index_v(type_info_v);
            const auto it = data.find(type_index_v);
            if (it == data.end()){
                throw std::logic_error(std::string("No deserialization function for type: ") + type_info_v.name());
            }
            return it->second;
        }

        void add_function(
            const std::type_info& type_info_v,
            const std::function<std::any(const std::string& input)>& function
            ) override
        {
            const std::type_index type_index_v(type_info_v);
            if (data.contains(type_index_v)) {
                throw std::logic_error(std::string("type already has deserialization function") + type_info_v.name());
            }

            data.emplace(type_index_v, function);
        }
    };

    std::any func_int(const std::string& s) {
        return std::stoi(s);
    }

    std::any func_double(const std::string& s) {
        return std::stod(s);
    }
}

TEST(AggregateDeserializerMapper, AddGetFunction) {
    FieldsGetter getter;

    const A a{10, 1};
    const B b{10.5, 1};

    DeserializationFunctionsMapper mapper;
    mapper.add_function(typeid(int), func_int);
    mapper.add_function(typeid(double), func_double);

    AggregateDeserializerMapper<std::string> aggregate_deserializer_mapper;

    aggregate_deserializer_mapper.add_function<A>("a", mapper, getter);
    aggregate_deserializer_mapper.add_function<B>("b", mapper, getter);

    A r_a = std::any_cast<A>(
        aggregate_deserializer_mapper.get_function("a")(std::vector<std::string>{"10", "1"})
        );
    B r_b = std::any_cast<B>(
        aggregate_deserializer_mapper.get_function("b")(std::vector<std::string>{"10.5", "1"})
        );

    EXPECT_EQ(r_a.a, a.a);
    EXPECT_EQ(r_a.b, a.b);
    EXPECT_EQ(r_b.a, b.a);
    EXPECT_EQ(r_b.b, b.b);
}


TEST(AggregateDeserializerMapper, AddSameKeyException) {
    FieldsGetter getter;

    DeserializationFunctionsMapper mapper;
    mapper.add_function(typeid(int), func_int);
    mapper.add_function(typeid(double), func_double);

    AggregateDeserializerMapper<std::string> aggregate_deserializer_mapper;

    aggregate_deserializer_mapper.add_function<A>("a", mapper, getter);

    EXPECT_THROW(
        [&]() {
            aggregate_deserializer_mapper.add_function<A>("a", mapper, getter);
        }(),
        std::logic_error
    );
}

TEST(AggregateDeserializerMapper, GetUnknownKeyException) {
    AggregateDeserializerMapper<std::string> aggregate_deserializer_mapper;

    EXPECT_THROW(
        aggregate_deserializer_mapper.get_function("f"),
        std::logic_error
    );
}
