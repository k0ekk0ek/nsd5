/*
 * allocator.h
 *
 * Copyright (c) 2024, NLnet Labs. All rights reserved.
 *
 * SPDX-License-Identifier: BSD-3-Clause
 *
 */
#ifndef NSD_ALLOCATOR_H
#define NSD_ALLOCATOR_H

#include "macros.h"

typedef struct nsd_allocator nsd_allocator_t;
struct nsd_allocator;

typedef void *(*nsd_malloc_t)(
  nsd_allocator_t *allocator, size_t size);
typedef void(*nsd_free_t)(
  nsd_allocator_t *allocator, void *ptr);

struct nsd_allocator {
  nsd_malloc_t malloc;
  nsd_free_t free;
  // implement, probably need allocarray, calloc, etc
};

nsd_nonnull((1))
nsd_alloc_size((2, 3))
nsd_warn_unused_result
static nsd_always_inline void *nsd_malloc(
  nsd_allocator_t *allocator, size_t size)
{
  return allocator->malloc(allocator, size);
}

static nsd_always_inline void nsd_free(
  nsd_allocator_t *allocator, void *ptr)
{
  allocator->free(allocator, ptr);
}

#endif // NSD_ALLOCATOR_H
