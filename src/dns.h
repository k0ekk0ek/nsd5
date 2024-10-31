/*
 * dns.h
 *
 * Copyright (c) 2024, NLnet Labs. All rights reserved.
 *
 * SPDX-License-Identifier: BSD-3-Clause
 *
 */
#ifndef NSD_DNS_H
#define NSD_DNS_H

/**
 * @defgroup class_nodes Class nodes
 *
 * Supported CLASSes.
 *
 * See @{iana{DNS CLASSes,dns-parameters,dns-parameters-2} for a list of
 * classes registered by IANA.
 *
 * @{
 */
/** Internet @rfc{1035} */
#define ZONE_CLASS_IN (1u)
/** CSNET @rfc{1035} @obsolete */
#define ZONE_CLASS_CS (2u)
/** CHAOS @rfc{1035} */
#define ZONE_CLASS_CH (3u)
/** Hesiod @rfc{1035} */
#define ZONE_CLASS_HS (4u)
/** Any (QCLASS) @rfc{1035} */
#define ZONE_CLASS_ANY (255u)
/** @} */

/**
 * @defgroup type_codes Type codes
 *
 * Supported resource record (RR) TYPEs.
 *
 * See @iana{RR TYPEs,dns-parameters,dns-parameters-4} for a list of
 * types registered by IANA.
 *
 * @{
 */
/** Host address @rfc{1035} */
#define ZONE_TYPE_A (1u)
/** Authoritative name server @rfc{1035} */
#define ZONE_TYPE_NS (2u)
/** Mail destination @rfc{1035} @obsolete */
#define ZONE_TYPE_MD (3u)
/** Mail forwarder @rfc{1035} @obsolete */
#define ZONE_TYPE_MF (4u)
/** Canonical name for an alias @rfc{1035} */
#define ZONE_TYPE_CNAME (5u)
/** Marks the start of authority @rfc{1035} */
#define ZONE_TYPE_SOA (6u)
/** Mailbox domain name @rfc{1035} @experimental */
#define ZONE_TYPE_MB (7u)
/** Mail group member @rfc{1035} @experimental */
#define ZONE_TYPE_MG (8u)
/** Mail rename domain name @rfc{1035} @experimental */
#define ZONE_TYPE_MR (9u)
/** Anything @rfc{883} @obsolete */
#define ZONE_TYPE_NULL (10u)
/** Well known service description @rfc{1035} */
#define ZONE_TYPE_WKS (11u)
/** Domain name pointer @rfc{1035} */
#define ZONE_TYPE_PTR (12u)
/** Host information @rfc{1035} */
#define ZONE_TYPE_HINFO (13u)
/** Mailbox or mail list information @rfc{1035} */
#define ZONE_TYPE_MINFO (14u)
/** Mail exchange @rfc{1035} */
#define ZONE_TYPE_MX (15u)
/** Text strings @rfc{1035} */
#define ZONE_TYPE_TXT (16u)
/** Responsible person @rfc{1035} */
#define ZONE_TYPE_RP (17u)
/** AFS Data Base location @rfc{1183} @rfc{5864} */
#define ZONE_TYPE_AFSDB (18u)
/** X.25 PSDN address @rfc{1183} */
#define ZONE_TYPE_X25 (19u)
/** ISDN address @rfc{1183} */
#define ZONE_TYPE_ISDN (20u)
/** Route Through @rfc{1183} */
#define ZONE_TYPE_RT (21u)
/** NSAP address, NSAP style A record @rfc{1706} */
#define ZONE_TYPE_NSAP (22u)
/** Domain name pointer, NSAP style @rfc{1348} @rfc{1637} */
#define ZONE_TYPE_NSAP_PTR (23u)
/** Signature @rfc{2535} */
#define ZONE_TYPE_SIG (24u)
/** Public key @rfc{2535} @rfc{2930} */
#define ZONE_TYPE_KEY (25u)
/** X.400 mail mapping information @rfc{2163} */
#define ZONE_TYPE_PX (26u)
/** Geographical Position @rfc{1712} */
#define ZONE_TYPE_GPOS (27u)
/** IPv6 Address @rfc{3596} */
#define ZONE_TYPE_AAAA (28u)
/** Location Information @rfc{1876} */
#define ZONE_TYPE_LOC (29u)
/** Next domain @rfc{3755} @rfc{2535} @obsolete */
#define ZONE_TYPE_NXT (30u)
/** Server Selection @rfc{2782} */
#define ZONE_TYPE_SRV (33u)
/** Naming Authority Pointer @rfc{2915} @rfc{2168} @rfc{3403} */
#define ZONE_TYPE_NAPTR (35u)
/** Key Exchanger @rfc{2230} */
#define ZONE_TYPE_KX (36u)
/** CERT @rfc{4398}*/
#define ZONE_TYPE_CERT (37u)
/** IPv6 Address @rfc{3226} @rfc{2874} @rfc{6563} @obsolete */
#define ZONE_TYPE_A6 (38u)
/** DNAME @rfc{6672} */
#define ZONE_TYPE_DNAME (39u)
/** Address Prefix List @rfc{3123} */
#define ZONE_TYPE_APL (42u)
/** Delegation Signer @rfc{4034} @rfc{3658} */
#define ZONE_TYPE_DS (43u)
/** SSH Key Fingerprint @rfc{4255} */
#define ZONE_TYPE_SSHFP (44u)
/** IPsec public key @rfc{4025} */
#define ZONE_TYPE_IPSECKEY (45u)
/** Resource Record Signature @rfc{4034} @rfc{3755} */
#define ZONE_TYPE_RRSIG (46u)
/** Next Secure @rfc{4034} @rfc{3755} */
#define ZONE_TYPE_NSEC (47u)
/** DNS Public Key @rfc{4034} @rfc{3755} */
#define ZONE_TYPE_DNSKEY (48u)
/** DHCID @rfc{4701} */
#define ZONE_TYPE_DHCID (49u)
/** NSEC3 @rfc{5155} */
#define ZONE_TYPE_NSEC3 (50u)
/** NSEC3PARAM @rfc{5155} */
#define ZONE_TYPE_NSEC3PARAM (51u)
/** TLSA @rfc{6698} */
#define ZONE_TYPE_TLSA (52u)
/** S/MIME cert association @rfc{8162} */
#define ZONE_TYPE_SMIMEA (53u)
/** Host Identity Protocol @rfc{8005} */
#define ZONE_TYPE_HIP (55u)
/** Child DS @rfc{7344} */
#define ZONE_TYPE_CDS (59u)
/** DNSKEY(s) the Child wants reflected in DS @rfc{7344} */
#define ZONE_TYPE_CDNSKEY (60u)
/** OpenPGP Key @rfc{7929} */
#define ZONE_TYPE_OPENPGPKEY (61u)
/** Child-To-Parent Synchronization @rfc{7477} */
#define ZONE_TYPE_CSYNC (62u)
/** Zone message digest @rfc{8976} */
#define ZONE_TYPE_ZONEMD (63u)
/** Service binding @rfc{9460} */
#define ZONE_TYPE_SVCB (64u)
/** Service binding @rfc{9460} */
#define ZONE_TYPE_HTTPS (65u)
/** Sender Policy Framework @rfc{7208} */
#define ZONE_TYPE_SPF (99u)
/** Node Identifier @rfc{6742} */
#define ZONE_TYPE_NID (104u)
/** 32-bit Locator for ILNPv4-capable nodes @rfc{6742} */
#define ZONE_TYPE_L32 (105u)
/** 64-bit Locator for ILNPv6-capable nodes @rfc{6742} */
#define ZONE_TYPE_L64 (106u)
/** Name of an ILNP subnetwork @rfc{6742} */
#define ZONE_TYPE_LP (107u)
/** EUI-48 address @rfc{7043} */
#define ZONE_TYPE_EUI48 (108u)
/** EUI-64 address @rfc{7043} */
#define ZONE_TYPE_EUI64 (109u)
/** Uniform Resource Identifier @rfc{7553} */
#define ZONE_TYPE_URI (256u)
/** Certification Authority Restriction @rfc{6844} */
#define ZONE_TYPE_CAA (257u)
/** DNS Authoritative Source (DNS-AS) */
#define ZONE_TYPE_AVC (258u)
/** DNSSEC Lookaside Validation @rfc{4431} */
#define ZONE_TYPE_DLV (32769u)
/** @} */

/**
 * @defgroup svc_params Service Parameter Keys
 *
 * Supported service parameters.
 *
 * See @iana{Service Parameter Keys (SvcParamKeys),dns-svcb,dns-svcparamkeys}
 * for a list of service parameter keys registered by IANA.
 *
 * @{
 */
/** Parameters clients must not ignore @rfc{9460} */
#define ZONE_SVC_PARAM_KEY_MANDATORY (0u)
/** Application Layer Protocol Negotiation (ALPN) protocol identifiers @rfc{9460} */
#define ZONE_SVC_PARAM_KEY_ALPN (1u)
/** No support for default protocol (alpn must be specified) @rfc{9460} */
#define ZONE_SVC_PARAM_KEY_NO_DEFAULT_ALPN (2u)
/** TCP or UDP port for alternative endpoint @rfc{9460} */
#define ZONE_SVC_PARAM_KEY_PORT (3u)
/** IPv4 address hints @rfc{9460} */
#define ZONE_SVC_PARAM_KEY_IPV4HINT (4u)
/** Encrypted ClientHello (ECH) configuration @draft{ietf, tls-svcb-ech} */
#define ZONE_SVC_PARAM_KEY_ECH (5u)
/** IPv6 address hints @rfc{9460} */
#define ZONE_SVC_PARAM_KEY_IPV6HINT (6u)
/** URI template in relative form @rfc{9461} */
#define ZONE_SVC_PARAM_KEY_DOHPATH (7u)
/** Target is an Oblivious HTTP service @draft{ohai,svcb-config} */
#define ZONE_SVC_PARAM_KEY_OHTTP (8u)
/** Reserved ("invalid key") @rfc{9460} */
#define ZONE_SVC_PARAM_KEY_INVALID_KEY (65535u)
/** @} */

#endif // NSD_DNS_H
