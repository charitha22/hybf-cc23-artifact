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
struct snd_emu10k1 {int /*<<< orphan*/  emu_lock; scalar_t__ port; } ;

/* Variables and functions */
 scalar_t__ DATA ; 
 int HLIPH ; 
 int HLIPL ; 
 scalar_t__ PTR ; 
 int /*<<< orphan*/  outl (unsigned int,scalar_t__) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 

void snd_emu10k1_voice_half_loop_intr_ack(struct snd_emu10k1 *emu, unsigned int voicenum)
{
	unsigned long flags;

	spin_lock_irqsave(&emu->emu_lock, flags);
	/* voice interrupt */
	if (voicenum >= 32) {
		outl(HLIPH << 16, emu->port + PTR);
		voicenum = 1 << (voicenum - 32);
	} else {
		outl(HLIPL << 16, emu->port + PTR);
		voicenum = 1 << voicenum;
	}
	outl(voicenum, emu->port + DATA);
	spin_unlock_irqrestore(&emu->emu_lock, flags);
}