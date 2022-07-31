#pragma once

#include "Badge.h"
#include "RefCounted.h"
#include "RefPtr.h"
#include "Span.h"
#include "Types.h"
#include "kmalloc.h"

namespace AK {

enum ShouldChomp {
    NoChomp,
    Chomp
};

class StringImpl : public RefCounted<StringImpl> {
public:
    NonnullRefPtr<StringImpl> to_lowercase() const;
    NonnullRefPtr<StringImpl> to_uppercase() const;

    size_t length() const;

    u32 hash() const { return 0; }
};

}
