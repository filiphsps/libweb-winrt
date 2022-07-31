#pragma once

#include <assert.h>
#include "./Platform.h"

// FIXME: Actually verify
#define VERIFY(expression)
//#define VERIFY assert

#define VERIFY_NOT_REACHED() VERIFY(false)
static constexpr bool TODO = false;
#define TODO() VERIFY(TODO)
