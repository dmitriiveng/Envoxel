#include "serde/serialization/aggregate/mapper/AggregateSerializerMapper.hpp"

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

    class SerializationFunctionsMapper final : public ISerializationFunctionsMapper<std::string, std::type_index> {
        std::unordered_map<std::type_index, std::function<std::string(const void*)>> data;

    public:
        std::function<std::string(const void*)> get_function(const std::type_index& type_index_v) const override
        {
            const auto it = data.find(type_index_v);
            if (it == data.end()) throw std::logic_error("doesn't have a serialization function");
            return it->second;
        }
        void add_function(
            const std::type_index& type_index_v,
            const std::function<std::string(const void*)>& function
            ) override
        {
            if (data.contains(type_index_v)) {
                throw std::logic_error("type already has serialization function");
            }

            data.emplace(type_index_v, function);
        }
    };

    std::string func_int(const void* ptr) {
        const int* i = reinterpret_cast<const int*>(ptr);
        return std::to_string(*i);
    }

    std::string func_double(const void* ptr) {
        const double* d = reinterpret_cast<const double*>(ptr);
        return std::to_string(*d);
    }
}

TEST(AggregateMapper, AddGetFunction) {
    FieldsGetter getter;

    A a{10, 1};
    B b{10, 1};

    SerializationFunctionsMapper mapper;
    mapper.add_function(typeid(int), func_int);
    mapper.add_function(typeid(double), func_double);

    AggregateSerializerMapper<std::string> aggregate_serializer_mapper;

    aggregate_serializer_mapper.add_function<A>("a", mapper, getter);
    aggregate_serializer_mapper.add_function<B>("b", mapper, getter);

    std::vector<std::string> r1 {std::to_string(a.a), std::to_string(a.b)};
    std::vector<std::string> r2 {std::to_string(b.a), std::to_string(b.b)};

    EXPECT_EQ(aggregate_serializer_mapper.get_function("a")(&a), r1);
    EXPECT_EQ(aggregate_serializer_mapper.get_function("b")(&b), r2);
}


TEST(AggregateMapper, AddSameKeyException) {
    FieldsGetter getter;

    SerializationFunctionsMapper mapper;
    mapper.add_function(typeid(int), func_int);
    mapper.add_function(typeid(double), func_double);

    AggregateSerializerMapper<std::string> aggregate_serializer_mapper;

    aggregate_serializer_mapper.add_function<A>("a", mapper, getter);

    EXPECT_THROW(
        [&]() {
            aggregate_serializer_mapper.add_function<A>("a", mapper, getter);
        }(),
        std::logic_error
    );
}

TEST(AggregateMapper, GetUnknownKeyException) {
    AggregateSerializerMapper<std::string> aggregate_serializer_mapper;

    EXPECT_THROW(
        aggregate_serializer_mapper.get_function("f"),
        std::logic_error
    );
}
