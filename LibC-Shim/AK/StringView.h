/*
 * Copyright (c) 2018-2021, Andreas Kling <kling@serenityos.org>
 *
 * SPDX-License-Identifier: BSD-2-Clause
 */

#pragma once
#pragma warning(disable: 4455)

#include "Assertions.h"
#include "Checked.h"
#include "Forward.h"
#include "Optional.h"
#include "Span.h"
#include "StdLibExtras.h"
#include "StringHash.h"
#include "StringUtils.h"

namespace AK {

class StringView {
public:
    ALWAYS_INLINE constexpr StringView() = default;
    ALWAYS_INLINE constexpr StringView(char const* characters, size_t length)
        : m_characters(characters)
        , m_length(length)
    {
        if (!is_constant_evaluated())
            VERIFY(!Checked<uintptr_t>::addition_would_overflow((uintptr_t)characters, length));
    }
    ALWAYS_INLINE StringView(unsigned char const* characters, size_t length)
        : m_characters((char const*)characters)
        , m_length(length)
    {
        //VERIFY(!Checked<uintptr_t>::addition_would_overflow((uintptr_t)characters, length));
    }
    ALWAYS_INLINE StringView(ReadonlyBytes bytes)
        : m_characters(reinterpret_cast<char const*>(bytes.data()))
        , m_length(bytes.size())
    {
    }

    StringView(ByteBuffer const&)
    {
        // FIXME: Impl this.
        VERIFY_NOT_REACHED();
    }
    StringView(String const&)
    {
        // FIXME: Impl this.
        VERIFY_NOT_REACHED();
    }
    StringView(FlyString const&)
    {
        // FIXME: Impl this.
        VERIFY_NOT_REACHED();
    }

    explicit StringView(ByteBuffer&&) = delete;
    explicit StringView(String&&) = delete;
    explicit StringView(FlyString&&) = delete;

    constexpr bool is_null() const
    {
        // FIXME: Impl this.
        VERIFY_NOT_REACHED();
        return false;
    }
    constexpr bool is_empty() const { return m_length == 0; }

    constexpr char const* characters_without_null_termination() const { return m_characters; }
    constexpr size_t length() const { return m_length; }

    ReadonlyBytes bytes() const
    {
        // FIXME: Impl this.
        VERIFY_NOT_REACHED();
        return {};
    }
    constexpr char const& operator[](size_t index) const;

    constexpr StringView substring_view(size_t start, size_t length) const
    {
        // FIXME: Impl this.
        VERIFY_NOT_REACHED();
        return StringView();
    }
    constexpr StringView substring_view(size_t start) const
    {
        // FIXME: Impl this.
        VERIFY_NOT_REACHED();
        return StringView();
    }

    StringView replace(StringView, StringView, ReplaceMode) const;
    constexpr int compare()
    {
        // FIXME: Impl this.
        VERIFY_NOT_REACHED();
        return 0;
    }

    constexpr int* begin() const
    {
        // FIXME: Impl this.
        VERIFY_NOT_REACHED();
        return 0;
    }
    constexpr int* end() const
    {
        // FIXME: Impl this.
        VERIFY_NOT_REACHED();
        return 0;
    }

    constexpr unsigned hash() const
    {
        // FIXME: Impl this.
        VERIFY_NOT_REACHED();
        return 0;
    }

    bool starts_with(StringView, CaseSensitivity = CaseSensitivity::CaseSensitive) const
    {
        // FIXME: Impl this.
        VERIFY_NOT_REACHED();
        return false;
    }
    bool ends_with(StringView, CaseSensitivity = CaseSensitivity::CaseSensitive) const
    {
        // FIXME: Impl this.
        VERIFY_NOT_REACHED();
        return false;
    }
    bool starts_with(char) const
    {
        // FIXME: Impl this.
        VERIFY_NOT_REACHED();
        return false;
    }
    bool ends_with(char) const
    {
        // FIXME: Impl this.
        VERIFY_NOT_REACHED();
        return false;
    }
    bool matches(StringView mask, CaseSensitivity = CaseSensitivity::CaseInsensitive) const
    {
        // FIXME: Impl this.
        VERIFY_NOT_REACHED();
        return false;
    }
    bool matches(StringView mask, Vector<MaskSpan>&, CaseSensitivity = CaseSensitivity::CaseInsensitive) const
    {
        // FIXME: Impl this.
        VERIFY_NOT_REACHED();
        return false;
    }
    bool contains(char) const
    {
        // FIXME: Impl this.
        VERIFY_NOT_REACHED();
        return false;
    }
    bool contains(StringView, CaseSensitivity = CaseSensitivity::CaseSensitive) const
    {
        // FIXME: Impl this.
        VERIFY_NOT_REACHED();
        return false;
    }
    bool equals_ignoring_case(StringView other) const
    {
        // FIXME: Impl this.
        VERIFY_NOT_REACHED();
        return false;
    }

    StringView trim(StringView characters, TrimMode mode = TrimMode::Both) const;
    StringView trim_whitespace(TrimMode mode = TrimMode::Both) const;

    String to_lowercase_string() const;
    String to_uppercase_string() const;
    String to_titlecase_string() const;

    Optional<size_t> find(char needle, size_t start = 0) const
    {
        // FIXME: Impl this.
        VERIFY_NOT_REACHED();
        return {};
    }
    Optional<size_t> find(StringView needle, size_t start = 0) const
    {
        // FIXME: Impl this.
        VERIFY_NOT_REACHED();
        return {};
    }
    Optional<size_t> find_last(char needle) const
    {
        // FIXME: Impl this.
        VERIFY_NOT_REACHED();
        return {};
    }

    Vector<size_t> find_all(StringView needle);

    using SearchDirection = StringUtils::SearchDirection;
    Optional<size_t> find_any_of(StringView needles, SearchDirection direction = SearchDirection::Forward) const;

    Vector<StringView> lines(bool consider_cr = true) const;

    template<typename T = int>
    Optional<T> to_int() const
    {
        // FIXME: Impl this.
        VERIFY_NOT_REACHED();
        return {};
    }
    template<typename T = unsigned>
    Optional<T> to_uint() const
    {
        // FIXME: Impl this.
        VERIFY_NOT_REACHED();
        return {};
    }

    StringView substring_view_starting_from_substring(StringView substring) const
    {
        // FIXME: Impl this.
        VERIFY_NOT_REACHED();
        return StringView();
    }
    StringView substring_view_starting_after_substring(StringView substring) const
    {
        // FIXME: Impl this.
        VERIFY_NOT_REACHED();
        return StringView();
    }

    bool copy_characters_to_buffer(char* buffer, size_t buffer_size) const
    {
        // FIXME: Impl this.
        VERIFY_NOT_REACHED();
        return false;
    }

    bool operator==(StringView other) const
    {
        // FIXME: Impl this.
        VERIFY_NOT_REACHED();
        return false;
    }
    constexpr bool operator==(char const* cstring) const
    {
        // FIXME: Impl this.
        VERIFY_NOT_REACHED();
        return false;
    }
    constexpr bool operator!=(StringView other) const
    {
        // FIXME: Impl this.
        VERIFY_NOT_REACHED();
        return false;
    }
    bool operator<(StringView other) const
    {
        // FIXME: Impl this.
        VERIFY_NOT_REACHED();
        return false;
    }
    bool operator<=(StringView other) const
    {
        // FIXME: Impl this.
        VERIFY_NOT_REACHED();
        return false;
    }
    bool operator>(StringView other) const
    {
        // FIXME: Impl this.
        VERIFY_NOT_REACHED();
        return false;
    }
    bool operator>=(StringView other) const
    {
        // FIXME: Impl this.
        VERIFY_NOT_REACHED();
        return false;
    }

    String to_string() const;

    template<typename... Ts>
    ALWAYS_INLINE constexpr bool is_one_of(Ts&&... strings) const
    {
        return (... || this->operator==(forward<Ts>(strings)));
    }

    template<typename... Ts>
    ALWAYS_INLINE constexpr bool is_one_of_ignoring_case(Ts&&... strings) const
    {
        return (... ||
                [this, &strings]() -> bool {
            if constexpr (requires(Ts a) { a.view()->StringView; })
                return this->equals_ignoring_case(forward<Ts>(strings.view()));
            else
                return this->equals_ignoring_case(forward<Ts>(strings));
        }());
    }

private:
    friend class String;
    char const* m_characters{ nullptr };
    size_t m_length{ 0 };
};

}

ALWAYS_INLINE constexpr AK::StringView operator"" sv(char const* cstring, size_t length)
{
    VERIFY_NOT_REACHED();
    return AK::StringView(cstring, length);
}

using AK::StringView;
