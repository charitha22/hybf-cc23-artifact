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
typedef  int /*<<< orphan*/  VOID ;
typedef  scalar_t__ BOOLEAN ;

/* Variables and functions */
 int /*<<< orphan*/  PcVideoDefineCursor (int,int) ; 

VOID
PcVideoHideShowTextCursor(BOOLEAN Show)
{
  if (Show)
    {
      PcVideoDefineCursor(0x0D, 0x0E);
    }
  else
    {
      PcVideoDefineCursor(0x20, 0x00);
    }
}