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
struct snd_kcontrol {int dummy; } ;
struct snd_ice1712 {int dummy; } ;
struct TYPE_3__ {int* value; } ;
struct TYPE_4__ {TYPE_1__ integer; } ;
struct snd_ctl_elem_value {TYPE_2__ value; int /*<<< orphan*/  id; } ;

/* Variables and functions */
 int STAC946X_MIC_L_VOLUME ; 
 int snd_ctl_get_ioffidx (struct snd_kcontrol*,int /*<<< orphan*/ *) ; 
 struct snd_ice1712* snd_kcontrol_chip (struct snd_kcontrol*) ; 
 int stac9460_2_get (struct snd_ice1712*,int) ; 
 int /*<<< orphan*/  stac9460_2_put (struct snd_ice1712*,int,int) ; 
 int stac9460_get (struct snd_ice1712*,int) ; 
 int /*<<< orphan*/  stac9460_put (struct snd_ice1712*,int,int) ; 

__attribute__((used)) static int stac9460_adc_vol_put(struct snd_kcontrol *kcontrol,
				struct snd_ctl_elem_value *ucontrol)
{
	struct snd_ice1712 *ice = snd_kcontrol_chip(kcontrol);
	int i, reg, id;
	unsigned char ovol, nvol;
	int change;

	id = snd_ctl_get_ioffidx(kcontrol, &ucontrol->id);
	if (id == 0) {
		for (i = 0; i < 2; ++i) {
			reg = STAC946X_MIC_L_VOLUME + i;
			nvol = ucontrol->value.integer.value[i] & 0x0f;
			ovol = 0x0f - stac9460_get(ice, reg);
			change = ((ovol & 0x0f) != nvol);
			if (change)
				stac9460_put(ice, reg, (0x0f - nvol) |
							(ovol & ~0x0f));
		}
	} else {
		for (i = 0; i < 2; ++i) {
			reg = STAC946X_MIC_L_VOLUME + i;
			nvol = ucontrol->value.integer.value[i] & 0x0f;
			ovol = 0x0f - stac9460_2_get(ice, reg);
			change = ((ovol & 0x0f) != nvol);
			if (change)
				stac9460_2_put(ice, reg, (0x0f - nvol) |
							(ovol & ~0x0f));
		}
	}
	return change;
}