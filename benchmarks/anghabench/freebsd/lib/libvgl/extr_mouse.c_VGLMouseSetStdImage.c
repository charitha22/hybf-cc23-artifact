#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct TYPE_2__ {int VXsize; } ;

/* Variables and functions */
 TYPE_1__* VGLDisplay ; 
 int /*<<< orphan*/  VGLMouseLargeAndMask ; 
 int /*<<< orphan*/  VGLMouseLargeOrMask ; 
 int /*<<< orphan*/  VGLMouseSetImage (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  VGLMouseSmallAndMask ; 
 int /*<<< orphan*/  VGLMouseSmallOrMask ; 

void
VGLMouseSetStdImage()
{
  if (VGLDisplay->VXsize > 800)
    VGLMouseSetImage(&VGLMouseLargeAndMask, &VGLMouseLargeOrMask);
  else
    VGLMouseSetImage(&VGLMouseSmallAndMask, &VGLMouseSmallOrMask);
}