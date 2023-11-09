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
struct ctl_scsiio {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  SSD_ELEM_NONE ; 
 int /*<<< orphan*/  SSD_KEY_MEDIUM_ERROR ; 
 int /*<<< orphan*/  ctl_set_sense (struct ctl_scsiio*,int,int /*<<< orphan*/ ,int,int,int /*<<< orphan*/ ) ; 

void
ctl_set_medium_error(struct ctl_scsiio *ctsio, int read)
{
	if (read) {
		/* "Unrecovered read error" */
		ctl_set_sense(ctsio,
			      /*current_error*/ 1,
			      /*sense_key*/ SSD_KEY_MEDIUM_ERROR,
			      /*asc*/ 0x11,
			      /*ascq*/ 0x00,
			      SSD_ELEM_NONE);
	} else {
		/* "Write error - auto reallocation failed" */
		ctl_set_sense(ctsio,
			      /*current_error*/ 1,
			      /*sense_key*/ SSD_KEY_MEDIUM_ERROR,
			      /*asc*/ 0x0C,
			      /*ascq*/ 0x02,
			      SSD_ELEM_NONE);
	}
}