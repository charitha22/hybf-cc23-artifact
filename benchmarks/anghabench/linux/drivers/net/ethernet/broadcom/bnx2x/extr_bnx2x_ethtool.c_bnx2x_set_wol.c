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
struct net_device {int dummy; } ;
struct ethtool_wolinfo {int wolopts; } ;
struct bnx2x {int flags; int wol; } ;

/* Variables and functions */
 int /*<<< orphan*/  BNX2X_MSG_ETHTOOL ; 
 int /*<<< orphan*/  CURR_CFG_MET_OS ; 
 int /*<<< orphan*/  DP (int /*<<< orphan*/ ,char*) ; 
 int EINVAL ; 
 int NO_WOL_FLAG ; 
 scalar_t__ SHMEM2_HAS (struct bnx2x*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SHMEM2_WR (struct bnx2x*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int WAKE_MAGIC ; 
 int /*<<< orphan*/  curr_cfg ; 
 struct bnx2x* netdev_priv (struct net_device*) ; 

__attribute__((used)) static int bnx2x_set_wol(struct net_device *dev, struct ethtool_wolinfo *wol)
{
	struct bnx2x *bp = netdev_priv(dev);

	if (wol->wolopts & ~WAKE_MAGIC) {
		DP(BNX2X_MSG_ETHTOOL, "WOL not supported\n");
		return -EINVAL;
	}

	if (wol->wolopts & WAKE_MAGIC) {
		if (bp->flags & NO_WOL_FLAG) {
			DP(BNX2X_MSG_ETHTOOL, "WOL not supported\n");
			return -EINVAL;
		}
		bp->wol = 1;
	} else
		bp->wol = 0;

	if (SHMEM2_HAS(bp, curr_cfg))
		SHMEM2_WR(bp, curr_cfg, CURR_CFG_MET_OS);

	return 0;
}