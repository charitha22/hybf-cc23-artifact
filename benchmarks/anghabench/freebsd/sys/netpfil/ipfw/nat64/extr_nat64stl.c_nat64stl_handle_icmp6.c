#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint32_t ;
struct pfloghdr {int dummy; } ;
struct nat64_counters {int dummy; } ;
struct TYPE_6__ {int flags; struct nat64_counters stats; } ;
struct TYPE_5__ {int /*<<< orphan*/  kidx; } ;
struct nat64stl_cfg {TYPE_3__ base; TYPE_2__ no; int /*<<< orphan*/  map64; } ;
struct TYPE_4__ {scalar_t__ len; } ;
struct mbuf {scalar_t__ m_len; TYPE_1__ m_pkthdr; } ;
struct ip_fw_chain {int dummy; } ;
struct ip6_hdr {int /*<<< orphan*/  ip6_dst; } ;
struct in6_addr {int dummy; } ;
struct icmp6_hdr {int icmp6_type; } ;

/* Variables and functions */
 int /*<<< orphan*/  AF_INET6 ; 
#define  ICMP6_DST_UNREACH 131 
#define  ICMP6_PACKET_TOO_BIG 130 
#define  ICMP6_PARAM_PROB 129 
#define  ICMP6_TIME_EXCEED_TRANSIT 128 
 scalar_t__ ICMP_MINLEN ; 
 int IPPROTO_ICMPV6 ; 
 int NAT64MFREE ; 
 int NAT64RETURN ; 
 int /*<<< orphan*/  NAT64STAT_INC (struct nat64_counters*,int /*<<< orphan*/ ) ; 
 int NAT64_LOG ; 
 int /*<<< orphan*/  TARG_VAL (struct ip_fw_chain*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dropped ; 
 int /*<<< orphan*/  htonl (int /*<<< orphan*/ ) ; 
 scalar_t__ ipfw_lookup_table (struct ip_fw_chain*,int /*<<< orphan*/ ,int,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  m_freem (struct mbuf*) ; 
 struct mbuf* m_pullup (struct mbuf*,scalar_t__) ; 
 void* mtodo (struct mbuf*,int) ; 
 int nat64_getlasthdr (struct mbuf*,int*) ; 
 int nat64_handle_icmp6 (struct mbuf*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,TYPE_3__*,struct pfloghdr*) ; 
 int /*<<< orphan*/  nat64stl_log (struct pfloghdr*,struct mbuf*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  nh4 ; 
 int /*<<< orphan*/  nomem ; 

__attribute__((used)) static int
nat64stl_handle_icmp6(struct ip_fw_chain *chain, struct nat64stl_cfg *cfg,
    struct mbuf *m)
{
	struct pfloghdr loghdr, *logdata;
	struct nat64_counters *stats;
	struct ip6_hdr *ip6i;
	struct icmp6_hdr *icmp6;
	uint32_t tablearg;
	int hlen, proto;

	hlen = 0;
	stats = &cfg->base.stats;
	proto = nat64_getlasthdr(m, &hlen);
	if (proto != IPPROTO_ICMPV6) {
		NAT64STAT_INC(stats, dropped);
		return (NAT64MFREE);
	}
	icmp6 = mtodo(m, hlen);
	switch (icmp6->icmp6_type) {
	case ICMP6_DST_UNREACH:
	case ICMP6_PACKET_TOO_BIG:
	case ICMP6_TIME_EXCEED_TRANSIT:
	case ICMP6_PARAM_PROB:
		break;
	default:
		NAT64STAT_INC(stats, dropped);
		return (NAT64MFREE);
	}
	hlen += sizeof(struct icmp6_hdr);
	if (m->m_pkthdr.len < hlen + sizeof(struct ip6_hdr) + ICMP_MINLEN) {
		NAT64STAT_INC(stats, dropped);
		return (NAT64MFREE);
	}
	if (m->m_len < hlen + sizeof(struct ip6_hdr) + ICMP_MINLEN)
		m = m_pullup(m, hlen + sizeof(struct ip6_hdr) + ICMP_MINLEN);
	if (m == NULL) {
		NAT64STAT_INC(stats, nomem);
		return (NAT64RETURN);
	}
	/*
	 * Use destination address from inner IPv6 header to determine
	 * IPv4 mapped address.
	 */
	ip6i = mtodo(m, hlen);
	if (ipfw_lookup_table(chain, cfg->map64,
	    sizeof(struct in6_addr), &ip6i->ip6_dst, &tablearg) == 0) {
		m_freem(m);
		return (NAT64RETURN);
	}
	if (cfg->base.flags & NAT64_LOG) {
		logdata = &loghdr;
		nat64stl_log(logdata, m, AF_INET6, cfg->no.kidx);
	} else
		logdata = NULL;
	return (nat64_handle_icmp6(m, 0,
	    htonl(TARG_VAL(chain, tablearg, nh4)), 0, &cfg->base, logdata));
}