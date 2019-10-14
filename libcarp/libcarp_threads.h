#pragma once

#include "libcarp.h"

typedef struct {
	voidptr winMutex;
} mutex;

typedef struct {
	uint32 threadID;
	voidptr winThread;
} thread;

// Mutex
LIBCARP_API void mutex_create(mutex* m);
LIBCARP_API void mutex_destroy(mutex* m);

LIBCARP_API void mutex_lock_timeout(mutex* m, uint32 timeout_ms);
LIBCARP_API void mutex_lock(mutex* m);
LIBCARP_API bool mutex_try_lock(mutex* m);

LIBCARP_API void mutex_unlock(mutex* m);

// Thread

LIBCARP_API void thread_create(thread* t, funcptr func, voidptr param);
LIBCARP_API void thread_create_resume(thread* t, funcptr func, voidptr param);

LIBCARP_API bool thread_resume(thread* t);
LIBCARP_API void thread_join(thread* other_thread);
LIBCARP_API void thread_sleep(uint32 ms);
LIBCARP_API NORETURN void thread_exit(uint32 exit_code);