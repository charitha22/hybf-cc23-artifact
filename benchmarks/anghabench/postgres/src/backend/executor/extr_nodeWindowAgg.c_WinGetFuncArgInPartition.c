#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_16__   TYPE_5__ ;
typedef  struct TYPE_15__   TYPE_4__ ;
typedef  struct TYPE_14__   TYPE_3__ ;
typedef  struct TYPE_13__   TYPE_2__ ;
typedef  struct TYPE_12__   TYPE_1__ ;

/* Type definitions */
typedef  int int64 ;
typedef  TYPE_3__* WindowObject ;
struct TYPE_12__ {TYPE_5__* ps_ExprContext; } ;
struct TYPE_13__ {TYPE_1__ ps; } ;
struct TYPE_15__ {int /*<<< orphan*/  spooled_rows; int /*<<< orphan*/  currentpos; int /*<<< orphan*/ * temp_slot_1; TYPE_2__ ss; } ;
typedef  TYPE_4__ WindowAggState ;
typedef  int /*<<< orphan*/  TupleTableSlot ;
struct TYPE_16__ {int /*<<< orphan*/ * ecxt_outertuple; } ;
struct TYPE_14__ {int /*<<< orphan*/  argstates; TYPE_4__* winstate; } ;
typedef  int /*<<< orphan*/  ExprState ;
typedef  TYPE_5__ ExprContext ;
typedef  int /*<<< orphan*/  Datum ;

/* Variables and functions */
 int /*<<< orphan*/  Assert (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ERROR ; 
 int /*<<< orphan*/  ExecEvalExpr (int /*<<< orphan*/ *,TYPE_5__*,int*) ; 
#define  WINDOW_SEEK_CURRENT 130 
#define  WINDOW_SEEK_HEAD 129 
#define  WINDOW_SEEK_TAIL 128 
 int /*<<< orphan*/  WinSetMarkPosition (TYPE_3__*,int) ; 
 int /*<<< orphan*/  WindowObjectIsValid (TYPE_3__*) ; 
 int /*<<< orphan*/  elog (int /*<<< orphan*/ ,char*,int) ; 
 scalar_t__ list_nth (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  spool_tuples (TYPE_4__*,int) ; 
 int window_gettupleslot (TYPE_3__*,int,int /*<<< orphan*/ *) ; 

Datum
WinGetFuncArgInPartition(WindowObject winobj, int argno,
						 int relpos, int seektype, bool set_mark,
						 bool *isnull, bool *isout)
{
	WindowAggState *winstate;
	ExprContext *econtext;
	TupleTableSlot *slot;
	bool		gottuple;
	int64		abs_pos;

	Assert(WindowObjectIsValid(winobj));
	winstate = winobj->winstate;
	econtext = winstate->ss.ps.ps_ExprContext;
	slot = winstate->temp_slot_1;

	switch (seektype)
	{
		case WINDOW_SEEK_CURRENT:
			abs_pos = winstate->currentpos + relpos;
			break;
		case WINDOW_SEEK_HEAD:
			abs_pos = relpos;
			break;
		case WINDOW_SEEK_TAIL:
			spool_tuples(winstate, -1);
			abs_pos = winstate->spooled_rows - 1 + relpos;
			break;
		default:
			elog(ERROR, "unrecognized window seek type: %d", seektype);
			abs_pos = 0;		/* keep compiler quiet */
			break;
	}

	gottuple = window_gettupleslot(winobj, abs_pos, slot);

	if (!gottuple)
	{
		if (isout)
			*isout = true;
		*isnull = true;
		return (Datum) 0;
	}
	else
	{
		if (isout)
			*isout = false;
		if (set_mark)
			WinSetMarkPosition(winobj, abs_pos);
		econtext->ecxt_outertuple = slot;
		return ExecEvalExpr((ExprState *) list_nth(winobj->argstates, argno),
							econtext, isnull);
	}
}