#pragma once

#include "./AK/Badge.h"
#include "./AK/RefCounted.h"
#include "./AK/RefPtr.h"
#include "./AK/Span.h"
#include "./AK/Types.h"
#include "./AK/kmalloc.h"

namespace AK {

class StringImpl : public RefCounted<StringImpl> {
public:
    NonnullRefPtr<StringImpl> to_lowercase() const;
    NonnullRefPtr<StringImpl> to_uppercase() const;

    u32 hash() const { return 0; }
};

}
