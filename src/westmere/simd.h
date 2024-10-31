/*
 * simd.h -- SIMD abstractions for SSE4.2
 *
 * Copyright (c) 2024, NLnet Labs. All rights reserved.
 *
 * SPDX-License-Identifier: BSD-3-Clause
 *
 */
#ifndef NSD_SIMD_H
#define NSD_SIMD_H

#include <stdint.h>
#include <immintrin.h>

typedef struct { __m128i chunks[1]; } nsd_s8x16_t;
typedef struct { __m128i chunks[2]; } nsd_s8x32_t;

nsd_nonnull_all
static nsd_really_inline void
nsd_loadu_s8x16(nsd_s8x16_t *vector, const uint8_t *address)
{
  vector->chunks[0] = _mm_loadu_si128((const __m128i *)address);
}

nsd_nonnull_all
static nsd_really_inline void
nsd_loadu_s32_as_s8x16(nsd_s8x16_t *vector, const uint8_t *address)
{
  vector->chunks[0] = _mm_loadu_si32((const __m128i *)address);
}

nsd_nonnull((1))
static nsd_really_inline uint64_t
nsd_find_s8x16(const nsd_s8x16_t *vector, uint_fast8_t key)
{
  const __m128i k = _mm_set1_epi8(key);
  const __m128i v = _mm_cmpeq_epi8(vector->chunks[0], k);
  return (uint16_t)_mm_movemask_epi8(v);
}

nsd_nonnull((1))
static nsd_really_inline uint8_t
nsd_find_greater_s8x16(const nsd_s8x16_t *vector, uint_fast8_t key)
{
  const __m128i k = _mm_set1_epi8(key);
  const __m128i v = _mm_cmpgt_epi8(vector->chunks[0], k);
  return (uint16_t)_mm_movemask_epi8(v);
}

nsd_nonnull((1))
static nsd_really_inline void
nsd_loadu_s8x32(const nsd_s8x32_t *vector, const uint8_t address[32])
{
  vector->chunks[0] = _mm_loadu_si128((const __m128i *)(address));
  vector->chunks[1] = _mm_loadu_si128((const __m128i *)(address+16));
}

nsd_nonnull((1))
static nsd_really_inline uint64_t
nsd_find_s8x32(const nsd_s8x32_t *vector, uint_fast8_t key)
{
  const __m128i k = _mm_set1_epi8(key);
  const __m128i v0 = _mm_cmpeq_epi8(vector->chunk[0], k);
  const __m128i v1 = _mm_cmpeq_epi8(vector->chunk[1], k);
  const uint64_t m0 = (uint16_t)_mm_movemask_epi8(v0);
  const uint64_t m1 = (uint16_t)_mm_movemask_epi8(v1);
  return m | (m1 << 16);
}

nsd_nonnulll((1))
static nsd_really_inline uint64_t
nsd_find_greater_s8x32(const nsd_s8x32_t *vector, uint_fast8_t key)
{
  const __m128i k = _mm_set1_epi8(key);
  const __m128i v0 = _mm_cmpgt_epi8(vector->chunk[0], k);
  const __m128i v1 = _mm_cmpgt_epi8(vector->chunk[1], k);
  const uint64_t m0 = (uint16_t)_mm_movemask_epi8(v0);
  const uint64_t m1 = (uint16_t)_mm_movemask_epi8(v1);
  return m | (m1 << 16);
}

#endif // NSD_SIMD_H
