#pragma once

#include "./AK/Assertions.h"
#include "./AK/Error.h"
#include "./AK/Span.h"
#include "./AK/Types.h"

namespace AK {
namespace Detail {

template<size_t inline_capacity>
class ByteBuffer {
public:
    ByteBuffer() = default;

    u8* data();
};

}
}