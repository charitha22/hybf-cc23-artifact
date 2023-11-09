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
typedef  scalar_t__ u32 ;
struct ixgbe_hw {int dummy; } ;
typedef  int /*<<< orphan*/  s32 ;

/* Variables and functions */
 int /*<<< orphan*/  IXGBE_ERR_EEPROM ; 
 scalar_t__ IXGBE_READ_REG (struct ixgbe_hw*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  IXGBE_SWSM (struct ixgbe_hw*) ; 
 scalar_t__ IXGBE_SWSM_SMBI ; 
 scalar_t__ IXGBE_SWSM_SWESMBI ; 
 int /*<<< orphan*/  IXGBE_WRITE_REG (struct ixgbe_hw*,int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  hw_dbg (struct ixgbe_hw*,char*) ; 
 int /*<<< orphan*/  ixgbe_release_eeprom_semaphore (struct ixgbe_hw*) ; 
 int /*<<< orphan*/  usleep_range (int,int) ; 

__attribute__((used)) static s32 ixgbe_get_eeprom_semaphore(struct ixgbe_hw *hw)
{
	u32 timeout = 2000;
	u32 i;
	u32 swsm;

	/* Get SMBI software semaphore between device drivers first */
	for (i = 0; i < timeout; i++) {
		/*
		 * If the SMBI bit is 0 when we read it, then the bit will be
		 * set and we have the semaphore
		 */
		swsm = IXGBE_READ_REG(hw, IXGBE_SWSM(hw));
		if (!(swsm & IXGBE_SWSM_SMBI))
			break;
		usleep_range(50, 100);
	}

	if (i == timeout) {
		hw_dbg(hw, "Driver can't access the Eeprom - SMBI Semaphore not granted.\n");
		/* this release is particularly important because our attempts
		 * above to get the semaphore may have succeeded, and if there
		 * was a timeout, we should unconditionally clear the semaphore
		 * bits to free the driver to make progress
		 */
		ixgbe_release_eeprom_semaphore(hw);

		usleep_range(50, 100);
		/* one last try
		 * If the SMBI bit is 0 when we read it, then the bit will be
		 * set and we have the semaphore
		 */
		swsm = IXGBE_READ_REG(hw, IXGBE_SWSM(hw));
		if (swsm & IXGBE_SWSM_SMBI) {
			hw_dbg(hw, "Software semaphore SMBI between device drivers not granted.\n");
			return IXGBE_ERR_EEPROM;
		}
	}

	/* Now get the semaphore between SW/FW through the SWESMBI bit */
	for (i = 0; i < timeout; i++) {
		swsm = IXGBE_READ_REG(hw, IXGBE_SWSM(hw));

		/* Set the SW EEPROM semaphore bit to request access */
		swsm |= IXGBE_SWSM_SWESMBI;
		IXGBE_WRITE_REG(hw, IXGBE_SWSM(hw), swsm);

		/* If we set the bit successfully then we got the
		 * semaphore.
		 */
		swsm = IXGBE_READ_REG(hw, IXGBE_SWSM(hw));
		if (swsm & IXGBE_SWSM_SWESMBI)
			break;

		usleep_range(50, 100);
	}

	/* Release semaphores and return error if SW EEPROM semaphore
	 * was not granted because we don't have access to the EEPROM
	 */
	if (i >= timeout) {
		hw_dbg(hw, "SWESMBI Software EEPROM semaphore not granted.\n");
		ixgbe_release_eeprom_semaphore(hw);
		return IXGBE_ERR_EEPROM;
	}

	return 0;
}