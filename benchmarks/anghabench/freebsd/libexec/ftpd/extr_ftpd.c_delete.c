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
struct stat {int /*<<< orphan*/  st_mode; } ;

/* Variables and functions */
 int /*<<< orphan*/  LOGCMD (char*,char*) ; 
 scalar_t__ S_ISDIR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ack (char*) ; 
 scalar_t__ guest ; 
 scalar_t__ lstat (char*,struct stat*) ; 
 scalar_t__ noguestmod ; 
 int /*<<< orphan*/  perror_reply (int,char*) ; 
 int /*<<< orphan*/  reply (int,char*) ; 
 scalar_t__ rmdir (char*) ; 
 scalar_t__ unlink (char*) ; 

void
delete(char *name)
{
	struct stat st;

	LOGCMD("delete", name);
	if (lstat(name, &st) < 0) {
		perror_reply(550, name);
		return;
	}
	if (S_ISDIR(st.st_mode)) {
		if (rmdir(name) < 0) {
			perror_reply(550, name);
			return;
		}
		goto done;
	}
	if (guest && noguestmod) {
		reply(550, "Operation not permitted.");
		return;
	}
	if (unlink(name) < 0) {
		perror_reply(550, name);
		return;
	}
done:
	ack("DELE");
}