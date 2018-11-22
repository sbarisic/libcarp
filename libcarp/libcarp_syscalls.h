#pragma once

#include "libcarp.h"

LIBCARP_SYSCALL_API voidptr libcarp_pages_alloc(uint32 count);
LIBCARP_SYSCALL_API void libcarp_pages_free(voidptr mem);