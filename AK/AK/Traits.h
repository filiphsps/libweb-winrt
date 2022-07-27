#pragma once

namespace AK {

template<typename T>
struct GenericTraits {
    using PeekType = T&;
    using ConstPeekType = T const&;
    static constexpr bool is_trivial() { return false; }
    static constexpr bool equals(const T& a, const T& b) { return a == b; }
    template<Concepts::HashCompatible<T> U>
    static bool equals(U const& a, T const& b) { return a == b; }
};

template<typename T>
struct Traits : public GenericTraits<T> {
};

}

using AK::GenericTraits;
using AK::Traits;