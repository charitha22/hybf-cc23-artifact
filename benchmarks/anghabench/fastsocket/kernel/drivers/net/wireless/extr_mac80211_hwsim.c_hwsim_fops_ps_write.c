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
typedef  scalar_t__ u64 ;
struct mac80211_hwsim_data {int ps; int ps_poll_pending; int /*<<< orphan*/  hw; } ;
typedef  enum ps_mode { ____Placeholder_ps_mode } ps_mode ;

/* Variables and functions */
 int EINVAL ; 
 int /*<<< orphan*/  IEEE80211_IFACE_ITER_NORMAL ; 
 scalar_t__ PS_AUTO_POLL ; 
 scalar_t__ PS_DISABLED ; 
 scalar_t__ PS_ENABLED ; 
 scalar_t__ PS_MANUAL_POLL ; 
 int /*<<< orphan*/  hwsim_send_nullfunc_no_ps ; 
 int /*<<< orphan*/  hwsim_send_nullfunc_ps ; 
 int /*<<< orphan*/  hwsim_send_ps_poll ; 
 int /*<<< orphan*/  ieee80211_iterate_active_interfaces (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct mac80211_hwsim_data*) ; 

__attribute__((used)) static int hwsim_fops_ps_write(void *dat, u64 val)
{
	struct mac80211_hwsim_data *data = dat;
	enum ps_mode old_ps;

	if (val != PS_DISABLED && val != PS_ENABLED && val != PS_AUTO_POLL &&
	    val != PS_MANUAL_POLL)
		return -EINVAL;

	old_ps = data->ps;
	data->ps = val;

	if (val == PS_MANUAL_POLL) {
		ieee80211_iterate_active_interfaces(data->hw,
						    IEEE80211_IFACE_ITER_NORMAL,
						    hwsim_send_ps_poll, data);
		data->ps_poll_pending = true;
	} else if (old_ps == PS_DISABLED && val != PS_DISABLED) {
		ieee80211_iterate_active_interfaces(data->hw,
						    IEEE80211_IFACE_ITER_NORMAL,
						    hwsim_send_nullfunc_ps,
						    data);
	} else if (old_ps != PS_DISABLED && val == PS_DISABLED) {
		ieee80211_iterate_active_interfaces(data->hw,
						    IEEE80211_IFACE_ITER_NORMAL,
						    hwsim_send_nullfunc_no_ps,
						    data);
	}

	return 0;
}