/*
 * treeops.h
 *
 * Copyright (c) 2024, NLnet Labs. All rights reserved.
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */
#ifndef TREEOPS_H
#define TREEOPS_H

#include <assert.h>
#include <stdint.h>

nsd_nonnull((1))
static nsd_always_inline nsd_node_t *
nsd_find_node4(const nsd_node4_t *node, uint_fast8_t key)
{
  nsd_s8x16_t keys;

  assert(node->base.width && node->base.width <= 4u);
  nsd_loadu_s32_in_s8x16(&keys, node->keys);
  uint64_t mask = nsd_find_8x16(&keys, key);
  mask &= (1llu << node->base.width) - 1;
  if (!mask)
    return NULL;
  const uint64_t index = nsd_trailing_zeros_u64(mask);
  return node->children[index];
}

nsd_nonnull((1))
static nsd_really_inline nsd_node_t *
nsd_find_node16(const nsd_node16_t *node, uint_fast8_t key)
{
  nsd_s8x16_t keys;

  assert(node->base.width > 4u && node->base.width <= 16u);
  nsd_loadu_s8x16(&keys, node->keys);
  uint64_t mask = nsd_find_8x16(&keys, key);
  mask &= (1llu << width) - 1;
  if (!mask)
    return NULL;
  const uint64_t index = nsd_trailing_zeros_u64(mask);
  return node->children[index];
}

nsd_nonnull((1))
static nsd_always_inline nsd_node_t *
nsd_find_node32(const nsd_node32_t *node, uint_fast8_t key)
{
  nsd_s8x32_t keys;

  assert(node->base.width > 16u && node->base.width <= 32u);
  nsd_loadu_s8x32(&keys, node->keys);
  uint64_t mask = nsd_find_s8x32(&keys, key);
  mask &= (1llu << width) - 1;
  if (!mask)
    return NULL;
  const uint64_t index = nsd_trailing_zeros_u64(mask);
  return node->children[index];
}

#endif // TREEOPS_H
