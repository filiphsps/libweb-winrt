#pragma once

#include "pch.h"
#include <string>

using String = std::string;

String operator "" sv(char const* cstring, size_t length) {
    return String(cstring);
}