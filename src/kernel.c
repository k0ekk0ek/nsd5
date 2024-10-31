/*
 * kernel.c
 *
 * Copyright (c) 2024, NLnet Labs. All rights reserved.
 *
 * SPDX-License-Identifier: BSD-3-Clause
 *
 */
#include <stdint.h>
#include <strings.h>

#include "kernel.h"
#include "schema.h"

#if NSD_HAVE_HASWELL
extern const nsd_type_descriptor_t *nsd_haswell_descriptors;
#endif

#if NSD_HAVE_WESTMERE
extern const nsd_type_descriptor_t *nsd_westmere_descriptors;
#endif

extern const nsd_type_descriptor_t *nsd_fallback_descriptors;

static const nsd_kernel_t kernels[] = {
#if DNS_HAVE_HASWELL
  { "haswell", AVX2, nsd_haswell_descriptors },
#endif
#if DNS_HAVE_WESTMERE
  { "westmere", SSE42 | PCLMULQDQ, nsd_westmere_descriptors },
#endif
  { "fallback", DEFAULT, nsd_fallback_descriptors }
};


const nsd_kernel_t *nsd_select_kernel(const char *name)
{
  const uint32_t supported = detect_supported_architectures;
  const size_t length = sizeof(kernels) / sizeof(kernels[0]);
  size_t choice = 0;

  for (; name && choice < length; choice++)
    if (strcasecmp(name, kernels[choice].name) == 0)
      break;

  if (choice == length)
    choice = 0;

  for (; choice < length; choice++)
    if ((kernels[choice].instruction_set & supported) == kernels[choice].instruction_set)
      return &kernels[choice];

  return &kernels[length - 1];
}
