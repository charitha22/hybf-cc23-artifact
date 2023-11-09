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
typedef  int /*<<< orphan*/  WINDOW ;

/* Variables and functions */
 int check_arg_count (int,int) ; 
 int /*<<< orphan*/  mvwscanw (int /*<<< orphan*/ *,int,int,char*,char**) ; 
 int /*<<< orphan*/  report_count (int) ; 
 int /*<<< orphan*/  report_error (char*) ; 
 int /*<<< orphan*/  report_int (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  report_status (char*) ; 
 scalar_t__ sscanf (char*,char*,int*) ; 

void
cmd_mvwscanw(int nargs, char **args)
{
	int y, x;
	WINDOW *win;
	char string[256];

	if (check_arg_count(nargs, 4) == 1)
		return;

	if (sscanf(args[0], "%p", &win) == 0) {
		report_count(1);
		report_error("BAD ARGUMENT");
		return;
	}

	if (sscanf(args[1], "%d", &y) == 0) {
		report_count(1);
		report_error("BAD ARGUMENT");
		return;
	}

	if (sscanf(args[2], "%d", &x) == 0) {
		report_count(1);
		report_error("BAD ARGUMENT");
		return;
	}

	/* XXX - call2 */
	report_count(2);
	report_int(mvwscanw(win, y, x, args[3], &string));
	report_status(string);
}