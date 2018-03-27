#pragma once

#include "kernels/detail.hpp"

#include "utilities/zip.hpp"

namespace projectT1::kernels {

template <class Kern, class ...Args>
inline auto apply_kern(Args & ...args) {
    return apply_kern(Kern{}, args...);
};

template <class Kern, class ...Args>
inline auto apply_kern(Kern && kern, Args & ...args) {
    typename Kern::return_type ret{};

    for (auto&& a : utilities::tuple::zip<Args...>(args...)) {
        detail::unpack(kern, a, ret);
    }

    return ret;
}

}