#pragma once

#include "./AK/Assertions.h"

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

private:
    ValueType m_result;
    ErrorType m_error;
};

}

using AK::Result;
