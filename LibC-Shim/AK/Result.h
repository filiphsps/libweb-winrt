/*
 * Copyright (c) 2018-2020, Andreas Kling <kling@serenityos.org>
 *
 * SPDX-License-Identifier: BSD-2-Clause
 */

#pragma once

#include "Assertions.h"
#include "Optional.h"

namespace AK {

template<typename ValueT, typename ErrorT>
class Result {
public:
    using ValueType = ValueT;
    using ErrorType = ErrorT;

    Result(ValueType const& res)
    {
    }

    Result(ErrorType const& error)
    {
    }

    Result()
    {
    }

    Result(Result&& other) = default;
    Result(Result const& other) = default;
    ~Result() = default;

    ValueType& value();

    ErrorType& error();

    bool is_error() const;

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
    {
    }

    Result(ErrorType&& error)
    {
    }

    Result()
    {
    }

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
