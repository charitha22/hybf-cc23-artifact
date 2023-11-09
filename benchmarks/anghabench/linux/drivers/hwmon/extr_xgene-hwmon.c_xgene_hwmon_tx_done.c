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
typedef  int /*<<< orphan*/  u16 ;
struct mbox_client {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void xgene_hwmon_tx_done(struct mbox_client *cl, void *msg, int ret)
{
	if (ret) {
		dev_dbg(cl->dev, "TX did not complete: CMD sent:%x, ret:%d\n",
			*(u16 *)msg, ret);
	} else {
		dev_dbg(cl->dev, "TX completed. CMD sent:%x, ret:%d\n",
			*(u16 *)msg, ret);
	}
}