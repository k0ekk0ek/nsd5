/*
 * bits.h -- haswell implementation of bit manipulation instructions
 *
 * Copyright (c) 2024, NLnet Labs. All rights reserved.
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */
#ifndef NSD_BITS_H
#define NSD_BITS_H

#include <stdbool.h>
#include <stdint.h>
#include <immintrin.h>

nsd_no_sanitize_undefined
static nsd_really_inline uint64_t nsd_trailing_zeros_u64(uint64_t mask)
{
  return (uint64_t)_tzcnt_u64(mask);
}

static nsd_really_inline uint64_t nsd_leading_zeros_u64(uint64_t mask)
{
  return (uint64_t)_lzcnt_u64(mask);
}

#endif // NSD_BITS_H
