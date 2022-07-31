/*
 * Copyright (c) 2018-2020, Andreas Kling <kling@serenityos.org>
 * Copyright (c) 2022, the SerenityOS developers.
 *
 * SPDX-License-Identifier: BSD-2-Clause
 */

#pragma once

#include "./AK/IPv4Address.h"
#include <string.h>

namespace Core {

class SocketAddress {
public:
    enum class Type {
        Invalid,
        IPv4,
        Local
    };

    SocketAddress() = default;
    SocketAddress(IPv4Address const& address)
        : m_type(Type::IPv4)
        , m_ipv4_address(address)
    {
    }

    SocketAddress(IPv4Address const& address, u16 port)
        : m_type(Type::IPv4)
        , m_ipv4_address(address)
        , m_port(port)
    {
    }

    static SocketAddress local(String const& address);

    Type type() const { return m_type; }
    bool is_valid() const { return m_type != Type::Invalid; }
    IPv4Address ipv4_address() const { return m_ipv4_address; }
    u16 port() const { return m_port; }

    String to_string() const;

private:
    Type m_type { Type::Invalid };
    IPv4Address m_ipv4_address;
    u16 m_port { 0 };
    String m_local_address;
};

}

template<>
struct AK::Formatter<Core::SocketAddress> : Formatter<String> {
    ErrorOr<void> format(FormatBuilder& builder, Core::SocketAddress const& value)
    {
        return Formatter<String>::format(builder, value.to_string());
    }
};
