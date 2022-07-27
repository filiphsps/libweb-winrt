#pragma once

namespace AK {

enum class CaseSensitivity {
    CaseInsensitive,
    CaseSensitive,
};

enum class ReplaceMode {
    All,
    FirstOnly,
};

enum class TrimMode {
    Left,
    Right,
    Both
};

enum class TrimWhitespace {
    Yes,
    No,
};

}

using AK::CaseSensitivity;
using AK::ReplaceMode;
using AK::TrimMode;
using AK::TrimWhitespace;