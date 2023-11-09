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
typedef  int u16 ;
struct snd_soc_dai {struct snd_soc_component* component; } ;
struct snd_soc_component {int dummy; } ;
struct TYPE_2__ {int pre_div; int n; int k; } ;

/* Variables and functions */
 int /*<<< orphan*/  WM8510_CLOCK ; 
 int /*<<< orphan*/  WM8510_PLLK1 ; 
 int /*<<< orphan*/  WM8510_PLLK2 ; 
 int /*<<< orphan*/  WM8510_PLLK3 ; 
 int /*<<< orphan*/  WM8510_PLLN ; 
 int /*<<< orphan*/  WM8510_POWER1 ; 
 TYPE_1__ pll_div ; 
 int /*<<< orphan*/  pll_factors (unsigned int,unsigned int) ; 
 int snd_soc_component_read32 (struct snd_soc_component*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  snd_soc_component_write (struct snd_soc_component*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int wm8510_set_dai_pll(struct snd_soc_dai *codec_dai, int pll_id,
		int source, unsigned int freq_in, unsigned int freq_out)
{
	struct snd_soc_component *component = codec_dai->component;
	u16 reg;

	if (freq_in == 0 || freq_out == 0) {
		/* Clock CODEC directly from MCLK */
		reg = snd_soc_component_read32(component, WM8510_CLOCK);
		snd_soc_component_write(component, WM8510_CLOCK, reg & 0x0ff);

		/* Turn off PLL */
		reg = snd_soc_component_read32(component, WM8510_POWER1);
		snd_soc_component_write(component, WM8510_POWER1, reg & 0x1df);
		return 0;
	}

	pll_factors(freq_out*4, freq_in);

	snd_soc_component_write(component, WM8510_PLLN, (pll_div.pre_div << 4) | pll_div.n);
	snd_soc_component_write(component, WM8510_PLLK1, pll_div.k >> 18);
	snd_soc_component_write(component, WM8510_PLLK2, (pll_div.k >> 9) & 0x1ff);
	snd_soc_component_write(component, WM8510_PLLK3, pll_div.k & 0x1ff);
	reg = snd_soc_component_read32(component, WM8510_POWER1);
	snd_soc_component_write(component, WM8510_POWER1, reg | 0x020);

	/* Run CODEC from PLL instead of MCLK */
	reg = snd_soc_component_read32(component, WM8510_CLOCK);
	snd_soc_component_write(component, WM8510_CLOCK, reg | 0x100);

	return 0;
}