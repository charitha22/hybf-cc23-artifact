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
struct device_attribute {int dummy; } ;
struct device {int dummy; } ;
typedef  int /*<<< orphan*/  ssize_t ;

/* Variables and functions */
 scalar_t__ LEGACY_BOOTING ; 
 scalar_t__ LEGACY_SUSPEND ; 
 int /*<<< orphan*/  PAGE_SIZE ; 
 scalar_t__ lighting_control_state ; 
 int /*<<< orphan*/  scnprintf (char*,int /*<<< orphan*/ ,char*) ; 

__attribute__((used)) static ssize_t show_control_state(struct device *dev,
				  struct device_attribute *attr, char *buf)
{
	if (lighting_control_state == LEGACY_BOOTING)
		return scnprintf(buf, PAGE_SIZE, "[booting] running suspend\n");
	else if (lighting_control_state == LEGACY_SUSPEND)
		return scnprintf(buf, PAGE_SIZE, "booting running [suspend]\n");
	return scnprintf(buf, PAGE_SIZE, "booting [running] suspend\n");
}