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

/* Variables and functions */
 int /*<<< orphan*/  exit (int) ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*,unsigned long) ; 
 unsigned long get_dscr () ; 
 unsigned long get_dscr_usr () ; 
 int /*<<< orphan*/  stderr ; 

__attribute__((used)) static void do_exec(unsigned long parent_dscr)
{
	unsigned long cur_dscr, cur_dscr_usr;

	cur_dscr = get_dscr();
	cur_dscr_usr = get_dscr_usr();

	if (cur_dscr != parent_dscr) {
		fprintf(stderr, "Parent DSCR %ld was not inherited "
				"over exec (kernel value)\n", parent_dscr);
		exit(1);
	}

	if (cur_dscr_usr != parent_dscr) {
		fprintf(stderr, "Parent DSCR %ld was not inherited "
				"over exec (user value)\n", parent_dscr);
		exit(1);
	}
	exit(0);
}