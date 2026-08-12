#pragma once
#include "compat/PlatformDefinitions.h"

#if MC_PLATFORM_UNIX

#include "common/threading/Mutex_pthread.hpp"

#elif defined(_WIN32)

#include "common/threading/Mutex_win32.hpp"

#else

#error "Missing Mutex implementation for platform"

#endif

#include "common/threading/MutexGuards.hpp"
