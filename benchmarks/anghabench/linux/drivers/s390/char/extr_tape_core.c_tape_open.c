#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct tape_device {scalar_t__ tape_state; int /*<<< orphan*/  cdev; TYPE_1__* discipline; } ;
struct TYPE_2__ {int /*<<< orphan*/  owner; } ;

/* Variables and functions */
 int /*<<< orphan*/  DBF_EVENT (int,char*) ; 
 int EBUSY ; 
 int ENODEV ; 
 scalar_t__ TS_BLKUSE ; 
 scalar_t__ TS_IN_USE ; 
 scalar_t__ TS_NOT_OPER ; 
 int /*<<< orphan*/  get_ccwdev_lock (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spin_lock_irq (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spin_unlock_irq (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  tape_state_set (struct tape_device*,scalar_t__) ; 
 int /*<<< orphan*/  try_module_get (int /*<<< orphan*/ ) ; 

int
tape_open(struct tape_device *device)
{
	int rc;

	spin_lock_irq(get_ccwdev_lock(device->cdev));
	if (device->tape_state == TS_NOT_OPER) {
		DBF_EVENT(6, "TAPE:nodev\n");
		rc = -ENODEV;
	} else if (device->tape_state == TS_IN_USE) {
		DBF_EVENT(6, "TAPE:dbusy\n");
		rc = -EBUSY;
	} else if (device->tape_state == TS_BLKUSE) {
		DBF_EVENT(6, "TAPE:dbusy\n");
		rc = -EBUSY;
	} else if (device->discipline != NULL &&
		   !try_module_get(device->discipline->owner)) {
		DBF_EVENT(6, "TAPE:nodisc\n");
		rc = -ENODEV;
	} else {
		tape_state_set(device, TS_IN_USE);
		rc = 0;
	}
	spin_unlock_irq(get_ccwdev_lock(device->cdev));
	return rc;
}