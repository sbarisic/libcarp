#pragma comment(lib, "libcarp.lib")

#include <libcarp.h>
#include <libcarp_syscalls.h>
#include <libcarp_threads.h>
#include <libcarp_fibers.h>

#include <stdio.h>

void Thread1() {
	printf("Thread 1!\n");

	while (true)
		thread_sleep(10);
}

int main() {
	printf("Main thread!\n");

	fiber cur_fiber;
	fiber_threadtofiber(&cur_fiber);

	fiber f1;
	fiber_create(&f1, Thread1);

	fiber_switch(&f1);


	while (true) {
	}

	return 0;
}