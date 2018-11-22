#pragma comment(lib, "libcarp.lib")

#include <libcarp.h>
#include <libcarp_syscalls.h>
#include <libcarp_threads.h>

#include <stdio.h>

void A(voidptr arg) {
	for (size_t i = 0; i < 4; i++) {
		printf("A: Hello %i!\n", i);
		thread_sleep(200);
	}
}

void B(voidptr arg) {
	for (size_t i = 0; i < 8; i++) {
		printf("B: Hello %i!\n", i);
		thread_sleep(94);
	}
}

int main(int argc, const char** argv) {
	if (thread_fork() == 0) {
		printf("thread child.\n");
	} else {
		printf("THREAD PARENT!\n");
	}

	printf("done!");
	while (true) {
	}
	return 0;
}