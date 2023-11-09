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
typedef  int /*<<< orphan*/  VGLBitmap ;

/* Variables and functions */
 int /*<<< orphan*/  VGLSetXY (int /*<<< orphan*/ *,int,int,int /*<<< orphan*/ ) ; 

void
plot(VGLBitmap * object, int x, int y, int flag, u_long color)
{
  /* non-zero flag indicates the pixels need swapping back. */
  if (flag)
    VGLSetXY(object, y, x, color);
  else
    VGLSetXY(object, x, y, color);
}