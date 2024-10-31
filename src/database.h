/*
 * database.h -- database for storing authoritative zone data
 *
 * Copyright (c) 2024, NLnet Labs. All rights reserved.
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */
#ifndef NSD_DATABASE_H
#define NSD_DATABASE_H

typedef struct nsd_rdata nsd_rdata_t;
struct nsd_rdata {
  uint_fast16_t rdlength;
  uint8_t rdata[]; // c99 flexible array
};

// RFC 2181 section 5.2:
//   TTLs of all RRs in an RRset must be the same.
typedef struct nsd_rrset nsd_rrset_t;
struct nsd_rrset {
  uint16_t type;
  uint16_t class;
  uint32_t ttl;
  struct {
    size_t count;
    nsd_rdata_t **rdata;
  } rrs;
};

typedef struct nsd_name nsd_name_t;
struct nsd_name {
  uint8_t length;
  uint8_t octets[]; // c99 flexible array
};

typedef struct nsd_name_key nsd_name_key_t;
struct nsd_name_key {
  uint8_t length;
  uint8_t octets[NSD_MAXDOMAINLEN + 64]; // padded to ensure safe simd usage
};

// name+key entries are "persitent" and stored in a separate tree, sorted by
// canonical name, so that lifecycles are not linked to domain entries.
// unreferenced entries (usage reaches zero) are marked for sweep.
//   1. allows for in-tree RDATA compression.
//   2. avoids key generation for resolving in-zone CNAME chains, etc.
typedef struct nsd_name_key_map nsd_name_key_map_t;
struct nsd_name_key_map {
  nsd_atomic_u64_t usage; // reference counter
  nsd_name_key_t key;
  nsd_name_t name;
};

struct uint8_t nsd_sha1_digest[20]; // 160 bits, or 20 bytes


typedef struct nsd_domain nsd_domain_t;
struct nsd_domain {
  struct {
    // FIXME: include a bitmap to quickly identify if any of the most common
    //        types are included (128-bits or so)? popcnt can be used to
    //        determine the position (may improve performance)
    uint16_t count;
    nsd_rrset_t *rrset; // FIXME: rather than solving everything via the path,
                        //        we could use fat nodes for the rrsets pointer
                        //        to achieve multiple revisions without impacting
                        //        lookup
  } rrsets;
#if NSD_NSEC3
  nsd_sha1_digest_t hash;
  // nsec3 tree references the hash member.
#endif
  nsd_name_t name; // c99 flexible array
  // name trees (owners and key+name map) reference the name member.
  // offsetof can be used to determine the node address
};


// Zone contains a region for everything within that zone to avoid any
// synchronization. The zone can be discarded with a "single" operation.
typedef struct nsd_zone nsd_zone_t;
struct nsd_zone {
  nsd_region_t region; // region for everything within the zone
  // - tree of owners
  //   owner table contains only owners (or in-zone domains) to make
  //   operations more convenient. likely improves performance too as it will
  //   allow for skipping the zone part in the key.
  // - tree of nsec3 hashes
  //   nsec3 hashes can be used directly as no hierarchy exists.
  // - tree of key+name map
  //   table will contain domains that are unrelated to the zone.
  nsd_name_t apex; // lower cased and uncompressed
};

typedef struct nsd_database nsd_database_t;
struct nsd_database {
  nsd_region_t region; // region for zone tree
  // - tree of zones
};

#endif // NSD_DATABASE_H
