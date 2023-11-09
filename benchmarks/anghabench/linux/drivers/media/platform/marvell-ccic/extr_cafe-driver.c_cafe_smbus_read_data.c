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
typedef  unsigned int u8 ;
typedef  unsigned int u16 ;
struct mcam_camera {int /*<<< orphan*/  dev_lock; } ;
struct cafe_camera {int /*<<< orphan*/  smbus_wait; struct mcam_camera mcam; } ;

/* Variables and functions */
 int /*<<< orphan*/  CAFE_SMBUS_TIMEOUT ; 
 int EIO ; 
 int /*<<< orphan*/  REG_TWSIC0 ; 
 int /*<<< orphan*/  REG_TWSIC1 ; 
 unsigned int TWSIC0_CLKDIV ; 
 unsigned int TWSIC0_EN ; 
 unsigned int TWSIC0_OVMAGIC ; 
 unsigned int TWSIC0_SID ; 
 unsigned int TWSIC0_SID_SHIFT ; 
 unsigned int TWSIC1_ADDR ; 
 unsigned int TWSIC1_ADDR_SHIFT ; 
 unsigned int TWSIC1_ERROR ; 
 unsigned int TWSIC1_READ ; 
 unsigned int TWSIC1_RVALID ; 
 int /*<<< orphan*/  cafe_smbus_read_done (struct mcam_camera*) ; 
 int /*<<< orphan*/  cam_err (struct cafe_camera*,char*,unsigned int,unsigned int) ; 
 unsigned int mcam_reg_read (struct mcam_camera*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mcam_reg_write (struct mcam_camera*,int /*<<< orphan*/ ,unsigned int) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  wait_event_timeout (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int cafe_smbus_read_data(struct cafe_camera *cam,
		u16 addr, u8 command, u8 *value)
{
	unsigned int rval;
	unsigned long flags;
	struct mcam_camera *mcam = &cam->mcam;

	spin_lock_irqsave(&mcam->dev_lock, flags);
	rval = TWSIC0_EN | ((addr << TWSIC0_SID_SHIFT) & TWSIC0_SID);
	rval |= TWSIC0_OVMAGIC; /* Make OV sensors work */
	/*
	 * Marvel sez set clkdiv to all 1's for now.
	 */
	rval |= TWSIC0_CLKDIV;
	mcam_reg_write(mcam, REG_TWSIC0, rval);
	(void) mcam_reg_read(mcam, REG_TWSIC1); /* force write */
	rval = TWSIC1_READ | ((command << TWSIC1_ADDR_SHIFT) & TWSIC1_ADDR);
	mcam_reg_write(mcam, REG_TWSIC1, rval);
	spin_unlock_irqrestore(&mcam->dev_lock, flags);

	wait_event_timeout(cam->smbus_wait,
			cafe_smbus_read_done(mcam), CAFE_SMBUS_TIMEOUT);
	spin_lock_irqsave(&mcam->dev_lock, flags);
	rval = mcam_reg_read(mcam, REG_TWSIC1);
	spin_unlock_irqrestore(&mcam->dev_lock, flags);

	if (rval & TWSIC1_ERROR) {
		cam_err(cam, "SMBUS read (%02x/%02x) error\n", addr, command);
		return -EIO;
	}
	if (!(rval & TWSIC1_RVALID)) {
		cam_err(cam, "SMBUS read (%02x/%02x) timed out\n", addr,
				command);
		return -EIO;
	}
	*value = rval & 0xff;
	return 0;
}