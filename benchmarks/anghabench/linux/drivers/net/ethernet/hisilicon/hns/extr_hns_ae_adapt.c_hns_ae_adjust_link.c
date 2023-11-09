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
struct hns_mac_cb {TYPE_1__* dsaf_dev; } ;
struct hnae_handle {int dummy; } ;
struct TYPE_2__ {int dsaf_ver; } ;

/* Variables and functions */
#define  AE_VERSION_1 129 
#define  AE_VERSION_2 128 
 int /*<<< orphan*/  MAC_COMM_MODE_RX ; 
 int /*<<< orphan*/  hns_ae_wait_flow_down (struct hnae_handle*) ; 
 struct hns_mac_cb* hns_get_mac_cb (struct hnae_handle*) ; 
 int /*<<< orphan*/  hns_mac_adjust_link (struct hns_mac_cb*,int,int) ; 
 int /*<<< orphan*/  hns_mac_disable (struct hns_mac_cb*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  hns_mac_enable (struct hns_mac_cb*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void hns_ae_adjust_link(struct hnae_handle *handle, int speed,
			       int duplex)
{
	struct hns_mac_cb *mac_cb = hns_get_mac_cb(handle);

	switch (mac_cb->dsaf_dev->dsaf_ver) {
	case AE_VERSION_1:
		hns_mac_adjust_link(mac_cb, speed, duplex);
		break;

	case AE_VERSION_2:
		/* chip need to clear all pkt inside */
		hns_mac_disable(mac_cb, MAC_COMM_MODE_RX);
		if (hns_ae_wait_flow_down(handle)) {
			hns_mac_enable(mac_cb, MAC_COMM_MODE_RX);
			break;
		}

		hns_mac_adjust_link(mac_cb, speed, duplex);
		hns_mac_enable(mac_cb, MAC_COMM_MODE_RX);
		break;

	default:
		break;
	}

	return;
}