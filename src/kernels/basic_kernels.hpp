#pragma once

namespace projectT1::kernels {

template <class V>
class KernScalarProduct {
public:
    using return_type = V;

    inline void apply(const V & left, const V & right,
                      return_type & ret) {
        ret += left * right;
    }

};

}