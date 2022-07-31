/*
 * Copyright (c) 2018-2020, Andreas Kling <kling@serenityos.org>
 *
 * SPDX-License-Identifier: BSD-2-Clause
 */

#pragma once

#include "./AK/Endian.h"
#include "./AK/Format.h"
#include "./AK/Optional.h"
#include "./AK/StringView.h"
#include "./AK/Vector.h"
#include "./AK/String.h"

namespace AK {

class IPv4Address {
    enum class SubnetClass : int {
        A = 0,
        B,
        C,
        D
    };

public:
    using in_addr_t = u32;

    constexpr IPv4Address() = default;

    constexpr IPv4Address(u32 a, u32 b, u32 c, u32 d)
    {
        m_data = (d << 24) | (c << 16) | (b << 8) | a;
    }

    constexpr IPv4Address(const u8 data[4])
    {
        m_data = (u32(data[3]) << 24) | (u32(data[2]) << 16) | (u32(data[1]) << 8) | u32(data[0]);
    }

    constexpr IPv4Address(NetworkOrdered<u32> address)
        : m_data(address)
    {
    }

    constexpr u8 operator[](int i) const
    {
        VERIFY(i >= 0 && i < 4);
        return octet(SubnetClass(i));
    }

    String to_string() const
    {
        return String::formatted("{}.{}.{}.{}",
            octet(SubnetClass::A),
            octet(SubnetClass::B),
            octet(SubnetClass::C),
            octet(SubnetClass::D));
    }

    String to_string_reversed() const
    {
        return String::formatted("{}.{}.{}.{}",
            octet(SubnetClass::D),
            octet(SubnetClass::C),
            octet(SubnetClass::B),
            octet(SubnetClass::A));
    }

    static Optional<IPv4Address> from_string(StringView string);

    static constexpr IPv4Address netmask_from_cidr(int cidr);

    constexpr in_addr_t to_in_addr_t() const { return m_data; }
    constexpr u32 to_u32() const { return m_data; }

    constexpr bool operator==(IPv4Address const& other) const = default;
    constexpr bool operator!=(IPv4Address const& other) const = default;

    constexpr bool is_zero() const
    {
        return m_data == 0u;
    }

private:
    constexpr u32 octet(const SubnetClass subnet) const
    {
        NetworkOrdered<u32> address(m_data);
        constexpr auto bits_per_byte = 8;
        auto const bits_to_shift = bits_per_byte * int(subnet);
        return (m_data >> bits_to_shift) & 0x0000'00FF;
    }

    u32 m_data {};
};

static_assert(sizeof(IPv4Address) == 4);

template<>
struct Traits<IPv4Address> : public GenericTraits<IPv4Address> {
    static constexpr unsigned hash(IPv4Address const& address) { return int_hash(address.to_u32()); }
};

template<>
struct Formatter<IPv4Address> : Formatter<String> {
    ErrorOr<void> format(FormatBuilder& builder, IPv4Address value)
    {
        return Formatter<String>::format(builder, value.to_string());
    }
};

}

using AK::IPv4Address;
