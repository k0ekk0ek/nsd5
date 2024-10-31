/*
 * bits.h -- westmere implementation of bit manipulation instructions
 *
 * Copyright (c) 2024, NLnet Labs. All rights reserved.
 *
 * SPDX-License-Identifier: BSD-3-Clause
 *
 */
#ifndef NSD_BITS_H
#define NSD_BITS_H

#include <stdbool.h>
#include <stdint.h>

nsd_no_sanitize_undefined
static nsd_always_inline uint64_t nsd_trailing_zeros_u64(uint64_t mask)
{
#if nsd_has_builtin(__builtin_ctzll)
  return (uint64_t)__builtin_ctzll(mask);
#else
  uint64_t count;
  asm("bsfq %[mask], %[count]"
      : [count] "=r" (count)
      : [mask] "mr" (mask));
  return count;
#endif
}

static nsd_really_inline uint64_t nsd_leading_zeros_u64(uint64_t mask)
{
#if nsd_has_builtin(__builtin_clzll)
  return (uint64_t)__builtin_clzll(mask);
#else
  uint64_t count;
  asm("bsrq %[mask], %[count]" :
      [count] "=r" (count) :
      [mask] "mr" (mask));
  return 63ull ^ count;
#endif
}

#endif // NSD_BITS_H
