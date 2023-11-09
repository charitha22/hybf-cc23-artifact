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
typedef  scalar_t__ u8 ;
typedef  int u32 ;
struct iwl_cfg {int dummy; } ;

/* Variables and functions */
 scalar_t__ FIRST_2GHZ_HT_MINUS ; 
 int IEEE80211_CHAN_INDOOR_ONLY ; 
 int IEEE80211_CHAN_IR_CONCURRENT ; 
 int IEEE80211_CHAN_NO_160MHZ ; 
 int IEEE80211_CHAN_NO_80MHZ ; 
 int IEEE80211_CHAN_NO_HT40 ; 
 int IEEE80211_CHAN_NO_HT40MINUS ; 
 int IEEE80211_CHAN_NO_HT40PLUS ; 
 int IEEE80211_CHAN_NO_IR ; 
 int IEEE80211_CHAN_RADAR ; 
 scalar_t__ LAST_2GHZ_HT_PLUS ; 
 int NUM_2GHZ_CHANNELS ; 
 int NVM_CHANNEL_160MHZ ; 
 int NVM_CHANNEL_40MHZ ; 
 int NVM_CHANNEL_80MHZ ; 
 int NVM_CHANNEL_ACTIVE ; 
 int NVM_CHANNEL_GO_CONCURRENT ; 
 int NVM_CHANNEL_IBSS ; 
 int NVM_CHANNEL_INDOOR_ONLY ; 
 int NVM_CHANNEL_RADAR ; 

__attribute__((used)) static u32 iwl_get_channel_flags(u8 ch_num, int ch_idx, bool is_5ghz,
				 u32 nvm_flags, const struct iwl_cfg *cfg)
{
	u32 flags = IEEE80211_CHAN_NO_HT40;

	if (!is_5ghz && (nvm_flags & NVM_CHANNEL_40MHZ)) {
		if (ch_num <= LAST_2GHZ_HT_PLUS)
			flags &= ~IEEE80211_CHAN_NO_HT40PLUS;
		if (ch_num >= FIRST_2GHZ_HT_MINUS)
			flags &= ~IEEE80211_CHAN_NO_HT40MINUS;
	} else if (nvm_flags & NVM_CHANNEL_40MHZ) {
		if ((ch_idx - NUM_2GHZ_CHANNELS) % 2 == 0)
			flags &= ~IEEE80211_CHAN_NO_HT40PLUS;
		else
			flags &= ~IEEE80211_CHAN_NO_HT40MINUS;
	}
	if (!(nvm_flags & NVM_CHANNEL_80MHZ))
		flags |= IEEE80211_CHAN_NO_80MHZ;
	if (!(nvm_flags & NVM_CHANNEL_160MHZ))
		flags |= IEEE80211_CHAN_NO_160MHZ;

	if (!(nvm_flags & NVM_CHANNEL_IBSS))
		flags |= IEEE80211_CHAN_NO_IR;

	if (!(nvm_flags & NVM_CHANNEL_ACTIVE))
		flags |= IEEE80211_CHAN_NO_IR;

	if (nvm_flags & NVM_CHANNEL_RADAR)
		flags |= IEEE80211_CHAN_RADAR;

	if (nvm_flags & NVM_CHANNEL_INDOOR_ONLY)
		flags |= IEEE80211_CHAN_INDOOR_ONLY;

	/* Set the GO concurrent flag only in case that NO_IR is set.
	 * Otherwise it is meaningless
	 */
	if ((nvm_flags & NVM_CHANNEL_GO_CONCURRENT) &&
	    (flags & IEEE80211_CHAN_NO_IR))
		flags |= IEEE80211_CHAN_IR_CONCURRENT;

	return flags;
}