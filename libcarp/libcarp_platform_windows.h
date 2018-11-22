#pragma once

#if defined(LIBCARP_WINDOWS_32) || defined(LIBCARP_WINDOWS_64)
#pragma warning(push, 0)
#include <Windows.h>
#include <setjmp.h>
#pragma warning(pop)
#endif