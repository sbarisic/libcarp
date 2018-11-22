#pragma comment(lib, "libcarp.lib")

#include <libcarp.h>
#include <libcarp_syscalls.h>

int main(int argc, const char** argv) {
	voidptr mem = libcarp_pages_alloc(1);

	libcarp_pages_free(mem);

	return 0;
}