#include "libcarp_fibers.h"
#include "libcarp_platform_windows.h"

void fiber_threadtofiber(fiber* f) {
	f->fiber_address = (voidptr)ConvertThreadToFiber(NULL);
}

void fiber_switch(fiber* f) {
	SwitchToFiber((LPVOID)f->fiber_address);
}

void fiber_create(fiber* f, funcptr start_func) {
	f->fiber_address = (voidptr)CreateFiber(0, (LPFIBER_START_ROUTINE)start_func, NULL);
}

void fiber_delete(fiber* f) {
	DeleteFiber((LPVOID)f->fiber_address);
}