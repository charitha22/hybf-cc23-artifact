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
typedef  int u32 ;
struct mpc_i2c {int interrupt; int /*<<< orphan*/  dev; int /*<<< orphan*/  queue; scalar_t__ base; int /*<<< orphan*/  irq; } ;

/* Variables and functions */
 int /*<<< orphan*/  CCR_MEN ; 
 int CSR_MAL ; 
 int CSR_MCF ; 
 int CSR_MIF ; 
 int CSR_RXAK ; 
 int EAGAIN ; 
 int EIO ; 
 int ENXIO ; 
 int ETIMEDOUT ; 
 scalar_t__ MPC_I2C_SR ; 
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ ,char*) ; 
 unsigned long jiffies ; 
 int readb (scalar_t__) ; 
 int /*<<< orphan*/  schedule () ; 
 scalar_t__ time_after (unsigned long,unsigned int) ; 
 scalar_t__ unlikely (int) ; 
 int wait_event_timeout (int /*<<< orphan*/ ,int,unsigned int) ; 
 int /*<<< orphan*/  writeb (int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  writeccr (struct mpc_i2c*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int i2c_wait(struct mpc_i2c *i2c, unsigned timeout, int writing)
{
	unsigned long orig_jiffies = jiffies;
	u32 cmd_err;
	int result = 0;

	if (!i2c->irq) {
		while (!(readb(i2c->base + MPC_I2C_SR) & CSR_MIF)) {
			schedule();
			if (time_after(jiffies, orig_jiffies + timeout)) {
				dev_dbg(i2c->dev, "timeout\n");
				writeccr(i2c, 0);
				result = -ETIMEDOUT;
				break;
			}
		}
		cmd_err = readb(i2c->base + MPC_I2C_SR);
		writeb(0, i2c->base + MPC_I2C_SR);
	} else {
		/* Interrupt mode */
		result = wait_event_timeout(i2c->queue,
			(i2c->interrupt & CSR_MIF), timeout);

		if (unlikely(!(i2c->interrupt & CSR_MIF))) {
			dev_dbg(i2c->dev, "wait timeout\n");
			writeccr(i2c, 0);
			result = -ETIMEDOUT;
		}

		cmd_err = i2c->interrupt;
		i2c->interrupt = 0;
	}

	if (result < 0)
		return result;

	if (!(cmd_err & CSR_MCF)) {
		dev_dbg(i2c->dev, "unfinished\n");
		return -EIO;
	}

	if (cmd_err & CSR_MAL) {
		dev_dbg(i2c->dev, "MAL\n");
		return -EAGAIN;
	}

	if (writing && (cmd_err & CSR_RXAK)) {
		dev_dbg(i2c->dev, "No RXAK\n");
		/* generate stop */
		writeccr(i2c, CCR_MEN);
		return -ENXIO;
	}
	return 0;
}