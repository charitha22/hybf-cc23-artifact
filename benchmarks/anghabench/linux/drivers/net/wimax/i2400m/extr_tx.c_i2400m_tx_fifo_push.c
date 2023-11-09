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
struct i2400m {int tx_in; size_t tx_out; void* tx_buf; } ;
struct device {int dummy; } ;

/* Variables and functions */
 int I2400M_TX_BUF_SIZE ; 
 void* TAIL_FULL ; 
 size_t __i2400m_tx_tail_room (struct i2400m*) ; 
 int /*<<< orphan*/  d_printf (int,struct device*,char*,size_t,size_t,...) ; 
 struct device* i2400m_dev (struct i2400m*) ; 

__attribute__((used)) static
void *i2400m_tx_fifo_push(struct i2400m *i2400m, size_t size,
			  size_t padding, bool try_head)
{
	struct device *dev = i2400m_dev(i2400m);
	size_t room, tail_room, needed_size;
	void *ptr;

	needed_size = size + padding;
	room = I2400M_TX_BUF_SIZE - (i2400m->tx_in - i2400m->tx_out);
	if (room < needed_size)	{ /* this takes care of Case B */
		d_printf(2, dev, "fifo push %zu/%zu: no space\n",
			 size, padding);
		return NULL;
	}
	/* Is there space at the tail? */
	tail_room = __i2400m_tx_tail_room(i2400m);
	if (!try_head && tail_room < needed_size) {
		/*
		 * If the tail room space is not enough to push the message
		 * in the TX FIFO, then there are two possibilities:
		 * 1. There is enough head room space to accommodate
		 * this message in the TX FIFO.
		 * 2. There is not enough space in the head room and
		 * in tail room of the TX FIFO to accommodate the message.
		 * In the case (1), return TAIL_FULL so that the caller
		 * can figure out, if the caller wants to push the message
		 * into the head room space.
		 * In the case (2), return NULL, indicating that the TX FIFO
		 * cannot accommodate the message.
		 */
		if (room - tail_room >= needed_size) {
			d_printf(2, dev, "fifo push %zu/%zu: tail full\n",
				 size, padding);
			return TAIL_FULL;	/* There might be head space */
		} else {
			d_printf(2, dev, "fifo push %zu/%zu: no head space\n",
				 size, padding);
			return NULL;	/* There is no space */
		}
	}
	ptr = i2400m->tx_buf + i2400m->tx_in % I2400M_TX_BUF_SIZE;
	d_printf(2, dev, "fifo push %zu/%zu: at @%zu\n", size, padding,
		 i2400m->tx_in % I2400M_TX_BUF_SIZE);
	i2400m->tx_in += size;
	return ptr;
}