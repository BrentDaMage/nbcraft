#pragma once
#include "compat/PlatformDefinitions.h"

#if MC_PLATFORM_UNIX

// pthread approach (Unix)
#include "common/threading/ThreadLocal_pthread.hpp"

#elif defined(_WIN32)

// TLS approach (Windows XP and newer)
#include "common/threading/ThreadLocal_tls.hpp"

// FLS approach (Windows Vista and newer)
//#include "common/threading/ThreadLocal_fls.hpp"

#else

#error "Missing ThreadLocal implementation for platform"

#endif
