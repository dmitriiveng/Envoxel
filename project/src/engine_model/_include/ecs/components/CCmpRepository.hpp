#pragma once
#include <vector>
#include <string_view>

using Entity = std::size_t;

// ECS is CmpRepository + SystemRepository

template<typename R>
concept CCmpRepository = requires(R& r, const R& cr, Entity e, std::string name) {

    // New entity
    { r.create_entity() } -> std::same_as<Entity>;

    // New component
    // Every time when new cmp is created, loader would register it
    { r.template register_component<struct T>(name) } -> std::same_as<void>;

    // Modifications
    { r.template add<struct T>(e) } -> std::same_as<T&>;
    { r.template get<struct T>(e) } -> std::same_as<T&>;
    { r.template has<struct T>(e) } -> std::convertible_to<bool>;
    { r.template remove<struct T>(e) } -> std::same_as<void>;

    // Foreach
    { r.template foreach_of<struct T>([](Entity, T&){}) } -> std::same_as<void>;
    { r.template foreach_only_of<struct T>([](Entity, T&){}) } -> std::same_as<void>;
    // Sends to callback name of the component + void* on memory where it is stored
    { r.for_each_entity([](Entity, std::vector<std::pair<std::string_view, void*>>) {}) }
        -> std::same_as<void>;

    // Const foreach
    { cr.template foreach_of<struct T>([](Entity, const T&){}) } -> std::same_as<void>;
    { cr.template foreach_only_of<struct T>([](Entity, const T&){}) } -> std::same_as<void>;
    // Sends to callback name of the component + void* on memory where it is stored
    { cr.for_each_entity([](Entity, std::vector<std::pair<std::string_view, const void*>>) {}) } 
        -> std::same_as<void>;   
};