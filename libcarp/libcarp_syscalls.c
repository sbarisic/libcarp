#include "libcarp_syscalls.h"

#if defined(LIBCARP_WINDOWS_32) || defined(LIBCARP_WINDOWS_64)
#pragma warning(push, 0)
#include <Windows.h>
#pragma warning(pop)
#endif

static size_t page_size = 0;

voidptr libcarp_pages_alloc(uint32 count) {
	if (page_size == 0) {
		SYSTEM_INFO sys_info;
		GetSystemInfo(&sys_info);

		page_size = (size_t)sys_info.dwPageSize;
	}

	if (count == 0) {
		// TODO: Error
	}

	voidptr memory = (voidptr)VirtualAlloc((LPVOID)NULL, (SIZE_T)(page_size * count), MEM_COMMIT, PAGE_READWRITE);

	if (memory == NULL) {
		// TODO: Error
	}

	return memory;
}

void libcarp_pages_free(voidptr mem) {
	if (mem == NULL) {
		// TODO: Error
		return;
	}

	if (!VirtualFree(mem, 0, MEM_RELEASE)) {
		// TODO: Error
	}
}