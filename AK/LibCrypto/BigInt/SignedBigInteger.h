#pragma once

#include "./AK/Span.h"
#include "./LibCrypto/BigInt/UnsignedBigInteger.h"

namespace Crypto {

class SignedBigInteger {
public:
    String to_base(u16 N) const;
};

}