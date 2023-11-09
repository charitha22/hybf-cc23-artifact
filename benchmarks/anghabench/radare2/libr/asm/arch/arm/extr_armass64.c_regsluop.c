#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int ut32 ;
struct TYPE_5__ {TYPE_1__* operands; } ;
struct TYPE_4__ {int reg_type; int type; int immediate; int reg; } ;
typedef  TYPE_2__ ArmOp ;

/* Variables and functions */
 int ARM_GPR ; 
 int ARM_REG32 ; 
 int UT32_MAX ; 
 int countTrailingZeros (int) ; 

__attribute__((used)) static ut32 regsluop(ArmOp *op, int k) {
	ut32 data = UT32_MAX;

	if (op->operands[1].reg_type & ARM_REG32) {
		return data;
	}
	if (op->operands[0].reg_type & ARM_REG32) {
		k -= 0x40;
	}
	if (op->operands[2].type & ARM_GPR) {
		return data;
	}

	int n = op->operands[2].immediate;
	if (n > 0xff || n < -0x100) {
		return data;
	}

	data = k | op->operands[0].reg << 24 | op->operands[1].reg << 29 | (op->operands[1].reg & 56) << 13;

	if (n < 0) {
		n *= -1;
		data |= ( 0xf & (0xf - (n - 1)) ) << 20;

		if (countTrailingZeros(n) > 3) {
			data |= (0x1f - ((n >> 4) - 1)) << 8;
		} else {
			data |= (0x1f - (n >> 4)) << 8;
		}
	} else {
		data |= (0xf & (n & 63)) << 20;
		if (countTrailingZeros(n) < 4) {
			data |= (n >> 4) << 8;
		} else {
			data |= (0xff & n) << 4;
		}
		data |= (n >> 8) << 8;
	}

	return data;
}