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
	voidptr winMutex = (voidptr)InterlockedExchange((volatile LONG*)&m->winMutex, (LONG)NULL);

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