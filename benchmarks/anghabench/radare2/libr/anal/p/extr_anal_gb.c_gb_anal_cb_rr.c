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
typedef  int ut8 ;
struct TYPE_7__ {int /*<<< orphan*/  esil; TYPE_2__* dst; TYPE_1__** src; } ;
struct TYPE_6__ {int memref; int /*<<< orphan*/  reg; } ;
struct TYPE_5__ {int imm; } ;
typedef  int /*<<< orphan*/  RReg ;
typedef  TYPE_3__ RAnalOp ;

/* Variables and functions */
 int /*<<< orphan*/  R_REG_TYPE_GPR ; 
 void* r_anal_value_new () ; 
 int /*<<< orphan*/  r_reg_get (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  r_strbuf_setf (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * regs_x ; 

__attribute__((used)) static inline void gb_anal_cb_rr (RReg *reg, RAnalOp *op, const ut8 data)
{
	op->dst = r_anal_value_new ();
	op->src[0] = r_anal_value_new ();
	op->src[0]->imm = 1;
	op->dst->reg = r_reg_get (reg, regs_x[data & 7], R_REG_TYPE_GPR);
	if ((data & 7) == 6) {
		op->dst->memref = 1;
		r_strbuf_setf (&op->esil, "1,%s,[1],&,H,:=,1,%s,[1],>>,7,C,<<,|,%s,=[1],H,C,:=,0,H,:=,0,N,:=", regs_x[data & 7], regs_x[data & 7], regs_x[data & 7]);
	} else {
		r_strbuf_setf (&op->esil, "1,%s,&,H,:=,1,%s,>>,7,C,<<,|,%s,=,H,C,:=,0,H,:=,0,N,:=", regs_x[data & 7], regs_x[data & 7], regs_x[data & 7]); //HACK
	}
}