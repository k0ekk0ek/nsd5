/*
 * region-allocator.h -- region allocator
 *
 * Copyright (c) 2024, NLnet Labs. All rights reserved.
 *
 * SPDX-License-Identifier: BSD-3-Clause
 *
 */
#ifndef NSD_REGION_ALLOCATOR_H
#define NSD_REGION_ALLOCATOR_H

#include "allocator.h"

typedef struct nsd_region_allocator nsd_region_allocator_t;
struct nsd_region_allocator {
  nsd_allocator_t allocator; // adhere to allocator "interface"
  // implement
};

#endif // NSD_REGION_ALLOCATOR_H
