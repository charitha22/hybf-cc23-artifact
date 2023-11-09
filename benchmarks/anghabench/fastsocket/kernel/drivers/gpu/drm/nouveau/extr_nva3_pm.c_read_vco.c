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
typedef  int u32 ;
struct nouveau_device {int dummy; } ;
struct drm_device {int dummy; } ;

/* Variables and functions */
 struct nouveau_device* nouveau_dev (struct drm_device*) ; 
 int nv_rd32 (struct nouveau_device*,int) ; 
 int read_pll (struct drm_device*,int,int) ; 

__attribute__((used)) static u32
read_vco(struct drm_device *dev, int clk)
{
	struct nouveau_device *device = nouveau_dev(dev);
	u32 sctl = nv_rd32(device, 0x4120 + (clk * 4));
	if ((sctl & 0x00000030) != 0x00000030)
		return read_pll(dev, 0x41, 0x00e820);
	return read_pll(dev, 0x42, 0x00e8a0);
}