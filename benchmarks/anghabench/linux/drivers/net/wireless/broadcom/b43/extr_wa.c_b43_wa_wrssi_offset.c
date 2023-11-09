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
struct TYPE_2__ {int rev; } ;
struct b43_wldev {TYPE_1__ phy; } ;

/* Variables and functions */
 int /*<<< orphan*/  B43_OFDMTAB_WRSSI ; 
 int /*<<< orphan*/  B43_OFDMTAB_WRSSI_R1 ; 
 int /*<<< orphan*/  b43_ofdmtab_write16 (struct b43_wldev*,int /*<<< orphan*/ ,int,int) ; 

__attribute__((used)) static void b43_wa_wrssi_offset(struct b43_wldev *dev)
{
	int i;

	if (dev->phy.rev == 1) {
		for (i = 0; i < 16; i++) {
			b43_ofdmtab_write16(dev, B43_OFDMTAB_WRSSI_R1,
						i, 0x0020);
		}
	} else {
		for (i = 0; i < 32; i++) {
			b43_ofdmtab_write16(dev, B43_OFDMTAB_WRSSI,
						i, 0x0820);
		}
	}
}