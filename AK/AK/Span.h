#pragma once

#include "./AK/Array.h"
#include "./AK/Assertions.h"
#include "./AK/Iterator.h"
#include "./AK/TypedTransfer.h"
#include "./AK/Types.h"

namespace AK {

namespace Detail {

template<typename T>
class Span {
public:
    inline constexpr Span() = default;

    inline constexpr Span(T*, size_t) {}
};

}

template<typename T>
class Span : public Detail::Span<T> {
public:
    using Detail::Span<T>::Span;

    constexpr Span() = default;
};

using ReadonlyBytes = Span<u8 const>;
using Bytes = Span<u8>;

}

using AK::Bytes;
using AK::ReadonlyBytes;
using AK::Span;
