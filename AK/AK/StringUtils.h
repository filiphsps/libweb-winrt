#pragma once

#include "./AK/Concepts.h"
#include "./AK/Forward.h"

namespace AK {

namespace Detail {
template<Concepts::AnyString T, Concepts::AnyString U>
inline constexpr bool IsHashCompatible<T, U> = true;
}

enum class CaseSensitivity {
    CaseInsensitive,
    CaseSensitive,
};

enum class ReplaceMode {
    All,
    FirstOnly,
};

enum class TrimMode {
    Left,
    Right,
    Both
};

enum class TrimWhitespace {
    Yes,
    No,
};

struct MaskSpan {
    size_t start;
    size_t length;

    bool operator==(MaskSpan const& other) const
    {
        return start == other.start && length == other.length;
    }
    bool operator!=(MaskSpan const& other) const
    {
        return !(*this == other);
    }
};

namespace StringUtils {

enum class SearchDirection {
    Forward,
    Backward
};

}

}

using AK::CaseSensitivity;
using AK::ReplaceMode;
using AK::TrimMode;
using AK::TrimWhitespace;
