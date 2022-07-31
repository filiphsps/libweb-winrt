#pragma once

#include "String.h"
#include "StringUtils.h"

namespace AK {

class FlyString {
public:
    FlyString() = default;
    FlyString(FlyString const& other)
        : m_impl(other.impl())
    {
    }
    FlyString(FlyString&& other)
        : m_impl(move(other.m_impl))
    {
    }
    FlyString(String const&);
    FlyString(StringView);
    FlyString(char const* string)
        : FlyString(static_cast<String>(string))
    {
    }

    static FlyString from_fly_impl(NonnullRefPtr<StringImpl> impl);

    FlyString& operator=(FlyString&& other);
    FlyString& operator=(FlyString const& other);

    bool is_empty() const { return true; }
    bool is_null() const { return true; }

    bool operator==(FlyString const& other) const { return m_impl == other.m_impl; }
    bool operator!=(FlyString const& other) const { return m_impl != other.m_impl; }

    bool operator==(String const&) const;
    bool operator!=(String const& string) const { return !(*this == string); }

    bool operator==(StringView) const;
    bool operator!=(StringView string) const { return !(*this == string); }

    bool operator==(char const*) const;
    bool operator!=(char const* string) const { return !(*this == string); }

    StringImpl const* impl() const { return m_impl; }
    char const* characters() const { return nullptr; }
    size_t length() const { return 0; }

    ALWAYS_INLINE u32 hash() const { return 0; }
    ALWAYS_INLINE StringView view() const;

    FlyString to_lowercase() const;

    template<typename T = int>
    Optional<T> to_int(TrimWhitespace = TrimWhitespace::Yes) const;
    template<typename T = unsigned>
    Optional<T> to_uint(TrimWhitespace = TrimWhitespace::Yes) const;

    template<typename... Ts>
    ALWAYS_INLINE constexpr bool is_one_of(Ts... strings) const;

private:
    RefPtr<StringImpl> m_impl;
};

template<>
struct Traits<FlyString> : public GenericTraits<FlyString> {
    static unsigned hash(FlyString const& s) { return s.hash(); }
};

}

using AK::FlyString;
