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
typedef  int /*<<< orphan*/  u_long ;
typedef  int /*<<< orphan*/  buf ;

/* Variables and functions */
 int setenv (char*,char*,int) ; 
 int /*<<< orphan*/  snprintf (char*,int,char*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
cl_putenv(char *name, char *str, u_long value)
{
	char buf[40];

	if (str == NULL) {
		(void)snprintf(buf, sizeof(buf), "%lu", value);
		return (setenv(name, buf, 1));
	} else
		return (setenv(name, str, 1));
}