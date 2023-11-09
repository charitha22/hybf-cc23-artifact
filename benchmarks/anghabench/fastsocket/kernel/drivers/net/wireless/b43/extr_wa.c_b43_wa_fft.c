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
struct TYPE_2__ {scalar_t__ type; } ;
struct b43_wldev {TYPE_1__ phy; } ;

/* Variables and functions */
 int /*<<< orphan*/  B43_OFDMTAB_DACRFPABB ; 
 scalar_t__ B43_PHYTYPE_A ; 
 int B43_TAB_FINEFREQA_SIZE ; 
 int B43_TAB_FINEFREQG_SIZE ; 
 int /*<<< orphan*/  b43_ofdmtab_write16 (struct b43_wldev*,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * b43_tab_finefreqa ; 
 int /*<<< orphan*/ * b43_tab_finefreqg ; 

__attribute__((used)) static void b43_wa_fft(struct b43_wldev *dev) /* Fine frequency table */
{
	int i;

	if (dev->phy.type == B43_PHYTYPE_A)
		for (i = 0; i < B43_TAB_FINEFREQA_SIZE; i++)
			b43_ofdmtab_write16(dev, B43_OFDMTAB_DACRFPABB, i, b43_tab_finefreqa[i]);
	else
		for (i = 0; i < B43_TAB_FINEFREQG_SIZE; i++)
			b43_ofdmtab_write16(dev, B43_OFDMTAB_DACRFPABB, i, b43_tab_finefreqg[i]);
}