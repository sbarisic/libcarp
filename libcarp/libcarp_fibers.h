#pragma once

#include "libcarp.h"

typedef struct {
	voidptr fiber_address;
} fiber;

void fiber_threadtofiber(fiber* f);
void fiber_switch(fiber* f);
void fiber_create(fiber* f, funcptr start_func);
void fiber_delete(fiber* f);