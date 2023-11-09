#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
typedef  int u_int ;
typedef  int u_char ;
struct sk_buff {int* data; int len; } ;
struct layer2 {int /*<<< orphan*/  l2m; int /*<<< orphan*/  flag; } ;

/* Variables and functions */
 int DEBUG_L2 ; 
 int /*<<< orphan*/  FLG_MOD128 ; 
 int /*<<< orphan*/  FLG_ORIG ; 
 int* debug ; 
 int l2addrsize (struct layer2*) ; 
 int /*<<< orphan*/  l2m_debug (int /*<<< orphan*/ *,char*,int,int,int,...) ; 
 scalar_t__ test_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int
FRMR_error(struct layer2 *l2, struct sk_buff *skb)
{
	u_int	headers = l2addrsize(l2) + 1;
	u_char	*datap = skb->data + headers;
	int	rsp = *skb->data & 0x2;

	if (test_bit(FLG_ORIG, &l2->flag))
		rsp = !rsp;
	if (!rsp)
		return 'L';
	if (test_bit(FLG_MOD128, &l2->flag)) {
		if (skb->len < headers + 5)
			return 'N';
		else if (*debug & DEBUG_L2)
			l2m_debug(&l2->l2m,
				  "FRMR information %2x %2x %2x %2x %2x",
				  datap[0], datap[1], datap[2], datap[3], datap[4]);
	} else {
		if (skb->len < headers + 3)
			return 'N';
		else if (*debug & DEBUG_L2)
			l2m_debug(&l2->l2m,
				  "FRMR information %2x %2x %2x",
				  datap[0], datap[1], datap[2]);
	}
	return 0;
}