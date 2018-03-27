#pragma once

namespace projectT1::kernels::detail {

template <class Kern, class Tuple, std::size_t... Is>
void unpack_impl(Kern && kern, Tuple&& tuple,
                 typename std::remove_reference_t<Kern>::return_type & ret, std::index_sequence<Is...>) {
    kern.apply(std::get<Is>(tuple)..., ret);
}

template <class Kern, class... Args>
void unpack(Kern && kern, const std::tuple<Args...> & tuple,
            typename std::remove_reference_t<Kern>::return_type & ret) {
    unpack_impl(kern, tuple, ret, std::index_sequence_for<Args...>{});
};

}