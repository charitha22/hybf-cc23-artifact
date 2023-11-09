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
struct pf_status {int /*<<< orphan*/  running; } ;

/* Variables and functions */
 int /*<<< orphan*/  DIOCGETSTATUS ; 
 int /*<<< orphan*/  LOG_ERR ; 
 int /*<<< orphan*/  O_RDWR ; 
 int /*<<< orphan*/  PF_LOG ; 
 int /*<<< orphan*/  PF_LOG_ALL ; 
 int dev ; 
 int /*<<< orphan*/  exit (int) ; 
 int ioctl (int,int /*<<< orphan*/ ,struct pf_status*) ; 
 int open (char*,int /*<<< orphan*/ ) ; 
 char* qname ; 
 int /*<<< orphan*/  rule_log ; 
 int /*<<< orphan*/  syslog (int /*<<< orphan*/ ,char*) ; 

void
init_filter(char *opt_qname, int opt_verbose)
{
	struct pf_status status;

	qname = opt_qname;

	if (opt_verbose == 1)
		rule_log = PF_LOG;
	else if (opt_verbose == 2)
		rule_log = PF_LOG_ALL;

	dev = open("/dev/pf", O_RDWR);	
	if (dev == -1) {
		syslog(LOG_ERR, "can't open /dev/pf");
		exit(1);
	}
	if (ioctl(dev, DIOCGETSTATUS, &status) == -1) {
		syslog(LOG_ERR, "DIOCGETSTATUS");
		exit(1);
	}
	if (!status.running) {
		syslog(LOG_ERR, "pf is disabled");
		exit(1);
	}
}