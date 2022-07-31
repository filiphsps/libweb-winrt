/*
 * Copyright (c) 2020, the SerenityOS developers.
 *
 * SPDX-License-Identifier: BSD-2-Clause
 */

#pragma once

#include "./AK/Span.h"
#include "./LibCrypto/BigInt/UnsignedBigInteger.h"

namespace Crypto {

struct SignedDivisionResult;

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

    static SignedBigInteger create_invalid();

    static SignedBigInteger import_data(StringView data);
    static SignedBigInteger import_data(u8 const* ptr, size_t length);

    static SignedBigInteger create_from(i64 value);

    size_t export_data(Bytes, bool remove_leading_zeros = false) const;;

    static SignedBigInteger from_base(u16 N, StringView str);
    String to_base(u16 N) const;

    u64 to_u64() const;
    double to_double() const;

    UnsignedBigInteger const& unsigned_value() const;
    Vector<u32, STARTING_WORD_SIZE> const words() const;
    bool is_negative() const;
    bool is_zero() const;

    void negate();

    void set_to_0();

    void set_to(i32 other);
    void set_to(SignedBigInteger const& other);

    void invalidate();

    bool is_invalid() const;

    size_t length() const;
    size_t trimmed_length();

    SignedBigInteger plus(SignedBigInteger const& other) const;
    SignedBigInteger minus(SignedBigInteger const& other) const;
    SignedBigInteger bitwise_or(SignedBigInteger const& other) const;
    SignedBigInteger bitwise_and(SignedBigInteger const& other) const;
    SignedBigInteger bitwise_xor(SignedBigInteger const& other) const;
    SignedBigInteger bitwise_not() const;
    SignedBigInteger shift_left(size_t num_bits) const;
    SignedBigInteger multiplied_by(SignedBigInteger const& other) const;
    SignedDivisionResult divided_by(SignedBigInteger const& divisor) const;

    SignedBigInteger plus(UnsignedBigInteger const& other) const;
    SignedBigInteger minus(UnsignedBigInteger const& other) const;
    SignedBigInteger multiplied_by(UnsignedBigInteger const& other) const;
    SignedDivisionResult divided_by(UnsignedBigInteger const& divisor) const;

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

struct SignedDivisionResult {
    Crypto::SignedBigInteger quotient;
    Crypto::SignedBigInteger remainder;
};

}

template<>
struct AK::Formatter<Crypto::SignedBigInteger> : AK::Formatter<Crypto::UnsignedBigInteger> {
    ErrorOr<void> format(FormatBuilder&, Crypto::SignedBigInteger const&);
};

inline Crypto::SignedBigInteger operator""_sbigint(char const* string, size_t length);
