#pragma once

// MACHINE_64 - 64 bit machine target
// MACHINE_32 - 32 bit machine target

// LIBCARP_WINDOWS_32 - 32 bit windows
// LIBCARP_WINDOWS_64 - 64 bit windows

// LIBCARP_MSVC_COMPILER - MSVC compiler
// LIBCARP_CPP - Compiling as C++?

#define LIBCARP_SYSCALL_API
#define LIBCARP_API

#ifdef _WIN32
#ifdef _WIN64
#define LIBCARP_WINDOWS_64
#define MACHINE_64
#else
#define LIBCARP_WINDOWS_32
#define MACHINE_32
#endif
#endif

#ifdef _MSC_VER
#define LIBCARP_MSVC_COMPILER
#endif

#ifdef __cplusplus
#define LIBCARP_CPP
#endif

// Attributes
#ifdef LIBCARP_MSVC_COMPILER
#define ALIGN(n) __declspec(align(n))
#define NAKED __declspec(naked)
#define NOALIAS __declspec(noalias)
#define RESTRICT __declspec(restrict)
#define NOINLINE __declspec(noinline)
#define INLINE __declspec(inline)
#define NORETURN __declspec(noreturn)
#define THREADLOCAL __declspec(thread)
#endif

#ifdef LIBCARP_MSVC_COMPILER
typedef __int8 int8;
typedef __int16 int16;
typedef __int32 int32;
typedef __int64 int64;

typedef unsigned __int8 uint8;
typedef unsigned __int16 uint16;
typedef unsigned __int32 uint32;
typedef unsigned __int64 uint64;
#endif

#ifndef LIBCARP_CPP
typedef _Bool bool;

#define true 1
#define false 0
#endif

#ifdef MACHINE_32
typedef uint32 size_t;
#elif MACHINE_64
typedef uint64 size_t;
#endif

typedef uint8 byte;

typedef void* voidptr;
typedef voidptr funcptr;

#define NULL ((voidptr)0)