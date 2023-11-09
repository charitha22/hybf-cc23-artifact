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
struct comedi_subdevice {int dummy; } ;
struct comedi_insn {int n; } ;
struct comedi_device {int dummy; } ;
struct TYPE_2__ {scalar_t__ b_TimerSelectMode; scalar_t__ iobase; } ;

/* Variables and functions */
 scalar_t__ ADDIDATA_TIMER ; 
 scalar_t__ ADDIDATA_WATCHDOG ; 
 scalar_t__ APCI3501_TCW_TRIG_STATUS ; 
 scalar_t__ APCI3501_WATCHDOG ; 
 TYPE_1__* devpriv ; 
 int inl (scalar_t__) ; 
 int /*<<< orphan*/  printk (char*) ; 

int i_APCI3501_ReadTimerCounterWatchdog(struct comedi_device *dev,
	struct comedi_subdevice *s, struct comedi_insn *insn, unsigned int *data)
{

	if (devpriv->b_TimerSelectMode == ADDIDATA_WATCHDOG) {
		data[0] =
			inl(devpriv->iobase + APCI3501_WATCHDOG +
			APCI3501_TCW_TRIG_STATUS) & 0x1;
		data[1] = inl(devpriv->iobase + APCI3501_WATCHDOG);
	}			/*  end if  (devpriv->b_TimerSelectMode==ADDIDATA_WATCHDOG) */

	else if (devpriv->b_TimerSelectMode == ADDIDATA_TIMER) {
		data[0] =
			inl(devpriv->iobase + APCI3501_WATCHDOG +
			APCI3501_TCW_TRIG_STATUS) & 0x1;
		data[1] = inl(devpriv->iobase + APCI3501_WATCHDOG);
	}			/*  end if  (devpriv->b_TimerSelectMode==ADDIDATA_TIMER) */

	else if ((devpriv->b_TimerSelectMode != ADDIDATA_TIMER)
		&& (devpriv->b_TimerSelectMode != ADDIDATA_WATCHDOG)) {
		printk("\nIn ReadTimerCounterWatchdog :: Invalid Subdevice \n");
	}
	return insn->n;
}