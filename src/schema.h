/*
 * schema.h -- type descriptor definitions
 *
 * Copyright (c) 2024, NLnet Labs. All rights reserved.
 *
 * SPDX-License-Identifier: BSD-3-Clause
 *
 */
#ifndef NSD_SCHEMA_H
#define NSD_SCHEMA_H

#include <stdbool.h>
#include <stdint.h>

#include "macros.h"
#include "kernel.h"

typedef struct nsd_rdata_descriptor nsd_rdata_descriptor_t;
struct nsd_rdata_descriptor {
  // FIXME: introduce a basic type to be used in mnemonics too
  //        for convenient printing.
  struct { dns_string_t key; } name;
  uint32_t length;
  // implement
};

typedef struct nsd_mnemonic nsd_mnemonic_t;
struct nsd_mnemonic {
  struct {
    char data[16];
    size_t length;
  } key;
  uint32_t value;
};

typedef struct nsd_type_descriptor nsd_type_descriptor_t;
struct nsd_type_descriptor;

#if 0
typedef int32_t (*dns_read_rdata_t)(
  const nsd_type_descriptor_t *descriptor,
  // FIXME: need more context if format/syntax errors need to be reported
  nsd_domain_table_t *owners,
  nsd_buffer_t *packet,
  uint16_t rdlength,
  uint8_t **rdata,
  uint32_t flags);

typedef int32_t (*nsd_write_rdata_t)(
  const nsd_type_descriptor_t *descriptor,
  // parameters
  );

typedef int32_t (*nsd_parse_rdata_t)(
  // provide full nsd context too
  nsd_parser_t *parser,
  const nsd_type_descriptor_t *descriptor,
  nsd_buffer_t *packet);
#endif

struct nsd_type_descriptor {
  nsd_menmonic_t name;
  uint16_t defined_in;
  uint8_t obsolete;
  uint8_t experimental;
  uint8_t compressible;
  uint8_t normalize;
#if 0
  nsd_read_rdata_t read_rdata;
  nsd_write_rdata_t write_rdata;
  nsd_parse_rdata_t parse_rdata;
#endif
  struct {
    size_t count;
    nsd_rdata_descriptor_t *fields;
  } rdata;
};

nsd_nonnull((1,4))
nsd_returns_nonnull
const nsd_uncommon_type_descriptor(
  const nsd_kernel_t *kernel,
  uint16_t type,
  uint16_t rdlength,
  const uint8_t *rdata);

nsd_nonnull((1,4))
nsd_returns_nonnull
static nsd_always_inline const nsd_type_descriptor_t *
nsd_type_descriptor(
  const nsd_kernel_t *kernel,
  uint16_t type,
  uint16_t rdlength,
  const uint8_t *rdata)
{
  if (nsd_unlikely((type > DNS_TYPE_AVC) || type == DNS_TYPE_IPSECKEY))
    return nsd_uncommon_type_descriptor(kernel, type, rdlength, rdata);
  return &kernel->descriptors[type];
}

#endif // NSD_SCHEMA_H
