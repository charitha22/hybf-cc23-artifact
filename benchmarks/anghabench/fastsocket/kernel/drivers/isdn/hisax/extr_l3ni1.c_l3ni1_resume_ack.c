#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u_char ;
struct sk_buff {int dummy; } ;
struct TYPE_5__ {int moderate; int cause; int bchannel; } ;
struct l3_process {int debug; int state; TYPE_3__* st; int /*<<< orphan*/  timer; TYPE_1__ para; } ;
struct TYPE_6__ {int /*<<< orphan*/  (* l3l4 ) (TYPE_3__*,int,struct l3_process*) ;} ;
struct TYPE_7__ {TYPE_2__ l3; } ;

/* Variables and functions */
 int CC_RESUME ; 
 int CONFIRM ; 
 int ERR_IE_COMPREHENSION ; 
 int /*<<< orphan*/  L3DelTimer (int /*<<< orphan*/ *) ; 
 int L3_DEB_WARN ; 
 int check_infoelements (struct l3_process*,struct sk_buff*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ie_RESUME_ACKNOWLEDGE ; 
 int /*<<< orphan*/  l3_debug (TYPE_3__*,char*,int) ; 
 int l3ni1_get_channel_id (struct l3_process*,struct sk_buff*) ; 
 int /*<<< orphan*/  l3ni1_status_send (struct l3_process*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  l3ni1_std_ie_err (struct l3_process*,int) ; 
 int /*<<< orphan*/  newl3state (struct l3_process*,int) ; 
 int /*<<< orphan*/  stub1 (TYPE_3__*,int,struct l3_process*) ; 

__attribute__((used)) static void
l3ni1_resume_ack(struct l3_process *pc, u_char pr, void *arg)
{
	struct sk_buff *skb = arg;
	int id, ret;

	if ((id = l3ni1_get_channel_id(pc, skb)) > 0) {
		if ((0 == id) || ((3 == id) && (0x10 == pc->para.moderate))) {
			if (pc->debug & L3_DEB_WARN)
				l3_debug(pc->st, "resume ack with wrong chid %x", id);
			pc->para.cause = 100;
			l3ni1_status_send(pc, pr, NULL);
			return;
		}
		pc->para.bchannel = id;
	} else if (1 == pc->state) {
		if (pc->debug & L3_DEB_WARN)
			l3_debug(pc->st, "resume ack without chid (ret %d)", id);
		pc->para.cause = 96;
		l3ni1_status_send(pc, pr, NULL);
		return;
	}
	ret = check_infoelements(pc, skb, ie_RESUME_ACKNOWLEDGE);
	if (ERR_IE_COMPREHENSION == ret) {
		l3ni1_std_ie_err(pc, ret);
		return;
	}
	L3DelTimer(&pc->timer);
	pc->st->l3.l3l4(pc->st, CC_RESUME | CONFIRM, pc);
	newl3state(pc, 10);
	if (ret) /* STATUS for none mandatory IE errors after actions are taken */
		l3ni1_std_ie_err(pc, ret);
}