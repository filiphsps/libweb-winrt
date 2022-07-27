#pragma once

#include "./AK/String.h"
#include "./AK/StringUtils.h"

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

    static FlyString from_fly_impl(NonnullRefPtr<StringImpl> impl)
    {
        //VERIFY(impl->is_fly());
        FlyString string;
        string.m_impl = move(impl);
        return string;
    }

    FlyString& operator=(FlyString&& other)
    {
        m_impl = move(other.m_impl);
        return *this;
    }

    bool is_empty() const { return true; }
    bool is_null() const { return true; }

    bool operator==(FlyString const& other) const { return m_impl == other.m_impl; }

    StringImpl const* impl() const { return m_impl; }
    char const* characters() const { return nullptr; }
    size_t length() const { return 0; }

    inline u32 hash() const { return 0; }
    inline StringView view() const;

    FlyString to_lowercase() const;

    template<typename T = int>
    Optional<T> to_int(TrimWhitespace = TrimWhitespace::Yes) const;
    template<typename T = unsigned>
    Optional<T> to_uint(TrimWhitespace = TrimWhitespace::Yes) const;

private:
    RefPtr<StringImpl> m_impl;
};

template<>
struct Traits<FlyString> : public GenericTraits<FlyString> {
    static unsigned hash(FlyString const& s) { return s.hash(); }
};

}

using AK::FlyString;
