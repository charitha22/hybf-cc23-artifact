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
typedef  int /*<<< orphan*/  in_addr_t ;

/* Variables and functions */
 int /*<<< orphan*/  AF_INET ; 
 int /*<<< orphan*/  M_WARN ; 
 int get_addr_generic (int /*<<< orphan*/ ,unsigned int,char const*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int,int volatile*,int /*<<< orphan*/ ) ; 

in_addr_t
getaddr(unsigned int flags,
        const char *hostname,
        int resolve_retry_seconds,
        bool *succeeded,
        volatile int *signal_received)
{
    in_addr_t addr;
    int status;

    status = get_addr_generic(AF_INET, flags, hostname, &addr, NULL,
                              resolve_retry_seconds, signal_received,
                              M_WARN);
    if (status==0)
    {
        if (succeeded)
        {
            *succeeded = true;
        }
        return addr;
    }
    else
    {
        if (succeeded)
        {
            *succeeded = false;
        }
        return 0;
    }
}