#pragma once

#include "pch.h"
#include <assert.h>
#define VERIFY assert

#define VERIFY_NOT_REACHED() VERIFY(false)
static constexpr bool TODO = false;
#define TODO() VERIFY(TODO)
