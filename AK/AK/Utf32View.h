/*
 * Copyright (c) 2020, Andreas Kling <kling@serenityos.org>
 *
 * SPDX-License-Identifier: BSD-2-Clause
 */

#pragma once

#include "./AK/Assertions.h"
#include "./AK/Checked.h"
#include "./AK/Types.h"

namespace AK {

class Utf32View;

class Utf32CodePointIterator {
    friend class Utf32View;

public:
    Utf32CodePointIterator() = default;
    ~Utf32CodePointIterator() = default;

    bool operator==(Utf32CodePointIterator const& other) const;
    bool operator!=(Utf32CodePointIterator const& other) const;
    Utf32CodePointIterator& operator++();
    ssize_t operator-(Utf32CodePointIterator const& other) const;
    u32 operator*() const;

    constexpr int code_point_length_in_bytes() const { return sizeof(u32); }
    bool done() const { return !m_length; }

private:
    Utf32CodePointIterator(u32 const* ptr, size_t length)
        : m_ptr(ptr)
        , m_length((ssize_t)length)
    {
    }
    u32 const* m_ptr{ nullptr };
    ssize_t m_length{ -1 };
};

class Utf32View {
public:
    using Iterator = Utf32CodePointIterator;

    Utf32View() = default;
    Utf32View(u32 const* code_points, size_t length)
        : m_code_points(code_points)
        , m_length(length)
    {
    }

    Utf32CodePointIterator begin() const;

    Utf32CodePointIterator end() const;

    u32 at(size_t index) const;

    u32 operator[](size_t index) const { return at(index); }

    u32 const* code_points() const { return m_code_points; }
    bool is_empty() const { return m_length == 0; }
    bool is_null() const { return !m_code_points; }
    size_t length() const { return m_length; }

    size_t iterator_offset(Utf32CodePointIterator const& it) const;

    Utf32View substring_view(size_t offset, size_t length) const;

private:
    u32 const* begin_ptr() const;
    u32 const* end_ptr() const;

    u32 const* m_code_points{ nullptr };
    size_t m_length{ 0 };
};

}

using AK::Utf32View;
