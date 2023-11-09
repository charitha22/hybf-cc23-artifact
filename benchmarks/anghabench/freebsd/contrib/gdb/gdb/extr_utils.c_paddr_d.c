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
typedef  int /*<<< orphan*/  LONGEST ;

/* Variables and functions */
 int /*<<< orphan*/  decimal2str (char*,char*,int /*<<< orphan*/ ) ; 
 char* get_cell () ; 

char *
paddr_d (LONGEST addr)
{
  char *paddr_str = get_cell ();
  if (addr < 0)
    decimal2str (paddr_str, "-", -addr);
  else
    decimal2str (paddr_str, "", addr);
  return paddr_str;
}