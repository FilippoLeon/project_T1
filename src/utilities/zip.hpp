
namespace projectT1::utilities::tuple {

template <class ...Args>
class zip : public std::tuple<Args...> {
public:
    using value_type = std::tuple<typename Args::value_type...>;
    using value_type_ref = std::tuple<typename Args::value_type&...>;

    std::tuple<Args&...> data;

    zip(Args& ...args)
        : data(args...) {

    }

    class iterator : public std::iterator<
        std::input_iterator_tag(),
        value_type, std::ptrdiff_t,
        value_type *, value_type_ref
    > {
    public:
        using iterator_t = std::tuple<typename Args::iterator...>;
        iterator_t it;

        inline iterator(iterator_t & it) : it(it) {};

        inline value_type_ref operator*() {
            //            value_type ret;
            // std::cout << __PRETTY_FUNCTION__ << typeid(value_type_ref).name() << "\n";
            return std::apply(
                [](auto& ...x) {
                    std::cout << "asda<dadsads" << std::endl;
                    //std::cout << *(x)...;
                    return std::forward_as_tuple(*(x)...);
                },
                it);
            //            return ret;
        }

        inline iterator_t& get() {
            return it;
        }

        inline iterator& operator++() {
            it = std::apply(
                [](auto&& ...x) {
                    return std::make_tuple(++(x)...);
                },
                it);
            return *this;
        }

        inline iterator operator++(int) {
            auto it_copy = it;
            it = std::apply(
                [](auto&& ...x) {
                    return std::make_tuple(++(x)...);
                },
                it);
            return it_copy;
        }

        bool operator==(const iterator & other) const {
            //return it == other.it;
            return any_equal(it, other.it);
        }

        bool operator!=(const iterator & other) const {
            return !(*this == other);
        }


        //    it == other.it)

        //    return iterator(std::apply(
        //        [](auto&& ...x) {
        //            return std::make_tuple(x.begin()...);
        //        }, data
        //    ));
        //}
    };

    iterator begin() {
        return iterator(std::apply(
            [](auto&& ...x) {
                return std::make_tuple(x.begin()...);
            }, data
        ));
    }

    iterator end() {
        return iterator(std::apply(
            [](auto&& ...x) {
                return std::make_tuple(x.end()...);
            }, data
        ));
    }

    //const_iterator cbegin() {
    //    return const_iterator(std::apply(
    //        [](auto&& ...x) {
    //            return std::make_tuple(x.cbegin()...);
    //        }, data
    //    ));
    //}

    //const_iterator cend() {
    //    return const_iterator();
    //}
};

}