#pragma once
#pragma warning(disable: 4455)

#include "./AK/Forward.h"
#include "./AK/StringUtils.h"

namespace AK {

class StringView {
public:
    inline constexpr StringView() = default;
    inline constexpr StringView(char const*, size_t) {}
    inline constexpr StringView(unsigned char const*, size_t) {}
    StringView(AK::String const&);
    StringView(FlyString const&);

    bool contains(char) const { return false; }
    bool contains(StringView, CaseSensitivity = CaseSensitivity::CaseSensitive) const { return false; }

    constexpr StringView substring_view(size_t start, size_t length) const { return StringView(); }

    StringView replace(StringView, StringView, ReplaceMode) const { return StringView(); }
    constexpr int compare() { return 0; }
    size_t length() { return 0; }

    constexpr char const* characters_without_null_termination() const { return (char*)""; }

    bool operator==(StringView other) const { return false; }
    bool operator==(char const* cstring) const { return false; }
    bool operator!=(StringView other) const { return false; }
    bool operator<(StringView other) const { return false; }
    bool operator<=(StringView other) const { return false; }
    bool operator>(StringView other) const { return false; }
    bool operator>=(StringView other) const { return false; }

    constexpr int* begin() const { return 0; }
    constexpr int* end() const { return 0; }
};

}

AK::StringView operator"" sv(char const* str, size_t length) {
    return AK::StringView(str, length);
}

using AK::StringView;