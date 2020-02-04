#include "libcarp_basics.h"
#include "libcarp_platform_windows.h"

libcarp_array* array_create(int32 count) {
	voidptr mem = (voidptr)GlobalAlloc(GMEM_FIXED, (SIZE_T)(count + sizeof(libcarp_array)));
	libcarp_array* array_ptr = (libcarp_array*)mem;
	array_ptr->count = count;
	return array_ptr;
}

int32 array_length(libcarp_array* a) {
	return a->count;
}

void array_free(libcarp_array* a) {
	GlobalFree((HGLOBAL)a);
}

voidptr array_index(libcarp_array* a, int32 idx, int32 element_size) {
	size_t mem = (size_t)(a + sizeof(libcarp_array));
	return (voidptr)(mem + element_size * idx);
}
