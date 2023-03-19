#pragma once

#include <cerrno>
#include <cstdint>
#include <cstring>

#ifndef _WIN32

#ifndef __cdecl
#define JUNIA_DEFINED___cdecl
#define __cdecl __attribute__((__cdecl__))
#endif

#ifndef errno_t
typedef int errno_t;
#endif

#ifndef rsize_t
typedef size_t rsize_t;
#endif

#endif

// ---------------------------------------------------------------------------------------------------------------------
// ---------------------------------------------------- Declarations ---------------------------------------------------
// ---------------------------------------------------------------------------------------------------------------------

/**
 * @brief Copies the contents on the address of src, including the terminating
 *        null character, to the location that's specified by dest. The
 *        destination string must be large enough to hold the source string and
 *        it's terminating null character. The behaviour is undefined if the
 *        destination and source strings overlap.
 * @param dest Location of the destination string buffer.
 * @param dest_size Size of the destination string buffer in char units. This
 *                  value must be greater than zero and not greater than
 *                  RSIZE_MAX. Ensure that this size accounts for the
 *                  terminating NULL following the string.
 * @param src Null-terminated source string buffer.
 * @return Zero if successful; otherwise, an error.
*/
inline errno_t __cdecl util_strcpy_s(char* dest, rsize_t dest_size, char const* src);

/**
 * @brief Copies the contents on the address of src, including the terminating
 *        null character, to the location that's specified by dest. The
 *        destination string must be large enough to hold the source string and
 *        it's terminating null character. The behaviour is undefined if the
 *        destination and source strings overlap.
 * @param dest Location of the destination string buffer.
 * @param dest_size Size of the destination string buffer in wchar_t units. This
 *                  value must be greater than zero and not greater than
 *                  RSIZE_MAX. Ensure that this size accounts for the
 *                  terminating NULL following the string.
 * @param src Null-terminated source string buffer.
 * @return Zero if successful; otherwise, an error.
*/
inline errno_t __cdecl util_wcscpy_s(wchar_t* dest, rsize_t dest_size, const wchar_t* src);

// ---------------------------------------------------------------------------------------------------------------------
// ---------------------------------------------------- Definitions ----------------------------------------------------
// ---------------------------------------------------------------------------------------------------------------------

inline errno_t __cdecl util_strcpy_s(char* dest, rsize_t dest_size, char const* src)
{
	if (dest_size == 0) return ERANGE;
	if (dest == nullptr) return EINVAL;
	if (src == nullptr)
	{
		dest[0] = '\0';
		return EINVAL;
	}
	size_t i;
	for (i = 0; i < dest_size; i++)
	{
		dest[i] = src[i];
		if (src[i] == '\0') break;
	}
	if (dest[i] != '\0')
	{
		dest[0] = '\0';
		return ERANGE;
	}
	return 0;
}

inline errno_t __cdecl util_wcscpy_s(wchar_t* dest, rsize_t dest_size, const wchar_t* src)
{
	if (dest_size == 0) return ERANGE;
	if (dest == nullptr) return EINVAL;
	if (src == nullptr)
	{
		dest[0] = '\0';
		return EINVAL;
	}
	size_t i;
	for (i = 0; i < dest_size; i++)
	{
		dest[i] = src[i];
		if (src[i] == '\0') break;
	}
	if (dest[i] != '\0')
	{
		dest[0] = '\0';
		return ERANGE;
	}
	return 0;
}

// ---------------------------------------------------------------------------------------------------------------------
// -------------------------------------------------------- END --------------------------------------------------------
// ---------------------------------------------------------------------------------------------------------------------

#ifdef JUNIA_DEFINED___cdecl
#undef __cdecl
#undef JUNIA_DEFINED___cdecl
#endif
