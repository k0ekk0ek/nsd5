/*
 * tree.h -- Adaptive Radix Trie optimized for domain names
 *
 * Copyright (c) 2024, NLnet Labs. All rights reserved.
 *
 * SPDX-License-Identifier: BSD-3-Clause
 *
 */
#ifndef NSD_TREE_H
#define NSD_TREE_H

#include "macros.h"

typedef struct nsd_node nsd_node_t;
struct nsd_node {
  uint8_t type;
  uint8_t width; // number of child nodes
  struct {
    // a prefix length of 10 octets is prescribed by the paper, but domain
    // names have a maximum length of 255 octets. an unsigned 8-bit integer
    // suffices.
    uint8_t length;
    // domain names are relatively short, a prefix length of 8 bytes is likely
    // enough to cover most cases. unused bytes are set to the character
    // representing the label separator (-128) for convenient comparison.
    uint8_t octets[8];
    uint8_t padding_;
  } prefix;
};

#define NSD_NODE4 (0u)
#define NSD_NODE16 (1u)
#define NSD_NODE32 (2u)
#define NSD_NODE48 (3u)
#define NSD_NODE256 (4u)

typedef struct nsd_node4 nsd_node4_t;
struct nsd_node4 {
  nsd_node_t base;
  uint8_t keys[4];
  nsd_node_t *children[4];
};

typedef struct nsd_node16 nsd_node16_t;
struct nsd_node16 {
  nsd_node_t base;
  uint8_t keys[16];
  nsd_node_t *children[16];
};

typedef struct nsd_node32 nsd_node32_t;
struct nsd_node32 {
  nsd_node_t base;
  uint8_t keys[32];
  nsd_node_t *children[16];
};

typedef struct nsd_node48 nsd_node48_t;
struct nsd_node48 {
  nsd_node_t base;
  uint8_t keys[230];
  nsd_node_t *children[48];
};

typedef struct nsd_node256 nsd_node256_t;
struct nsd_node256 {
  nsd_node_t base;
  nsd_node_t *children[230];
};

static nsd_always_inline bool
nsd_is_tagged_node(const nsd_node_t *node)
{
  return (uintptr_t)node & 1u;
}

static nsd_always_inline nsd_node_t *
nsd_tag_node(const nsd_node_t *node)
{
  return (nsd_node_t *)((uintptr_t)node | 1u);
}

static nsd_always_inline nsd_node_t *
nsd_untag_node(const nsd_node_t *node)
{
  return (nsd_node_t *)((uintptr_t)node & ~1u);
}

#endif // NSD_TREE_H
