/*
 * treeops.h
 *
 * Copyright (c) 2024, NLnet Labs. All rights reserved.
 *
 * SPDX-License-Identifier: BSD-3-Clause
 *
 */
#ifndef TREEOPS_H
#define TREEOPS_H

#include <assert.h>
#include <stdint.h>

nsd_nonnull((1))
static nsd_really_inline nsd_node_t *
nsd_find_node4(const nsd_node4_t *node, uint_fast8_t key, uint_fast8_t width)
{
  assert(width && width <= 4);

  if (node->keys[0] == key)
    return node->children[0];

  for (uint_fast8_t i = 1; i < width; i++) {
    if (node->keys[i] == key)
      return node->children[i];
    if (node->keys[i] > key)
      break;
  }

  return NULL;
}

nsd_nonnull((1))
static nsd_really_inline nsd_node_t *
nsd_find_node16(
  const nsd_node16_t *node, uint_fast8_t key, uint_fast8_t width)
{
  // implement
}

nsd_nonnull((1))
static nsd_really_inline nsd_node_t *
nsd_find_node32(
  const nsd_node32_t *node, uint_fast8_t key, uint_fast8_t width)
{
  // implement
}

#endif // TREEOPS_H
