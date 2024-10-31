/*
 * kernel.h
 *
 * Copyright (c) 2024, NLnet Labs. All rights reserved.
 *
 * SPDX-License-Identifier: BSD-3-Clause
 *
 */
#ifndef NSD_KERNEL_H
#define NSD_KERNEL_H

#include <stdint.h>

#include "macros.h"

struct nsd_type_descriptor;

typedef struct nsd_kernel nsd_kernel_t;
struct nsd_kernel {
  const char *name;
  uint32_t instruction_set;
  const struct nsd_type_descriptor *descriptors;
};

nsd_returns_nonnull
const nsd_kernel_t *nsd_select_kernel(const char *name);

#endif // NSD_KERNEL_H
