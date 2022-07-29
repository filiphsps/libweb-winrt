/*
 * Copyright (c) 2020, Itamar S. <itamar8910@gmail.com>
 * Copyright (c) 2022, the SerenityOS developers.
 *
 * SPDX-License-Identifier: BSD-2-Clause
 */

#pragma once

#include "./AK/ByteBuffer.h"
#include "./AK/Span.h"
#include "./AK/String.h"
#include "./AK/Types.h"
#include "./AK/Vector.h"

namespace Crypto {

struct UnsignedDivisionResult;
constexpr size_t STARTING_WORD_SIZE = 32;

class UnsignedBigInteger {
public:
    using Word = u32;
    static constexpr size_t BITS_IN_WORD = 32;

    UnsignedBigInteger(Word x) { m_words.append(x); }

    explicit UnsignedBigInteger(Vector<Word, STARTING_WORD_SIZE>&& words)
        : m_words(move(words))
    {
    }

    explicit UnsignedBigInteger(u8 const* ptr, size_t length);

    UnsignedBigInteger() = default;

private:
    friend class UnsignedBigIntegerAlgorithms;
    // Little endian
    // m_word[0] + m_word[1] * Word::MAX + m_word[2] * Word::MAX * Word::MAX + ...
    Vector<Word, STARTING_WORD_SIZE> m_words;

    mutable u32 m_cached_hash{ 0 };

    // Used to indicate a negative result, or a result of an invalid operation
    bool m_is_invalid{ false };

    mutable Optional<size_t> m_cached_trimmed_length;
};

}

inline Crypto::UnsignedBigInteger operator""_bigint(char const* string, size_t length);
