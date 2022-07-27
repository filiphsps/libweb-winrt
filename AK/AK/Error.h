#pragma once

#include "./AK/Optional.h"
#include "./AK/StringView.h"
#include "./AK/Try.h"
#include "./AK/Variant.h"

namespace AK {

class Error {
};

template<typename T, typename ErrorType>
class ErrorOr final : public Variant<T, ErrorType>{
};

}

using AK::Error;
using AK::ErrorOr;