#pragma once

#include <assert.h>
#include "./Platform.h"

//#define VERIFY assert
#define VERIFY(expression) ([&]{ assert(expression); return nullptr; }())

#define VERIFY_NOT_REACHED() VERIFY(false)
static constexpr bool TODO = false;
#define TODO() VERIFY(TODO)
