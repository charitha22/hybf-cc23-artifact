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
typedef  int u32 ;
struct r8192_priv {size_t CCK_index; } ;
struct net_device {int dummy; } ;

/* Variables and functions */
 int** CCKSwingTable_Ch14 ; 
 int** CCKSwingTable_Ch1_Ch13 ; 
 int /*<<< orphan*/  COMP_POWER_TRACKING ; 
 int /*<<< orphan*/  RT_TRACE (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  bMaskDWord ; 
 int /*<<< orphan*/  bMaskHWord ; 
 int /*<<< orphan*/  bMaskLWord ; 
 int /*<<< orphan*/  rCCK0_DebugPort ; 
 int /*<<< orphan*/  rCCK0_TxFilter1 ; 
 int /*<<< orphan*/  rCCK0_TxFilter2 ; 
 int /*<<< orphan*/  rtl92e_set_bb_reg (struct net_device*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 struct r8192_priv* rtllib_priv (struct net_device*) ; 

__attribute__((used)) static void _rtl92e_dm_cck_tx_power_adjust_thermal_meter(struct net_device *dev,
							 bool bInCH14)
{
	u32 TempVal;
	struct r8192_priv *priv = rtllib_priv(dev);

	TempVal = 0;
	if (!bInCH14) {
		TempVal = CCKSwingTable_Ch1_Ch13[priv->CCK_index][0] +
			  (CCKSwingTable_Ch1_Ch13[priv->CCK_index][1] << 8);
		rtl92e_set_bb_reg(dev, rCCK0_TxFilter1, bMaskHWord, TempVal);
		RT_TRACE(COMP_POWER_TRACKING,
			 "CCK not chnl 14, reg 0x%x = 0x%x\n", rCCK0_TxFilter1,
			 TempVal);
		TempVal = CCKSwingTable_Ch1_Ch13[priv->CCK_index][2] +
			  (CCKSwingTable_Ch1_Ch13[priv->CCK_index][3] << 8) +
			  (CCKSwingTable_Ch1_Ch13[priv->CCK_index][4] << 16)+
			  (CCKSwingTable_Ch1_Ch13[priv->CCK_index][5] << 24);
		rtl92e_set_bb_reg(dev, rCCK0_TxFilter2, bMaskDWord, TempVal);
		RT_TRACE(COMP_POWER_TRACKING,
			 "CCK not chnl 14, reg 0x%x = 0x%x\n", rCCK0_TxFilter2,
			 TempVal);
		TempVal = CCKSwingTable_Ch1_Ch13[priv->CCK_index][6] +
			  (CCKSwingTable_Ch1_Ch13[priv->CCK_index][7] << 8);

		rtl92e_set_bb_reg(dev, rCCK0_DebugPort, bMaskLWord, TempVal);
		RT_TRACE(COMP_POWER_TRACKING,
			 "CCK not chnl 14, reg 0x%x = 0x%x\n", rCCK0_DebugPort,
			 TempVal);
	} else {
		TempVal = CCKSwingTable_Ch14[priv->CCK_index][0] +
			  (CCKSwingTable_Ch14[priv->CCK_index][1] << 8);

		rtl92e_set_bb_reg(dev, rCCK0_TxFilter1, bMaskHWord, TempVal);
		RT_TRACE(COMP_POWER_TRACKING, "CCK chnl 14, reg 0x%x = 0x%x\n",
			rCCK0_TxFilter1, TempVal);
		TempVal = CCKSwingTable_Ch14[priv->CCK_index][2] +
			  (CCKSwingTable_Ch14[priv->CCK_index][3] << 8) +
			  (CCKSwingTable_Ch14[priv->CCK_index][4] << 16)+
			  (CCKSwingTable_Ch14[priv->CCK_index][5] << 24);
		rtl92e_set_bb_reg(dev, rCCK0_TxFilter2, bMaskDWord, TempVal);
		RT_TRACE(COMP_POWER_TRACKING, "CCK chnl 14, reg 0x%x = 0x%x\n",
			rCCK0_TxFilter2, TempVal);
		TempVal = CCKSwingTable_Ch14[priv->CCK_index][6] +
			  (CCKSwingTable_Ch14[priv->CCK_index][7]<<8);

		rtl92e_set_bb_reg(dev, rCCK0_DebugPort, bMaskLWord, TempVal);
		RT_TRACE(COMP_POWER_TRACKING, "CCK chnl 14, reg 0x%x = 0x%x\n",
			rCCK0_DebugPort, TempVal);
	}
}