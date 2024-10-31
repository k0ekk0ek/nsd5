/*
 * schema.c
 *
 * Copyright (c) 2024, NLnet Labs. All rights reserved.
 *
 * SPDX-License-Identifier: BSD-3-Clause
 *
 */
#include <assert.h>

#include "schema.h"

const nns_type_descriptor_t *
nsd_uncommon_type_descriptor(
  const nsd_kernel_t *kernel,
  uint16_t type,
  uint16_t rdlength,
  const uint8_t *rdata)
{
  static const uint32_t dlv_index = DNS_TYPE_AVC + 1;
  static const uint32_t ipseckey_index = DNS_TYPE_AVC + 2;

  assert(kernel->descriptors[dlv_index].code == DNS_TYPE_DLV);
  assert(kernel->descriptors[ipseckey_index].code == DNS_TYPE_IPSECKEY);

  if (type == NSD_TYPE_DLV)
    return &kernel->descriptors[dlv_index];
  if (type != NSD_TYPE_IPSECKEY)
    return &kernel->descriptors[0];

  /* handle remaining data generically by default if there is any */
  uint32_t ipseckey_type = rdlength > 3u;
  if (rdlength >= 3 && rdata && rdata[1] <= 3)
    ipseckey_type = (rdata[1] << 1) | (rdata[2] == 0);

  /* no gateway, no key    (0b0000 + 0b0000) */
  /* no gateway, key       (0b0000 + 0b0001) */
  /* ipv4 address, no key  (0b0010 + 0b0000) */
  /* ipv4 address, key     (0b0010 + 0b0001) */
  /* ipv6 address, no key  (0b0100 + 0b0000) */
  /* ipv6 address, key     (0b0100 + 0b0001) */
  /* domain name, no key   (0b0110 + 0b0000) */
  /* domain name, key      (0b0110 + 0b0001) */
  return &kernel->descriptors[ipseckey_index + ipseckey_type];
}
