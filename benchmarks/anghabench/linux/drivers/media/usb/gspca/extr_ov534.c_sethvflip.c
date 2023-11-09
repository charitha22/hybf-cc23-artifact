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
typedef  int u8 ;
struct sd {scalar_t__ sensor; } ;
struct gspca_dev {int dummy; } ;
typedef  scalar_t__ s32 ;

/* Variables and functions */
 scalar_t__ SENSOR_OV767x ; 
 int sccb_reg_read (struct gspca_dev*,int) ; 
 int /*<<< orphan*/  sccb_reg_write (struct gspca_dev*,int,int) ; 

__attribute__((used)) static void sethvflip(struct gspca_dev *gspca_dev, s32 hflip, s32 vflip)
{
	struct sd *sd = (struct sd *) gspca_dev;
	u8 val;

	if (sd->sensor == SENSOR_OV767x) {
		val = sccb_reg_read(gspca_dev, 0x1e);	/* mvfp */
		val &= ~0x30;
		if (hflip)
			val |= 0x20;
		if (vflip)
			val |= 0x10;
		sccb_reg_write(gspca_dev, 0x1e, val);
	} else {
		val = sccb_reg_read(gspca_dev, 0x0c);
		val &= ~0xc0;
		if (hflip == 0)
			val |= 0x40;
		if (vflip == 0)
			val |= 0x80;
		sccb_reg_write(gspca_dev, 0x0c, val);
	}
}