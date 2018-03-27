#pragma once

namespace projectT1::kernels {

template <class Kern, class ...Args>
inline auto apply_kern(Args & ...args) {
    apply_kern(Kern{}, args...);
};

template <class Kern, class ...Args>
inline auto apply_kern(Kern && kern, Args & ...args) {
    typename Kern::return_type ret{};

    zip<Args...> a(args...);

    auto it = a.begin();
    ++a.begin();
    std::cout << *std::get<0>(a.begin().get()) << '\n';
    std::cout << *a.begin() << '\n';
    std::cout << *++(a.begin()) << '\n';
    std::cout << *it << " " << *(it++) << " " << *++it << '\n';
    unpack(kern, *a.begin(), ret);

    std::cout << ret << '\n';
    for (auto&& a : zip<Args...>(args...)) {
        unpack(kern, a, ret);
    }
    std::cout << ret << '\n';
    return ret;
}

}