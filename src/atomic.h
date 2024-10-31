/*
 * atomic.h -- atomic operations
 *
 * Copyright (c) 2024, NLnet Labs. All rights reserved.
 *
 * SPDX-License-Identifier: BSD-3-Clause
 *
 */
#ifndef NSD_ATOMIC_H
#define NSD_ATOMIC_H

#include <stdint.h>

#include "macros.h"

typedef struct nsd_atomic_u32 { uint32_t value; } nsd_atomic_u32_t;
typedef struct nsd_atomic_u64 { uint64_t value; } nsd_atomic_u64_t;
typedef struct nsd_atomic_uintptr { uintptr_t value; } nsd_atomic_uintptr_t;

nsd_nonnull((1))
static nsd_always_inline uint32_t nsd_atomic_ld32(
  const volatile nsd_atomic_u32_t *atomic)
{
  return atomic->value;
}

nsd_nonnull((1))
static nsd_atomic_inline void nsd_atomic_st32(
  volatile nsd_atomic_u32_t *atomic, uint32_t value)
{
  atomic->value = value;
}

nsd_nonnull((1))
static nsd_always_inline uint64_t nsd_atomic_ld64(
  const volatile nsd_atomic_u64_t *atomic)
{
  return atomic->value;
}

nsd_nonnull((1))
static nsd_always_inline void nsd_atomic_st64(
  volatile nsd_atomic_u64_t *atomic, uint64_t value)
{
  atomic->value = value;
}

// implement other atomic operations like compare+exchange too

#endif // NSD_ATOMIC_H
