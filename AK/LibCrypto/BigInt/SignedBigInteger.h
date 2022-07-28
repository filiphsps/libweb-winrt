#pragma once

#include "./AK/Span.h"
#include "./LibCrypto/BigInt/UnsignedBigInteger.h"

namespace Crypto {

class SignedBigInteger {
    String to_base(u16 N) const;
};

}