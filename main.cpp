#include <benchmark/benchmark.h>

#include <iostream>
#include <vector>
#include <tuple>
#include <utility>

template <class V>
class KernScalarProduct {
public:
    using return_type = V;

    inline void apply(const V & left, const V & right,
                      return_type & ret) {
        ret += left * right;
    }

};

template <class ...Args>
class zip : public std::tuple<Args...>{
public:
    using value_type = std::tuple<typename Args::value_type...>;
    using value_type_ref = std::tuple<typename Args::value_type&...>;

    class iterator : public std::iterator<
            std::input_iterator_tag(),
            value_type, std::ptrdiff_t,
            value_type *, value_type_ref
        > {
    public:
        using iterator_t = std::tuple<typename Args::iterator...>;
        iterator_t it;

        inline value_type_ref operator*() {
//            value_type ret;
            std::cout << __PRETTY_FUNCTION__ << typeid(value_type_ref).name() << "\n";
            return std::apply(
                    [](auto& ...x) {
                        std::cout << "asda<dadsads" << std::endl;
                        std::cout << *(x)...;
                        return std::forward_as_tuple(*(x)...);
                    },
                    it);
//            return ret;
        }

        inline iterator& operator++() {
            std::apply(
                    [](auto ...x){
                        std::make_tuple(++(x)...);
                    },
            it);
            return *this;
        }

    };

    iterator begin() {
        return iterator();
    }

    iterator end() {
        return iterator();
    }
};

template<class C, class T, class Tuple, std::size_t... Is>
void stream_tuple_impl(std::basic_ostream<C, T> & o,
                  const Tuple & tuple,
                  std::index_sequence<Is...>) {
    ((o << (Is == 0 ? "" : ", ") << std::get<Is>(tuple)), ...);
}

template<class C, class T, class... Args>
decltype(auto) operator<<(std::basic_ostream<C, T> & o,
                          const std::tuple<Args...> & tuple) {
    o << "(";
    stream_tuple_impl(o, tuple, std::index_sequence_for<Args...>{});
    return o << ")";
}

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

template <class Kern, class ...Args>
inline auto apply_kern(Args & ...args) {
    apply_kern(Kern{}, args...);
};

template <class Kern, class ...Args>
inline auto apply_kern(Kern && kern, Args & ...args) {
    typename Kern::return_type ret {};

    zip<Args...> a;
    ++a.begin();
    std::cout << *a.begin() << '\n';
//    unpack(kern, *a.begin(), ret);

    std::cout << ret << '\n';
//    for(auto&& a: zip(args...)) {
//        unpack(kern, a, ret);
//    }
    return ret;
}

//static void test01(benchmark::State& state) {
int main() {
    std::vector<int> v1{1, 2, 3};
    std::vector<int> v2{1, 2, 3};

    apply_kern<KernScalarProduct<int>>(v1, v2);
}
//
//}
//BENCHMARK(test01);


//BENCHMARK_MAIN();