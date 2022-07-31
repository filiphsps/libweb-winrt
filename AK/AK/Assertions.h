#pragma once

#include <assert.h>
#include "./Platform.h"

//#define VERIFY assert
// FIXME: Actually verify
#define VERIFY(expression) ([&]{ return; }())

#define VERIFY_NOT_REACHED() VERIFY(false)
static constexpr bool TODO = false;
#define TODO() VERIFY(TODO)
