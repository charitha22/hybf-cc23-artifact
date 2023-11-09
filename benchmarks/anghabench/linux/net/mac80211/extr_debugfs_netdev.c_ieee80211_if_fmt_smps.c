#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_4__ ;
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {size_t req_smps; } ;
struct TYPE_5__ {size_t req_smps; } ;
struct TYPE_8__ {TYPE_3__ ap; TYPE_1__ mgd; } ;
struct TYPE_6__ {scalar_t__ type; } ;
struct ieee80211_sub_if_data {size_t smps_mode; TYPE_4__ u; TYPE_2__ vif; } ;
typedef  int /*<<< orphan*/  ssize_t ;

/* Variables and functions */
 int /*<<< orphan*/  EINVAL ; 
 scalar_t__ NL80211_IFTYPE_AP ; 
 scalar_t__ NL80211_IFTYPE_STATION ; 
 char** smps_modes ; 
 int /*<<< orphan*/  snprintf (char*,int,char*,char*,char*) ; 

__attribute__((used)) static ssize_t ieee80211_if_fmt_smps(const struct ieee80211_sub_if_data *sdata,
				     char *buf, int buflen)
{
	if (sdata->vif.type == NL80211_IFTYPE_STATION)
		return snprintf(buf, buflen, "request: %s\nused: %s\n",
				smps_modes[sdata->u.mgd.req_smps],
				smps_modes[sdata->smps_mode]);
	if (sdata->vif.type == NL80211_IFTYPE_AP)
		return snprintf(buf, buflen, "request: %s\nused: %s\n",
				smps_modes[sdata->u.ap.req_smps],
				smps_modes[sdata->smps_mode]);
	return -EINVAL;
}