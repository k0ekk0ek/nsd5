#include <assert.h>
#include <stdint.h>
#include <string.h>
#include <stdio.h>
#include <immintrin.h>

#define really_inline inline __attribute__((always_inline))
#define never_inline __attribute__((noinline))

typedef struct node node_t;
struct node {
  uint8_t type;
};

#define NODE4 (0u)

typedef struct node4 node4_t;
struct node4 {
  node_t base;
  uint8_t keys[4];
  node_t *children[4];
};

static never_inline node_t *find_node4(const node4_t *node, uint8_t key)
{
  assert(node->base.type == NODE4);

  for (uint32_t i=0; i < 4; i++) {
    if (node->keys[i] == key)
      return node->children[i];
  }

  return NULL;
}

static never_inline node_t *find_node4_unrolled(const node4_t *node, uint8_t key)
{
  const uint32_t k1 = (key == node->keys[0]);
  const uint32_t k2 = (key == node->keys[1]) << 1;
  const uint32_t k3 = (key == node->keys[2]) << 2;
  const uint32_t k4 = (key == node->keys[3]) << 3;
  const uint32_t k = k1 | k2 | k3 | k4;
  if (k)
    return node->children[ __builtin_ctz(k) ];
  return NULL;
}

// swar implementation based on:
// http://0x80.pl/notesen/2023-03-06-swar-find-any.html
static really_inline uint32_t has_zero_byte(uint32_t v)
{
  const uint32_t v1 = v - 0x01010101u;
  const uint32_t v2 = v1 & ~(v);
  const uint32_t v3 = v2 & 0x80808080u;
  return v3;
	//return (v - 0x01010101u) & ~(v) & 0x80808080u;
}

static really_inline uint32_t index_of_first_set_byte(uint32_t v)
{
  //return ((((v - 1) & 0x10101010) * 0x10101010) >> 24) - 1;
  const uint32_t v1 = __builtin_ctz(v);
  const uint32_t v2 = v1 / 8;
  return v2;
}

// based on http://0x80.pl/notesen/2023-03-06-swar-find-any.html
static never_inline node_t *find_node4_swar(const node4_t *node, uint8_t key)
{
  assert(node->base.type == NODE4);
  static_assert(sizeof(uint32_t) == sizeof(node->keys));

  uint32_t keys;
  memcpy(&keys, node->keys, sizeof(keys));
  uint32_t mask = 0x01010101u * key; // broadcast
  uint32_t matches = has_zero_byte(keys ^ mask);
  if (matches)
    return node->children[index_of_first_set_byte(matches)];
  return NULL;
}

// simd implementation based on:
// https://stackoverflow.com/questions/74803190/fastest-way-to-find-16bit-match-in-a-4-element-short-array
static never_inline node_t *find_node4_simd(const node4_t *node, uint8_t key)
{
  assert(node->base.type == NODE4);
  static_assert(sizeof(uint32_t) == sizeof(node->keys));

  __m128i keys = _mm_loadu_si32((const __m128i *)node->keys);
  uint16_t mask = _mm_movemask_epi8(_mm_cmpeq_epi8(keys, _mm_set1_epi8(key)));
  if (mask)
    return node->children[ __builtin_ctz(mask) ];
  return NULL;
}

int main(int argc, char *argv[])
{
  char w1[] = "alpha";
  char w2[] = "bravo";
  char w3[] = "charlie";
  char w4[] = "delta";
  node_t *n1 = (node_t *)w1;
  node_t *n2 = (node_t *)w2;
  node_t *n3 = (node_t *)w3;
  node_t *n4 = (node_t *)w4;
  const node4_t node = { { NODE4 }, { 'a', 'b', 'c', 'd' }, { n1, n2, n3, n4 } };

  if (argc != 2 || strlen(argv[1]) != 1) {
    printf("please choose: a) %s, b) %s, c) %s, d) %s, *) no choice\n", w1, w2, w3, w4);
    return 1;
  }

  printf("choice: %c\n", argv[1][0]);
  node_t *p = find_node4_simd(&node, (uint8_t)argv[1][0]);
  if (!p)
    printf("no match!\n");
  else
    printf("you chose: %s\n", (const char *)p);

  return 0;
}
