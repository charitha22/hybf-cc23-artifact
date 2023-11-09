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
struct wmi_cmd_hdr {int /*<<< orphan*/  cmd_id; } ;
struct sk_buff {int /*<<< orphan*/  len; scalar_t__ data; } ;
struct ath10k {int dummy; } ;
typedef  enum wmi_10_4_event_id { ____Placeholder_wmi_10_4_event_id } wmi_10_4_event_id ;

/* Variables and functions */
 int /*<<< orphan*/  ATH10K_DBG_WMI ; 
 int MS (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
#define  WMI_10_4_CHAN_INFO_EVENTID 154 
#define  WMI_10_4_DEBUG_FATAL_CONDITION_EVENTID 153 
#define  WMI_10_4_DEBUG_MESG_EVENTID 152 
#define  WMI_10_4_DEBUG_PRINT_EVENTID 151 
#define  WMI_10_4_DFS_STATUS_CHECK_EVENTID 150 
#define  WMI_10_4_ECHO_EVENTID 149 
#define  WMI_10_4_HOST_SWBA_EVENTID 148 
#define  WMI_10_4_MGMT_RX_EVENTID 147 
#define  WMI_10_4_PDEV_BSS_CHAN_INFO_EVENTID 146 
#define  WMI_10_4_PDEV_TEMPERATURE_EVENTID 145 
#define  WMI_10_4_PDEV_TPC_CONFIG_EVENTID 144 
#define  WMI_10_4_PDEV_TPC_TABLE_EVENTID 143 
#define  WMI_10_4_PEER_RATECODE_LIST_EVENTID 142 
#define  WMI_10_4_PEER_STA_KICKOUT_EVENTID 141 
#define  WMI_10_4_PEER_STA_PS_STATECHG_EVENTID 140 
#define  WMI_10_4_PHYERR_EVENTID 139 
#define  WMI_10_4_READY_EVENTID 138 
#define  WMI_10_4_ROAM_EVENTID 137 
#define  WMI_10_4_SCAN_EVENTID 136 
#define  WMI_10_4_SERVICE_READY_EVENTID 135 
#define  WMI_10_4_TBTTOFFSET_UPDATE_EVENTID 134 
#define  WMI_10_4_TDLS_PEER_EVENTID 133 
#define  WMI_10_4_UPDATE_STATS_EVENTID 132 
#define  WMI_10_4_VDEV_START_RESP_EVENTID 131 
#define  WMI_10_4_VDEV_STOPPED_EVENTID 130 
#define  WMI_10_4_WDS_PEER_EVENTID 129 
#define  WMI_10_4_WOW_WAKEUP_HOST_EVENTID 128 
 int /*<<< orphan*/  WMI_CMD_HDR_CMD_ID ; 
 int /*<<< orphan*/  __le32_to_cpu (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ath10k_dbg (struct ath10k*,int /*<<< orphan*/ ,char*,int) ; 
 int ath10k_tm_event_wmi (struct ath10k*,int,struct sk_buff*) ; 
 int /*<<< orphan*/  ath10k_warn (struct ath10k*,char*,int) ; 
 int /*<<< orphan*/  ath10k_wmi_event_chan_info (struct ath10k*,struct sk_buff*) ; 
 int /*<<< orphan*/  ath10k_wmi_event_debug_mesg (struct ath10k*,struct sk_buff*) ; 
 int /*<<< orphan*/  ath10k_wmi_event_debug_print (struct ath10k*,struct sk_buff*) ; 
 int /*<<< orphan*/  ath10k_wmi_event_dfs_status_check (struct ath10k*,struct sk_buff*) ; 
 int /*<<< orphan*/  ath10k_wmi_event_echo (struct ath10k*,struct sk_buff*) ; 
 int /*<<< orphan*/  ath10k_wmi_event_host_swba (struct ath10k*,struct sk_buff*) ; 
 int /*<<< orphan*/  ath10k_wmi_event_mgmt_rx (struct ath10k*,struct sk_buff*) ; 
 int /*<<< orphan*/  ath10k_wmi_event_pdev_bss_chan_info (struct ath10k*,struct sk_buff*) ; 
 int /*<<< orphan*/  ath10k_wmi_event_pdev_tpc_config (struct ath10k*,struct sk_buff*) ; 
 int /*<<< orphan*/  ath10k_wmi_event_peer_sta_kickout (struct ath10k*,struct sk_buff*) ; 
 int /*<<< orphan*/  ath10k_wmi_event_peer_sta_ps_state_chg (struct ath10k*,struct sk_buff*) ; 
 int /*<<< orphan*/  ath10k_wmi_event_phyerr (struct ath10k*,struct sk_buff*) ; 
 int /*<<< orphan*/  ath10k_wmi_event_ready (struct ath10k*,struct sk_buff*) ; 
 int /*<<< orphan*/  ath10k_wmi_event_roam (struct ath10k*,struct sk_buff*) ; 
 int /*<<< orphan*/  ath10k_wmi_event_scan (struct ath10k*,struct sk_buff*) ; 
 int /*<<< orphan*/  ath10k_wmi_event_service_ready (struct ath10k*,struct sk_buff*) ; 
 int /*<<< orphan*/  ath10k_wmi_event_tbttoffset_update (struct ath10k*,struct sk_buff*) ; 
 int /*<<< orphan*/  ath10k_wmi_event_temperature (struct ath10k*,struct sk_buff*) ; 
 int /*<<< orphan*/  ath10k_wmi_event_tpc_final_table (struct ath10k*,struct sk_buff*) ; 
 int /*<<< orphan*/  ath10k_wmi_event_update_stats (struct ath10k*,struct sk_buff*) ; 
 int /*<<< orphan*/  ath10k_wmi_event_vdev_start_resp (struct ath10k*,struct sk_buff*) ; 
 int /*<<< orphan*/  ath10k_wmi_event_vdev_stopped (struct ath10k*,struct sk_buff*) ; 
 int /*<<< orphan*/  ath10k_wmi_handle_tdls_peer_event (struct ath10k*,struct sk_buff*) ; 
 int /*<<< orphan*/  ath10k_wmi_queue_set_coverage_class_work (struct ath10k*) ; 
 int /*<<< orphan*/  dev_kfree_skb (struct sk_buff*) ; 
 int /*<<< orphan*/  skb_pull (struct sk_buff*,int) ; 
 int /*<<< orphan*/  trace_ath10k_wmi_event (struct ath10k*,int,scalar_t__,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void ath10k_wmi_10_4_op_rx(struct ath10k *ar, struct sk_buff *skb)
{
	struct wmi_cmd_hdr *cmd_hdr;
	enum wmi_10_4_event_id id;
	bool consumed;

	cmd_hdr = (struct wmi_cmd_hdr *)skb->data;
	id = MS(__le32_to_cpu(cmd_hdr->cmd_id), WMI_CMD_HDR_CMD_ID);

	if (!skb_pull(skb, sizeof(struct wmi_cmd_hdr)))
		goto out;

	trace_ath10k_wmi_event(ar, id, skb->data, skb->len);

	consumed = ath10k_tm_event_wmi(ar, id, skb);

	/* Ready event must be handled normally also in UTF mode so that we
	 * know the UTF firmware has booted, others we are just bypass WMI
	 * events to testmode.
	 */
	if (consumed && id != WMI_10_4_READY_EVENTID) {
		ath10k_dbg(ar, ATH10K_DBG_WMI,
			   "wmi testmode consumed 0x%x\n", id);
		goto out;
	}

	switch (id) {
	case WMI_10_4_MGMT_RX_EVENTID:
		ath10k_wmi_event_mgmt_rx(ar, skb);
		/* mgmt_rx() owns the skb now! */
		return;
	case WMI_10_4_ECHO_EVENTID:
		ath10k_wmi_event_echo(ar, skb);
		break;
	case WMI_10_4_DEBUG_MESG_EVENTID:
		ath10k_wmi_event_debug_mesg(ar, skb);
		ath10k_wmi_queue_set_coverage_class_work(ar);
		break;
	case WMI_10_4_SERVICE_READY_EVENTID:
		ath10k_wmi_event_service_ready(ar, skb);
		return;
	case WMI_10_4_SCAN_EVENTID:
		ath10k_wmi_event_scan(ar, skb);
		ath10k_wmi_queue_set_coverage_class_work(ar);
		break;
	case WMI_10_4_CHAN_INFO_EVENTID:
		ath10k_wmi_event_chan_info(ar, skb);
		break;
	case WMI_10_4_PHYERR_EVENTID:
		ath10k_wmi_event_phyerr(ar, skb);
		break;
	case WMI_10_4_READY_EVENTID:
		ath10k_wmi_event_ready(ar, skb);
		ath10k_wmi_queue_set_coverage_class_work(ar);
		break;
	case WMI_10_4_PEER_STA_KICKOUT_EVENTID:
		ath10k_wmi_event_peer_sta_kickout(ar, skb);
		break;
	case WMI_10_4_ROAM_EVENTID:
		ath10k_wmi_event_roam(ar, skb);
		ath10k_wmi_queue_set_coverage_class_work(ar);
		break;
	case WMI_10_4_HOST_SWBA_EVENTID:
		ath10k_wmi_event_host_swba(ar, skb);
		break;
	case WMI_10_4_TBTTOFFSET_UPDATE_EVENTID:
		ath10k_wmi_event_tbttoffset_update(ar, skb);
		break;
	case WMI_10_4_DEBUG_PRINT_EVENTID:
		ath10k_wmi_event_debug_print(ar, skb);
		ath10k_wmi_queue_set_coverage_class_work(ar);
		break;
	case WMI_10_4_VDEV_START_RESP_EVENTID:
		ath10k_wmi_event_vdev_start_resp(ar, skb);
		ath10k_wmi_queue_set_coverage_class_work(ar);
		break;
	case WMI_10_4_VDEV_STOPPED_EVENTID:
		ath10k_wmi_event_vdev_stopped(ar, skb);
		ath10k_wmi_queue_set_coverage_class_work(ar);
		break;
	case WMI_10_4_WOW_WAKEUP_HOST_EVENTID:
	case WMI_10_4_PEER_RATECODE_LIST_EVENTID:
	case WMI_10_4_WDS_PEER_EVENTID:
	case WMI_10_4_DEBUG_FATAL_CONDITION_EVENTID:
		ath10k_dbg(ar, ATH10K_DBG_WMI,
			   "received event id %d not implemented\n", id);
		break;
	case WMI_10_4_UPDATE_STATS_EVENTID:
		ath10k_wmi_event_update_stats(ar, skb);
		break;
	case WMI_10_4_PDEV_TEMPERATURE_EVENTID:
		ath10k_wmi_event_temperature(ar, skb);
		break;
	case WMI_10_4_PDEV_BSS_CHAN_INFO_EVENTID:
		ath10k_wmi_event_pdev_bss_chan_info(ar, skb);
		break;
	case WMI_10_4_PDEV_TPC_CONFIG_EVENTID:
		ath10k_wmi_event_pdev_tpc_config(ar, skb);
		break;
	case WMI_10_4_TDLS_PEER_EVENTID:
		ath10k_wmi_handle_tdls_peer_event(ar, skb);
		break;
	case WMI_10_4_PDEV_TPC_TABLE_EVENTID:
		ath10k_wmi_event_tpc_final_table(ar, skb);
		break;
	case WMI_10_4_DFS_STATUS_CHECK_EVENTID:
		ath10k_wmi_event_dfs_status_check(ar, skb);
		break;
	case WMI_10_4_PEER_STA_PS_STATECHG_EVENTID:
		ath10k_wmi_event_peer_sta_ps_state_chg(ar, skb);
		break;
	default:
		ath10k_warn(ar, "Unknown eventid: %d\n", id);
		break;
	}

out:
	dev_kfree_skb(skb);
}