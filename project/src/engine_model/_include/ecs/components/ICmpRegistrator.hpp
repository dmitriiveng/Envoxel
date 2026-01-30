#include <string_view>

// Registers component in ECS and in serializer
// Example:
// struct pos{int x, y};
// using register_cmp(...) = Loader.get_instance.get_cmp_register.register_cmp(...);
// register_cmp<pos>("position");

template<typename R>
concept CCmpRegistrator = requires(R& r, std::string_view name) {
    { r.template register_component<struct T>(name) } -> std::same_as<void>;
};