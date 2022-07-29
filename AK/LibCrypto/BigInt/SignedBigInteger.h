/*
 * Copyright (c) 2020, the SerenityOS developers.
 *
 * SPDX-License-Identifier: BSD-2-Clause
 */

#pragma once

#include "./AK/Span.h"
#include "./LibCrypto/BigInt/UnsignedBigInteger.h"

namespace Crypto {

class SignedBigInteger {
public:
    SignedBigInteger(i32 x)
        : m_sign(x < 0)
        , m_unsigned_data(abs(x))
    {
    }

    SignedBigInteger(UnsignedBigInteger&& unsigned_data, bool sign)
        : m_sign(sign)
        , m_unsigned_data(move(unsigned_data))
    {
        ensure_sign_is_valid();
    }

    explicit SignedBigInteger(UnsignedBigInteger unsigned_data)
        : m_sign(false)
        , m_unsigned_data(move(unsigned_data))
    {
    }

    SignedBigInteger()
        : m_sign(false)
        , m_unsigned_data()
    {
    }

    String to_base(u16 N) const;

    u32 hash() const;

    void set_bit_inplace(size_t bit_index);

    bool operator==(SignedBigInteger const& other) const;
    bool operator!=(SignedBigInteger const& other) const;
    bool operator<(SignedBigInteger const& other) const;
    bool operator<=(SignedBigInteger const& other) const;
    bool operator>(SignedBigInteger const& other) const;
    bool operator>=(SignedBigInteger const& other) const;

    bool operator==(UnsignedBigInteger const& other) const;
    bool operator!=(UnsignedBigInteger const& other) const;
    bool operator<(UnsignedBigInteger const& other) const;
    bool operator>(UnsignedBigInteger const& other) const;

private:
    void ensure_sign_is_valid();

    bool m_sign{ false };
    UnsignedBigInteger m_unsigned_data;
};

}

inline Crypto::SignedBigInteger operator""_sbigint(char const* string, size_t length);
