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
typedef  int /*<<< orphan*/  u16 ;
struct TYPE_2__ {scalar_t__ (* write_reg ) (struct e1000_hw*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ;scalar_t__ (* read_reg ) (struct e1000_hw*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ;} ;
struct e1000_phy_info {scalar_t__ smart_speed; scalar_t__ autoneg_advertised; TYPE_1__ ops; } ;
struct e1000_hw {struct e1000_phy_info phy; } ;
typedef  scalar_t__ s32 ;

/* Variables and functions */
 scalar_t__ E1000_ALL_10_SPEED ; 
 scalar_t__ E1000_ALL_NOT_GIG ; 
 scalar_t__ E1000_ALL_SPEED_DUPLEX ; 
 int /*<<< orphan*/  IGP01E1000_PHY_PORT_CONFIG ; 
 int /*<<< orphan*/  IGP01E1000_PSCFR_SMART_SPEED ; 
 int /*<<< orphan*/  IGP02E1000_PHY_POWER_MGMT ; 
 int /*<<< orphan*/  IGP02E1000_PM_D3_LPLU ; 
 scalar_t__ e1000_smart_speed_off ; 
 scalar_t__ e1000_smart_speed_on ; 
 scalar_t__ stub1 (struct e1000_hw*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 scalar_t__ stub2 (struct e1000_hw*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ stub3 (struct e1000_hw*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 scalar_t__ stub4 (struct e1000_hw*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ stub5 (struct e1000_hw*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 scalar_t__ stub6 (struct e1000_hw*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ stub7 (struct e1000_hw*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ stub8 (struct e1000_hw*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 scalar_t__ stub9 (struct e1000_hw*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

s32 igb_set_d3_lplu_state(struct e1000_hw *hw, bool active)
{
	struct e1000_phy_info *phy = &hw->phy;
	s32 ret_val = 0;
	u16 data;

	if (!(hw->phy.ops.read_reg))
		goto out;

	ret_val = phy->ops.read_reg(hw, IGP02E1000_PHY_POWER_MGMT, &data);
	if (ret_val)
		goto out;

	if (!active) {
		data &= ~IGP02E1000_PM_D3_LPLU;
		ret_val = phy->ops.write_reg(hw, IGP02E1000_PHY_POWER_MGMT,
					     data);
		if (ret_val)
			goto out;
		/* LPLU and SmartSpeed are mutually exclusive.  LPLU is used
		 * during Dx states where the power conservation is most
		 * important.  During driver activity we should enable
		 * SmartSpeed, so performance is maintained.
		 */
		if (phy->smart_speed == e1000_smart_speed_on) {
			ret_val = phy->ops.read_reg(hw,
						    IGP01E1000_PHY_PORT_CONFIG,
						    &data);
			if (ret_val)
				goto out;

			data |= IGP01E1000_PSCFR_SMART_SPEED;
			ret_val = phy->ops.write_reg(hw,
						     IGP01E1000_PHY_PORT_CONFIG,
						     data);
			if (ret_val)
				goto out;
		} else if (phy->smart_speed == e1000_smart_speed_off) {
			ret_val = phy->ops.read_reg(hw,
						     IGP01E1000_PHY_PORT_CONFIG,
						     &data);
			if (ret_val)
				goto out;

			data &= ~IGP01E1000_PSCFR_SMART_SPEED;
			ret_val = phy->ops.write_reg(hw,
						     IGP01E1000_PHY_PORT_CONFIG,
						     data);
			if (ret_val)
				goto out;
		}
	} else if ((phy->autoneg_advertised == E1000_ALL_SPEED_DUPLEX) ||
		   (phy->autoneg_advertised == E1000_ALL_NOT_GIG) ||
		   (phy->autoneg_advertised == E1000_ALL_10_SPEED)) {
		data |= IGP02E1000_PM_D3_LPLU;
		ret_val = phy->ops.write_reg(hw, IGP02E1000_PHY_POWER_MGMT,
					      data);
		if (ret_val)
			goto out;

		/* When LPLU is enabled, we should disable SmartSpeed */
		ret_val = phy->ops.read_reg(hw, IGP01E1000_PHY_PORT_CONFIG,
					    &data);
		if (ret_val)
			goto out;

		data &= ~IGP01E1000_PSCFR_SMART_SPEED;
		ret_val = phy->ops.write_reg(hw, IGP01E1000_PHY_PORT_CONFIG,
					     data);
	}

out:
	return ret_val;
}