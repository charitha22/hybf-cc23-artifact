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
typedef  scalar_t__ uint32_t ;
struct ifdrv {int ifd_len; int /*<<< orphan*/  ifd_cmd; struct ifbreq* ifd_data; int /*<<< orphan*/  ifd_name; } ;
struct ifbreq {int /*<<< orphan*/  ifbr_ifsflags; int /*<<< orphan*/  ifbr_ifsname; } ;
struct bridge_port {scalar_t__ priv_set; char const* p_name; } ;
typedef  int /*<<< orphan*/  b_req ;

/* Variables and functions */
 int /*<<< orphan*/  BRDGGIFFLGS ; 
 int /*<<< orphan*/  BRDGSIFFLGS ; 
 int /*<<< orphan*/  IFBIF_PRIVATE ; 
 int /*<<< orphan*/  LOG_ERR ; 
 int /*<<< orphan*/  SIOCGDRVSPEC ; 
 int /*<<< orphan*/  SIOCSDRVSPEC ; 
 int SNMP_ERR_WRONG_VALUE ; 
 scalar_t__ TruthValue_false ; 
 scalar_t__ TruthValue_true ; 
 int /*<<< orphan*/  bzero (struct ifbreq*,int) ; 
 int /*<<< orphan*/  errno ; 
 scalar_t__ ioctl (int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct ifdrv*) ; 
 int /*<<< orphan*/  sock ; 
 int /*<<< orphan*/  strerror (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  strlcpy (int /*<<< orphan*/ ,char const*,int) ; 
 int /*<<< orphan*/  syslog (int /*<<< orphan*/ ,char*,char const*,int /*<<< orphan*/ ) ; 

int
bridge_port_set_private(const char *bif_name, struct bridge_port *bp,
    uint32_t priv_set)
{
	struct ifdrv ifd;
	struct ifbreq b_req;

	if (bp->priv_set == priv_set)
		return (0);

	bzero(&b_req, sizeof(b_req));
	strlcpy(ifd.ifd_name, bif_name, sizeof(ifd.ifd_name));
	ifd.ifd_len = sizeof(b_req);
	ifd.ifd_data = &b_req;
	strlcpy(b_req.ifbr_ifsname, bp->p_name, sizeof(b_req.ifbr_ifsname));
	ifd.ifd_cmd = BRDGGIFFLGS;

	if (ioctl(sock, SIOCGDRVSPEC, &ifd) < 0) {
		syslog(LOG_ERR, "get member %s param: ioctl(BRDGGIFFLGS) "
		    "failed: %s", bp->p_name, strerror(errno));
		return (-1);
	}

	if (priv_set == TruthValue_true)
		b_req.ifbr_ifsflags |= IFBIF_PRIVATE;
	else if (priv_set == TruthValue_false)
		b_req.ifbr_ifsflags &= ~IFBIF_PRIVATE;
	else
		return (SNMP_ERR_WRONG_VALUE);

	ifd.ifd_cmd = BRDGSIFFLGS;
	if (ioctl(sock, SIOCSDRVSPEC, &ifd) < 0) {
		syslog(LOG_ERR, "set member %s param: ioctl(BRDGSIFFLGS) "
		    "failed: %s", bp->p_name, strerror(errno));
		return (-1);
	}

	bp->priv_set = priv_set;

	return (0);
}