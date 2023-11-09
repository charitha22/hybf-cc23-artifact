#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ u8 ;
typedef  scalar_t__ u32 ;
struct r8192_priv {scalar_t__ undecorated_smoothed_pwdb; int framesync; scalar_t__ reset_count; scalar_t__ framesyncMonitor; TYPE_2__* ieee80211; } ;
struct net_device {int dummy; } ;
struct TYPE_4__ {scalar_t__ state; scalar_t__ bfsync_enable; int fsync_state; TYPE_1__* pHTInfo; int /*<<< orphan*/  fsync_seconddiff_ratethreshold; int /*<<< orphan*/  fsync_firstdiff_ratethreshold; int /*<<< orphan*/  fsync_rate_bitmap; int /*<<< orphan*/  fsync_multiple_timeinterval; int /*<<< orphan*/  fsync_time_interval; int /*<<< orphan*/  fsync_rssi_threshold; } ;
struct TYPE_3__ {int IOTAction; } ;

/* Variables and functions */
 int /*<<< orphan*/  COMP_HALDM ; 
#define  Default_Fsync 130 
 int HT_IOT_ACT_CDD_FSYNC ; 
#define  HW_Fsync 129 
 scalar_t__ IEEE80211_LINKED ; 
 scalar_t__ REG_C38_TH ; 
 int /*<<< orphan*/  RT_TRACE (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ RegC38_Default ; 
 scalar_t__ RegC38_Fsync_AP_BCM ; 
 scalar_t__ RegC38_NonFsync_Other_AP ; 
#define  SW_Fsync 128 
 int /*<<< orphan*/  dm_EndHWFsync (struct net_device*) ; 
 int /*<<< orphan*/  dm_EndSWFsync (struct net_device*) ; 
 int /*<<< orphan*/  dm_StartHWFsync (struct net_device*) ; 
 int /*<<< orphan*/  dm_StartSWFsync (struct net_device*) ; 
 struct r8192_priv* ieee80211_priv (struct net_device*) ; 
 int /*<<< orphan*/  rOFDM0_RxDetector3 ; 
 int /*<<< orphan*/  write_nic_byte (struct net_device*,int /*<<< orphan*/ ,int) ; 

void dm_check_fsync(struct net_device *dev)
{
#define	RegC38_Default				0
#define	RegC38_NonFsync_Other_AP		1
#define	RegC38_Fsync_AP_BCM			2
	struct r8192_priv *priv = ieee80211_priv(dev);
	/*u32			framesyncC34;*/
	static u8		reg_c38_State = RegC38_Default;
	static u32	reset_cnt;

	RT_TRACE(COMP_HALDM, "RSSI %d TimeInterval %d MultipleTimeInterval %d\n", priv->ieee80211->fsync_rssi_threshold, priv->ieee80211->fsync_time_interval, priv->ieee80211->fsync_multiple_timeinterval);
	RT_TRACE(COMP_HALDM, "RateBitmap 0x%x FirstDiffRateThreshold %d SecondDiffRateThreshold %d\n", priv->ieee80211->fsync_rate_bitmap, priv->ieee80211->fsync_firstdiff_ratethreshold, priv->ieee80211->fsync_seconddiff_ratethreshold);

	if (priv->ieee80211->state == IEEE80211_LINKED &&
		(priv->ieee80211->pHTInfo->IOTAction & HT_IOT_ACT_CDD_FSYNC)) {
		if (priv->ieee80211->bfsync_enable == 0) {
			switch (priv->ieee80211->fsync_state) {
			case Default_Fsync:
				dm_StartHWFsync(dev);
				priv->ieee80211->fsync_state = HW_Fsync;
				break;
			case SW_Fsync:
				dm_EndSWFsync(dev);
				dm_StartHWFsync(dev);
				priv->ieee80211->fsync_state = HW_Fsync;
				break;
			case HW_Fsync:
			default:
				break;
			}
		} else {
			switch (priv->ieee80211->fsync_state) {
			case Default_Fsync:
				dm_StartSWFsync(dev);
				priv->ieee80211->fsync_state = SW_Fsync;
				break;
			case HW_Fsync:
				dm_EndHWFsync(dev);
				dm_StartSWFsync(dev);
				priv->ieee80211->fsync_state = SW_Fsync;
				break;
			case SW_Fsync:
			default:
				break;
			}
		}
		if (priv->framesyncMonitor) {
			if (reg_c38_State != RegC38_Fsync_AP_BCM) {
				/* For broadcom AP we write different default value */
				write_nic_byte(dev, rOFDM0_RxDetector3, 0x95);

				reg_c38_State = RegC38_Fsync_AP_BCM;
			}
		}
	} else {
		switch (priv->ieee80211->fsync_state) {
		case HW_Fsync:
			dm_EndHWFsync(dev);
			priv->ieee80211->fsync_state = Default_Fsync;
			break;
		case SW_Fsync:
			dm_EndSWFsync(dev);
			priv->ieee80211->fsync_state = Default_Fsync;
			break;
		case Default_Fsync:
		default:
			break;
		}

		if (priv->framesyncMonitor) {
			if (priv->ieee80211->state == IEEE80211_LINKED) {
				if (priv->undecorated_smoothed_pwdb <= REG_C38_TH) {
					if (reg_c38_State != RegC38_NonFsync_Other_AP) {
						write_nic_byte(dev, rOFDM0_RxDetector3, 0x90);

						reg_c38_State = RegC38_NonFsync_Other_AP;
					}
				} else if (priv->undecorated_smoothed_pwdb >= (REG_C38_TH + 5)) {
					if (reg_c38_State) {
						write_nic_byte(dev, rOFDM0_RxDetector3, priv->framesync);
						reg_c38_State = RegC38_Default;
						/*DbgPrint("Fsync is idle, rssi>=40, write 0xc38 = 0x%x\n", pHalData->framesync);*/
					}
				}
			} else {
				if (reg_c38_State) {
					write_nic_byte(dev, rOFDM0_RxDetector3, priv->framesync);
					reg_c38_State = RegC38_Default;
					/*DbgPrint("Fsync is idle, not connected, write 0xc38 = 0x%x\n", pHalData->framesync);*/
				}
			}
		}
	}
	if (priv->framesyncMonitor) {
		if (priv->reset_count != reset_cnt) { /* After silent reset, the reg_c38_State will be returned to default value */
			write_nic_byte(dev, rOFDM0_RxDetector3, priv->framesync);
			reg_c38_State = RegC38_Default;
			reset_cnt = priv->reset_count;
			/*DbgPrint("reg_c38_State = 0 for silent reset.\n");*/
		}
	} else {
		if (reg_c38_State) {
			write_nic_byte(dev, rOFDM0_RxDetector3, priv->framesync);
			reg_c38_State = RegC38_Default;
			/*DbgPrint("framesync no monitor, write 0xc38 = 0x%x\n", pHalData->framesync);*/
		}
	}
}