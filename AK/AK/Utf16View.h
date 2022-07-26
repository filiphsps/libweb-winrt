/*
 * Copyright (c) 2021, Tim Flynn <trflynn89@serenityos.org>
 *
 * SPDX-License-Identifier: BSD-2-Clause
 */

#pragma once

#include "./AK/Format.h"
#include "./AK/Forward.h"
#include "./AK/Optional.h"
#include "./AK/Span.h"
#include "./AK/String.h"
#include "./AK/Types.h"
#include "./AK/Vector.h"

namespace AK {

Vector<u16, 1> utf8_to_utf16(StringView);
Vector<u16, 1> utf8_to_utf16(Utf8View const&);
Vector<u16, 1> utf32_to_utf16(Utf32View const&);
void code_point_to_utf16(Vector<u16, 1>&, u32);

class Utf16View;

class Utf16CodePointIterator {
    friend class Utf16View;

public:
    Utf16CodePointIterator() = default;
    ~Utf16CodePointIterator() = default;

    bool operator==(Utf16CodePointIterator const& other) const;

    bool operator!=(Utf16CodePointIterator const& other) const;

    Utf16CodePointIterator& operator++();
    u32 operator*() const;

    size_t length_in_code_units() const;

private:
    Utf16CodePointIterator(u16 const* ptr, size_t length)
        : m_ptr(ptr)
        , m_remaining_code_units(length)
    {
    }

    u16 const* m_ptr{ nullptr };
    size_t m_remaining_code_units{ 0 };
};

class Utf16View {
public:
    static bool is_high_surrogate(u16);
    static bool is_low_surrogate(u16);
    static u32 decode_surrogate_pair(u16 high_surrogate, u16 low_surrogate);

    Utf16View() = default;
    ~Utf16View() = default;

    explicit Utf16View(Span<u16 const> code_units)
        : m_code_units(code_units)
    {
    }

    bool operator==(Utf16View const& other) const { return m_code_units == other.m_code_units; }

    enum class AllowInvalidCodeUnits {
        Yes,
        No,
    };

    String to_utf8(AllowInvalidCodeUnits = AllowInvalidCodeUnits::No) const;

    bool is_null() const;
    bool is_empty() const;
    size_t length_in_code_units() const;
    size_t length_in_code_points() const;

    Utf16CodePointIterator begin() const;
    Utf16CodePointIterator end() const;

    u16 const* data() const;
    u16 code_unit_at(size_t index) const;
    u32 code_point_at(size_t index) const;

    size_t code_point_offset_of(size_t code_unit_offset) const;
    size_t code_unit_offset_of(size_t code_point_offset) const;
    size_t code_unit_offset_of(Utf16CodePointIterator const&) const;

    Utf16View substring_view(size_t code_unit_offset, size_t code_unit_length) const;
    Utf16View substring_view(size_t code_unit_offset) const;

    Utf16View unicode_substring_view(size_t code_point_offset, size_t code_point_length) const;
    Utf16View unicode_substring_view(size_t code_point_offset) const;

    bool validate(size_t& valid_code_units) const;
    bool validate() const;

    bool equals_ignoring_case(Utf16View const&) const;

private:
    u16 const* begin_ptr() const;
    u16 const* end_ptr() const;

    size_t calculate_length_in_code_points() const;

    Span<u16 const> m_code_units;
    mutable Optional<size_t> m_length_in_code_points;
};

}

template<>
struct AK::Formatter<AK::Utf16View> : Formatter<FormatString> {
    ErrorOr<void> format(FormatBuilder& builder, AK::Utf16View const& value);
};

using AK::Utf16View;
