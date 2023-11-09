#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int uint32_t ;
typedef  int /*<<< orphan*/  uint16_t ;
struct comedi_subdevice {struct comedi_async* async; } ;
struct comedi_device {int /*<<< orphan*/  spinlock; } ;
struct comedi_cmd {scalar_t__ convert_src; int chanlist_len; int* chanlist; int flags; scalar_t__ start_src; int start_arg; scalar_t__ stop_src; int stop_arg; } ;
struct comedi_async {struct comedi_cmd cmd; } ;
struct TYPE_7__ {scalar_t__ layout; } ;
struct TYPE_6__ {int adc_control1_bits; int ai_dma_desc_bus_addr; int ai_cmd_running; scalar_t__ main_iobase; TYPE_1__* ai_dma_desc; scalar_t__ ai_dma_index; } ;
struct TYPE_5__ {int /*<<< orphan*/  transfer_size; } ;

/* Variables and functions */
 scalar_t__ ADC_BUFFER_CLEAR_REG ; 
 scalar_t__ ADC_CONTROL0_REG ; 
 scalar_t__ ADC_CONTROL1_REG ; 
 int ADC_DITHER_BIT ; 
 int ADC_DMA_DISABLE_BIT ; 
 int ADC_ENABLE_BIT ; 
 int ADC_GATE_LEVEL_BIT ; 
 int ADC_HI_CHANNEL_4020_MASK ; 
 int ADC_LO_CHANNEL_4020_MASK ; 
 int ADC_MODE_MASK ; 
 int ADC_SAMPLE_COUNTER_EN_BIT ; 
 int ADC_SOFT_GATE_BITS ; 
 scalar_t__ ADC_START_REG ; 
 int ADC_START_TRIG_EXT_BITS ; 
 int ADC_START_TRIG_FALLING_BIT ; 
 int ADC_START_TRIG_SOFT_BITS ; 
 int ADC_SW_GATE_BIT ; 
 scalar_t__ CALIBRATION_REG ; 
 int CHANNEL_MODE_4020_MASK ; 
 scalar_t__ CR_CHAN (int) ; 
 int CR_INVERT ; 
 scalar_t__ DAQ_ATRIG_LOW_4020_REG ; 
 int /*<<< orphan*/  DEBUG_PRINT (char*,...) ; 
 int EXT_START_TRIG_BNC_BIT ; 
 int EXT_STOP_TRIG_BNC_BIT ; 
 int FOUR_CHANNEL_4020_BITS ; 
 scalar_t__ LAYOUT_4020 ; 
 int PLX_DESC_IN_PCI_BIT ; 
 int PLX_INTR_TERM_COUNT ; 
 int PLX_XFER_LOCAL_TO_PCI ; 
 scalar_t__ TRIG_EXT ; 
 scalar_t__ TRIG_NOW ; 
 int TRIG_WAKE_EOS ; 
 int TWO_CHANNEL_4020_BITS ; 
 int /*<<< orphan*/  abort_dma (struct comedi_device*,int) ; 
 int adc_hi_chan_4020_bits (scalar_t__) ; 
 int adc_lo_chan_4020_bits (scalar_t__) ; 
 int adc_mode_bits (int) ; 
 unsigned int ai_dma_ring_count (TYPE_3__*) ; 
 TYPE_3__* board (struct comedi_device*) ; 
 int /*<<< orphan*/  cpu_to_le32 (int) ; 
 int /*<<< orphan*/  disable_ai_pacing (struct comedi_device*) ; 
 int /*<<< orphan*/  dma_start_sync (struct comedi_device*,int) ; 
 int dma_transfer_size (struct comedi_device*) ; 
 int /*<<< orphan*/  enable_ai_interrupts (struct comedi_device*,struct comedi_cmd*) ; 
 int /*<<< orphan*/  load_first_dma_descriptor (struct comedi_device*,int,int) ; 
 TYPE_2__* priv (struct comedi_device*) ; 
 int /*<<< orphan*/  set_ai_pacing (struct comedi_device*,struct comedi_cmd*) ; 
 int setup_channel_queue (struct comedi_device*,struct comedi_cmd*) ; 
 int /*<<< orphan*/  setup_sample_counters (struct comedi_device*,struct comedi_cmd*) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 scalar_t__ use_hw_sample_counter (struct comedi_cmd*) ; 
 int /*<<< orphan*/  writew (int,scalar_t__) ; 

__attribute__((used)) static int ai_cmd(struct comedi_device *dev, struct comedi_subdevice *s)
{
	struct comedi_async *async = s->async;
	struct comedi_cmd *cmd = &async->cmd;
	uint32_t bits;
	unsigned int i;
	unsigned long flags;
	int retval;

	disable_ai_pacing(dev);
	abort_dma(dev, 1);

	retval = setup_channel_queue(dev, cmd);
	if (retval < 0)
		return retval;

	/*  make sure internal calibration source is turned off */
	writew(0, priv(dev)->main_iobase + CALIBRATION_REG);

	set_ai_pacing(dev, cmd);

	setup_sample_counters(dev, cmd);

	enable_ai_interrupts(dev, cmd);

	spin_lock_irqsave(&dev->spinlock, flags);
	/* set mode, allow conversions through software gate */
	priv(dev)->adc_control1_bits |= ADC_SW_GATE_BIT;
	priv(dev)->adc_control1_bits &= ~ADC_DITHER_BIT;
	if (board(dev)->layout != LAYOUT_4020) {
		priv(dev)->adc_control1_bits &= ~ADC_MODE_MASK;
		if (cmd->convert_src == TRIG_EXT)
			priv(dev)->adc_control1_bits |= adc_mode_bits(13);	/*  good old mode 13 */
		else
			priv(dev)->adc_control1_bits |= adc_mode_bits(8);	/*  mode 8.  What else could you need? */
	} else {
		priv(dev)->adc_control1_bits &= ~CHANNEL_MODE_4020_MASK;
		if (cmd->chanlist_len == 4)
			priv(dev)->adc_control1_bits |= FOUR_CHANNEL_4020_BITS;
		else if (cmd->chanlist_len == 2)
			priv(dev)->adc_control1_bits |= TWO_CHANNEL_4020_BITS;
		priv(dev)->adc_control1_bits &= ~ADC_LO_CHANNEL_4020_MASK;
		priv(dev)->adc_control1_bits |=
		    adc_lo_chan_4020_bits(CR_CHAN(cmd->chanlist[0]));
		priv(dev)->adc_control1_bits &= ~ADC_HI_CHANNEL_4020_MASK;
		priv(dev)->adc_control1_bits |=
		    adc_hi_chan_4020_bits(CR_CHAN
					  (cmd->
					   chanlist[cmd->chanlist_len - 1]));
	}
	writew(priv(dev)->adc_control1_bits,
	       priv(dev)->main_iobase + ADC_CONTROL1_REG);
	DEBUG_PRINT("control1 bits 0x%x\n", priv(dev)->adc_control1_bits);
	spin_unlock_irqrestore(&dev->spinlock, flags);

	/*  clear adc buffer */
	writew(0, priv(dev)->main_iobase + ADC_BUFFER_CLEAR_REG);

	if ((cmd->flags & TRIG_WAKE_EOS) == 0 ||
	    board(dev)->layout == LAYOUT_4020) {
		priv(dev)->ai_dma_index = 0;

		/*  set dma transfer size */
		for (i = 0; i < ai_dma_ring_count(board(dev)); i++)
			priv(dev)->ai_dma_desc[i].transfer_size =
			    cpu_to_le32(dma_transfer_size(dev) *
					sizeof(uint16_t));

		/*  give location of first dma descriptor */
		load_first_dma_descriptor(dev, 1,
					  priv(dev)->ai_dma_desc_bus_addr |
					  PLX_DESC_IN_PCI_BIT |
					  PLX_INTR_TERM_COUNT |
					  PLX_XFER_LOCAL_TO_PCI);

		dma_start_sync(dev, 1);
	}

	if (board(dev)->layout == LAYOUT_4020) {
		/* set source for external triggers */
		bits = 0;
		if (cmd->start_src == TRIG_EXT && CR_CHAN(cmd->start_arg))
			bits |= EXT_START_TRIG_BNC_BIT;
		if (cmd->stop_src == TRIG_EXT && CR_CHAN(cmd->stop_arg))
			bits |= EXT_STOP_TRIG_BNC_BIT;
		writew(bits, priv(dev)->main_iobase + DAQ_ATRIG_LOW_4020_REG);
	}

	spin_lock_irqsave(&dev->spinlock, flags);

	/* enable pacing, triggering, etc */
	bits = ADC_ENABLE_BIT | ADC_SOFT_GATE_BITS | ADC_GATE_LEVEL_BIT;
	if (cmd->flags & TRIG_WAKE_EOS)
		bits |= ADC_DMA_DISABLE_BIT;
	/*  set start trigger */
	if (cmd->start_src == TRIG_EXT) {
		bits |= ADC_START_TRIG_EXT_BITS;
		if (cmd->start_arg & CR_INVERT)
			bits |= ADC_START_TRIG_FALLING_BIT;
	} else if (cmd->start_src == TRIG_NOW)
		bits |= ADC_START_TRIG_SOFT_BITS;
	if (use_hw_sample_counter(cmd))
		bits |= ADC_SAMPLE_COUNTER_EN_BIT;
	writew(bits, priv(dev)->main_iobase + ADC_CONTROL0_REG);
	DEBUG_PRINT("control0 bits 0x%x\n", bits);

	priv(dev)->ai_cmd_running = 1;

	spin_unlock_irqrestore(&dev->spinlock, flags);

	/*  start aquisition */
	if (cmd->start_src == TRIG_NOW) {
		writew(0, priv(dev)->main_iobase + ADC_START_REG);
		DEBUG_PRINT("soft trig\n");
	}

	return 0;
}