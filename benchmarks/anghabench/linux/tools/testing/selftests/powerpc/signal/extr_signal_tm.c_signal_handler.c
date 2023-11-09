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

/* Variables and functions */
 int SIGUSR1 ; 
 int fail ; 
 int signaled ; 
 scalar_t__ tcheck_active () ; 

__attribute__((used)) static void signal_handler(int sig)
{
	if (tcheck_active()) {
		fail = 2;
		return;
	}

	if (sig == SIGUSR1)
		signaled = 1;
	else
		fail = 1;
}