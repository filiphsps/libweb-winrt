#pragma once

#include "./AK/Badge.h"
#include "./AK/RefCounted.h"
#include "./AK/RefPtr.h"
#include "./AK/Span.h"
#include "./AK/Types.h"

namespace AK {

class StringImpl : public RefCounted<StringImpl> {

};

}