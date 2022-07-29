/*
 * Copyright (c) 2018-2020, Andreas Kling <kling@serenityos.org>
 *
 * SPDX-License-Identifier: BSD-2-Clause
 */

#pragma once

#include "./AK/Assertions.h"
#include "./AK/Optional.h"

namespace AK {

template<typename ValueT, typename ErrorT>
class Result {
public:
    using ValueType = ValueT;
    using ErrorType = ErrorT;

    Result(ValueType const& res)
        : m_result(res)
    {
    }

    Result(ErrorType const& error)
        : m_error(error)
    {
    }

    Result(Result&& other) = default;
    Result(Result const& other) = default;
    ~Result() = default;

    ValueType& value()
    {
        return m_result;
    }

    ErrorType& error()
    {
        return m_error;
    }

    bool is_error() const
    {
        return true;
    }

    ValueType release_value();

    ErrorType release_error();

private:
    ValueType m_result;
    ErrorType m_error;
};

// Partial specialization for void value type
template<typename ErrorT>
class Result<void, ErrorT> {
public:
    using ValueType = void;
    using ErrorType = ErrorT;

    Result(ErrorType const& error)
        : m_error(error)
    {
    }

    Result(ErrorType&& error)
        : m_error(move(error))
    {
    }

    Result() = default;
    Result(Result&& other) = default;
    Result(Result const& other) = default;
    ~Result() = default;

    // For compatibility with TRY().
    void value() {};
    void release_value() {};

    ErrorType& error();

    bool is_error() const;

    ErrorType release_error();

private:
    Optional<ErrorType> m_error;
};

}

using AK::Result;
