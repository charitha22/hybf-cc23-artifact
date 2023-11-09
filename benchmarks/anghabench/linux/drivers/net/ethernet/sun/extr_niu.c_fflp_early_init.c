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
struct niu_parent {int flags; scalar_t__ plat_type; } ;
struct niu {int /*<<< orphan*/  dev; struct niu_parent* parent; } ;

/* Variables and functions */
 int /*<<< orphan*/  H1POLY ; 
 int /*<<< orphan*/  H2POLY ; 
 int /*<<< orphan*/  KERN_DEBUG ; 
 int PARENT_FLGS_CLS_HWINIT ; 
 scalar_t__ PLAT_TYPE_NIU ; 
 int fflp_disable_all_partitions (struct niu*) ; 
 int /*<<< orphan*/  fflp_errors_enable (struct niu*,int /*<<< orphan*/ ) ; 
 int fflp_hash_clear (struct niu*) ; 
 int /*<<< orphan*/  fflp_llcsnap_enable (struct niu*,int) ; 
 int /*<<< orphan*/  fflp_reset (struct niu*) ; 
 int /*<<< orphan*/  fflp_set_timings (struct niu*) ; 
 int /*<<< orphan*/  netif_printk (struct niu*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,int) ; 
 int /*<<< orphan*/  niu_lock_parent (struct niu*,unsigned long) ; 
 int /*<<< orphan*/  niu_unlock_parent (struct niu*,unsigned long) ; 
 int /*<<< orphan*/  nw64 (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  probe ; 
 int tcam_early_init (struct niu*) ; 
 int tcam_flush_all (struct niu*) ; 
 int /*<<< orphan*/  vlan_tbl_clear (struct niu*) ; 

__attribute__((used)) static int fflp_early_init(struct niu *np)
{
	struct niu_parent *parent;
	unsigned long flags;
	int err;

	niu_lock_parent(np, flags);

	parent = np->parent;
	err = 0;
	if (!(parent->flags & PARENT_FLGS_CLS_HWINIT)) {
		if (np->parent->plat_type != PLAT_TYPE_NIU) {
			fflp_reset(np);
			fflp_set_timings(np);
			err = fflp_disable_all_partitions(np);
			if (err) {
				netif_printk(np, probe, KERN_DEBUG, np->dev,
					     "fflp_disable_all_partitions failed, err=%d\n",
					     err);
				goto out;
			}
		}

		err = tcam_early_init(np);
		if (err) {
			netif_printk(np, probe, KERN_DEBUG, np->dev,
				     "tcam_early_init failed, err=%d\n", err);
			goto out;
		}
		fflp_llcsnap_enable(np, 1);
		fflp_errors_enable(np, 0);
		nw64(H1POLY, 0);
		nw64(H2POLY, 0);

		err = tcam_flush_all(np);
		if (err) {
			netif_printk(np, probe, KERN_DEBUG, np->dev,
				     "tcam_flush_all failed, err=%d\n", err);
			goto out;
		}
		if (np->parent->plat_type != PLAT_TYPE_NIU) {
			err = fflp_hash_clear(np);
			if (err) {
				netif_printk(np, probe, KERN_DEBUG, np->dev,
					     "fflp_hash_clear failed, err=%d\n",
					     err);
				goto out;
			}
		}

		vlan_tbl_clear(np);

		parent->flags |= PARENT_FLGS_CLS_HWINIT;
	}
out:
	niu_unlock_parent(np, flags);
	return err;
}