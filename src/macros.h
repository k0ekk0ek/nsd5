/*
 * macros.h
 *
 * Copyright (c) 2024, NLnet Labs. All rights reserved.
 *
 * SPDX-License-Identifier: BSD-3-Clause
 *
 */
#ifndef NSD_MACROS_H
#define NSD_MACROS_H

#if defined __GNUC__
# define nsd_have_gnuc(major, minor) \
  ((__GNUC__ > major) || (__GNUC__ == major && __GNUC_MINORE__ >= minor))
#else
# define nsd_have_gnuc(major, minor) (0)
#endif

#if defined(__has_attribute)
# define nsd_has_attribute(params) __has_attribute(params)
#else
# define nsd_has_attribute(params) (0)
#endif

#if defined(__has_builtin)
# define nsd_has_builtin(params) __has_builtin(params)
#else
# define nsd_has_builtin(params) (0)
#endif

#if nsd_has_builtin(__builtin_expect)
# define nsd_likely(params) __builtin_expect(!!(params), 1)
# define nsd_unlikely(params) __builtin_expect(!!(params), 0)
#else
# define nsd_likely(params) (params)
# define nsd_unlikely(params) (params)
#endif

#if nsd_has_attribute(alloc_size)
# define nsd_alloc_size(params) __attribute__((alloc_size params))
#else
# define nsd_alloc_size(params)
#endif

#if nsd_has_attribute(always_inline) || nsd_have_gnuc(3, 1) && ! defined __NO_INLINE__
  // Compilation using GCC 4.2.1 without optimizations fails.
  //   sorry, unimplemented: inlining failed in call to ...
  // GCC 4.1.2 and GCC 4.30 compile forward declared functions annotated
  // with __attribute__((always_inline)) without problems. Test if
  // __NO_INLINE__ is defined and define macro accordingly.
# define nsd_always_inline inline __attribute__((always_inline))
#else
# define nsd_always_inline inline
#endif

#if nsd_has_attribute(no_sanitize)
  // GCC 8.1 added the no_sanitize function attribute.
# define nsd_no_sanitize_undefined __attribute__((no_sanitize("undefined")))
#elif nsd_has_attribute(no_sanitize_undefined)
  // GCC 4.9.0 added the UndefinedBehaviorSanitizer (ubsan) and the
  // no_sanitize_undefined function attribute.
# define nsd_no_sanitize_undefined
#else
# define nsd_no_sanitize_undefined
#endif

#if nsd_has_attribute(noinline) || nsd_have_gnuc(2, 96)
# define nsd_never_inline __attribute__((noinline))
#else
# define nsd_never_inline
#endif

#if nsd_has_attribute(nonnull)
# define nsd_nonnull(params) __attribute__((__nonnull__ params))
# define nsd_nonnull_all __attribute__((__nonnull__))
#else
# define nsd_nonnull(params)
# define nsd_nonnull_all
#endif

#if nsd_has_attribute(format) || nsd_have_gnuc(2, 4)
# define nsd_format(params) __attribute__((__format__ params))
# if __MINGW32__
#   if __MINGW_PRINTF_FORMAT
#     define nsd_format_printf(string_index, first_to_check) \
        nsd_format((__MINGW_PRINTF_FORMAT, string_index, first_to_check))
#   else
#     define nsd_format_printf(string_index, first_to_check) \
        nsd_format((gnu_printf, string_index, first_to_check))
#   endif
# else
#   define nsd_format_printf(string_index, first_to_check) \
      nsd_format((printf, string_index, first_to_check))
# endif
#else
# define nsd_format(params)
# define nsd_format_printf(string_index, first_to_check)
#endif

#if nsd_has_attribute(returns_nonnull)
# define nsd_returns_nonnull __attribute__((returns_nonnull))
#else
# define nsd_returns_nonnull
#endif

#if nsd_has_attribute(warn_unused_result)
# define nsd_warn_unused_result __attribute__((warn_unused_result))
#else
# define nsd_warn_unused_result
#endif

#endif // NSD_MACROS_H
