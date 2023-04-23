#pragma once

#ifndef JUNIAFUNC_EXPORT

#if defined(_MSC_VER)
// msvc
#define JUNIAFUNC_EXPORT extern "C" __declspec(dllexport)

#elif defined(__clang__) || defined(__GNUC__)
// clang or gcc
#define JUNIAFUNC_EXPORT extern "C" __attribute__((visibility("default")))

#else
// unknown compiler
#pragma message(": warning: Unknown compiler. Omitting export semantics.")
#endif

#endif
