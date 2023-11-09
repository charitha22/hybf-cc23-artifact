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
typedef  int uint8_t ;
struct regulator_dev {int dummy; } ;
struct device {int dummy; } ;
struct da903x_regulator_info {int max_uV; int min_uV; int step_uV; int vol_shift; int vol_nbits; int /*<<< orphan*/  vol_reg; } ;

/* Variables and functions */
 int EINVAL ; 
 scalar_t__ check_range (struct da903x_regulator_info*,int,int) ; 
 int da903x_update (struct device*,int /*<<< orphan*/ ,int,int) ; 
 int /*<<< orphan*/  pr_err (char*,int,int) ; 
 struct da903x_regulator_info* rdev_get_drvdata (struct regulator_dev*) ; 
 struct device* to_da903x_dev (struct regulator_dev*) ; 

__attribute__((used)) static int da9030_set_ldo14_voltage(struct regulator_dev *rdev,
				  int min_uV, int max_uV)
{
	struct da903x_regulator_info *info = rdev_get_drvdata(rdev);
	struct device *da903x_dev = to_da903x_dev(rdev);
	uint8_t val, mask;
	int thresh;

	if (check_range(info, min_uV, max_uV)) {
		pr_err("invalid voltage range (%d, %d) uV\n", min_uV, max_uV);
		return -EINVAL;
	}

	thresh = (info->max_uV + info->min_uV) / 2;
	if (min_uV < thresh) {
		val = (thresh - min_uV + info->step_uV - 1) / info->step_uV;
		val |= 0x4;
	} else {
		val = (min_uV - thresh + info->step_uV - 1) / info->step_uV;
	}

	val <<= info->vol_shift;
	mask = ((1 << info->vol_nbits) - 1)  << info->vol_shift;

	return da903x_update(da903x_dev, info->vol_reg, val, mask);
}