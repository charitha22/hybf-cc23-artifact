#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {unsigned int fdc; int* fdv; } ;
typedef  TYPE_1__ vlclua_dtable_t ;
typedef  int /*<<< orphan*/  lua_State ;

/* Variables and functions */
 TYPE_1__* vlclua_get_dtable (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int vlclua_fd_get_lua( lua_State *L, int fd )
{
    vlclua_dtable_t *dt = vlclua_get_dtable( L );

    if( (unsigned)fd < 3u )
        return fd;
    for( unsigned i = 0; i < dt->fdc; i++ )
        if( dt->fdv[i] == fd )
            return 3 + i;
    return -1;
}