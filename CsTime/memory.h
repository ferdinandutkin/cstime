#pragma once
#include "framework.h"
#include "globals.h"
#include <tuple>

byte_ptr_t find_pattern(address_t address, address_diff_t max_length, const_byte_ptr_t target, const_byte_ptr_t mask);

address_diff_t get_module_size(address_t address);


namespace {
    template <size_t index, typename T, typename ...Ts>
    struct offset_of
    {
        static constexpr size_t value = sizeof(T) + offset_of<index - 1, Ts...>::value;
    };


    template <size_t index, typename ...Ts>
    struct offset_of<index, std::tuple<Ts...>>
    {
        static constexpr size_t value = offset_of<index, Ts...>::value;
    };

    template<typename T, typename ...Ts>
    struct offset_of<0, T, Ts...>
    {
        static constexpr size_t value = 0;
    };

    template <size_t index, typename ...Ts>
    static constexpr size_t offset_of_v = offset_of<index, Ts...>::value;



    template <size_t index, typename TTuple>
    auto read_single_impl(char* buffer) -> std::tuple_element_t<index, TTuple> {
        using target_type = std::tuple_element_t<index, TTuple>;

        auto offet = offset_of_v<index, TTuple>;

        return *((target_type*)(buffer + offet));
    }

    template <typename TTuple, size_t... Idxs>
    TTuple read_impl(char* buffer, std::index_sequence<Idxs...>) {
        return std::make_tuple(read_single_impl<Idxs, TTuple>(buffer)...);

    }

}


template <typename ...Ts>
std::tuple<Ts...> read(char* buffer) requires (sizeof...(Ts) > 1) {
    return read_impl<std::tuple<Ts...>>(buffer, std::make_index_sequence<sizeof...(Ts)>{});
}


template <typename T>
T read(char* buffer) {
    return read_single_impl<0, std::tuple<T>>(buffer);
}
