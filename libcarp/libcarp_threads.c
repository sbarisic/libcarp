#include "libcarp_threads.h"
#include "libcarp_platform_windows.h"

// Mutex

void mutex_create(mutex* m) {
	m->winMutex = (voidptr)CreateMutex(NULL, FALSE, NULL);

	if (m->winMutex == NULL) {
		// TODO: Error
		return;
	}
}

void mutex_destroy(mutex* m) {
	voidptr winMutex = InterlockedExchange(&m->winMutex, NULL);

	if (winMutex == NULL) {
		// TODO: Error
		return;
	}

	CloseHandle((HANDLE)winMutex);
}

void mutex_lock_timeout(mutex* m, uint32 timeout_ms) {
	DWORD result = WaitForSingleObject((HANDLE)m->winMutex, (DWORD)timeout_ms);

	if (!((result == WAIT_OBJECT_0) || (result == WAIT_ABANDONED))) {
		// TODO: Error
		return;
	}
}

void mutex_lock(mutex* m) {
	mutex_lock_timeout(m, INFINITE);
}

bool mutex_try_lock(mutex* m) {
	DWORD result = WaitForSingleObject((HANDLE)m->winMutex, 0);
	return (result == WAIT_OBJECT_0) || (result == WAIT_ABANDONED);
}

void mutex_unlock(mutex* m) {
	ReleaseMutex((HANDLE)m->winMutex);
}

// Thread

void thread_create(thread* t, funcptr func, voidptr param) {
	DWORD threadID;
	HANDLE winThread = CreateThread(NULL, 0, (LPTHREAD_START_ROUTINE)func, param, CREATE_SUSPENDED, &threadID);

	if (winThread == NULL) {
		// TODO: Error
		return;
	}

	t->winThread = winThread;
	t->threadID = threadID;
}

void thread_create_resume(thread* t, funcptr func, voidptr param) {
	thread_create(t, func, param);
	thread_resume(t);
}

NORETURN void thread_exit(uint32 exit_code) {
	ExitThread((DWORD)exit_code);
}

bool thread_resume(thread* t) {
	if (t->winThread == NULL) {
		// TODO: Error
		return false;
	}

	return ResumeThread(t->winThread) != -1;
}

void thread_join(thread* other_thread) {
	if (other_thread->winThread == NULL) {
		// TODO: Error
		return;
	}

	DWORD result = WaitForSingleObject(other_thread->winThread, INFINITE);

	if (result == WAIT_FAILED) {
		// TODO: Error
		return;
	}
}

void thread_sleep(uint32 ms) {
	Sleep((DWORD)ms);
}

typedef struct {
	voidptr stack_base;
	voidptr stack_limit;

	jmp_buf jmp;

} thread_fork_data;

static void fork_child(volatile thread_fork_data* data) {
	NT_TIB* TIB = (NT_TIB*)__readfsdword(0x18);

	int64 stack_len = (int64)data->stack_base - (int64)data->stack_limit;
	memcpy(TIB->StackLimit, data->stack_limit, stack_len);

	longjmp(data->jmp, 1);
}

int32 thread_fork() {
	volatile thread_fork_data data = { 0 };
	NT_TIB* TIB = (NT_TIB*)__readfsdword(0x18);

	data.stack_base = (voidptr)TIB->StackBase;
	data.stack_limit = (voidptr)TIB->StackLimit;

	int setjmp_result = 0;

	if (!(setjmp_result = setjmp(data.jmp))) {
		thread child_thread;
		thread_create_resume(&child_thread, fork_child, &data);

		while (true)
			;

		return 1;
	} else {

		while (true) {

		}
		return 0;
	}

	return -1;
}