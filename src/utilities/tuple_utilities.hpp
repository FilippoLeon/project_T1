#pragma once

#include <tuple>
#include <iostream>

namespace projectT1::utilities::tuple  {
namespace detail {

template <class First, class... Args>
auto head(const std::tuple<First, Args...> & t) {
    return  std::get<0>(t);
}

template <std::size_t... Is, class... Args>
auto tail_impl(std::index_sequence<Is...>, std::tuple<Args...> tuple) {
    return std::make_tuple(std::get<Is + 1u>(tuple)...);
}

template <class... Args>
auto tail(const std::tuple<Args...> & tuple) {
    return tail_impl(std::make_index_sequence<sizeof...(Args)-1u>(), tuple);
}

template<class C, class T, class Tuple, std::size_t... Is>
void stream_tuple_impl(std::basic_ostream<C, T> & o,
                       const Tuple & tuple,
                       std::index_sequence<Is...>) {
    ((o << (Is == 0 ? "" : ", ") << std::get<Is>(tuple)), ...);
}

} // END namespace projectT1::utilities::tuple::detail

template <class T1, class T2>
bool any_equal(std::tuple<T1> lhs, std::tuple<T2> rhs) {
    return std::get<0>(lhs) == std::get<0>(rhs);
}

template <class... Args, class...OtherArgs >
bool any_equal(const std::tuple<Args...> & lhs, const std::tuple<OtherArgs...> & rhs) {
    return detail::head(lhs) == detail::head(rhs) || any_equal(detail::tail(lhs), detail::tail(rhs));
}

} // END namespace projectT1::utilities::tuple

template<class C, class T, class... Args>
decltype(auto) operator<<(std::basic_ostream<C, T> & o,
                          const std::tuple<Args...> & tuple) {
    o << "(";
    projectT1::utilities::tuple::detail::stream_tuple_impl(o, tuple, std::index_sequence_for<Args...>{});
    return o << ")";
}