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
struct baycom_state {unsigned int baud; int opt_dcd; } ;

/* Variables and functions */
 unsigned int simple_strtoul (char const*,int /*<<< orphan*/ *,int) ; 
 scalar_t__ strchr (char const*,char) ; 
 int /*<<< orphan*/  strncmp (char const*,char*,int) ; 

__attribute__((used)) static int baycom_setmode(struct baycom_state *bc, const char *modestr)
{
	unsigned int baud;

	if (!strncmp(modestr, "ser", 3)) {
		baud = simple_strtoul(modestr+3, NULL, 10);
		if (baud >= 3 && baud <= 48)
			bc->baud = baud*100;
	}
	if (strchr(modestr, '*'))
		bc->opt_dcd = 0;
	else if (strchr(modestr, '+'))
		bc->opt_dcd = -1;
	else
		bc->opt_dcd = 1;
	return 0;
}