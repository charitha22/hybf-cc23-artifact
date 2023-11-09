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
 char const* norm2 (char*,double,char*,int) ; 

__attribute__((used)) static __inline const char *
norm(char *buf, double val, int normalize)
{
	if (normalize)
		return norm2(buf, val, "%.3f %s", normalize);
	else
		return norm2(buf, val, "%.0f %s", normalize);
}