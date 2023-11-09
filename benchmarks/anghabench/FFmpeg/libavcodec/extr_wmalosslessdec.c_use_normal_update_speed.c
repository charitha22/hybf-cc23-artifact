#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {int* cdlms_ttl; int* update_speed; TYPE_1__** cdlms; scalar_t__ bV3RTM; } ;
typedef  TYPE_2__ WmallDecodeCtx ;
struct TYPE_4__ {int recent; int order; int* lms_updates; } ;

/* Variables and functions */

__attribute__((used)) static void use_normal_update_speed(WmallDecodeCtx *s, int ich)
{
    int ilms, recent, icoef;
    for (ilms = s->cdlms_ttl[ich] - 1; ilms >= 0; ilms--) {
        recent = s->cdlms[ich][ilms].recent;
        if (s->update_speed[ich] == 8)
            continue;
        if (s->bV3RTM)
            for (icoef = 0; icoef < s->cdlms[ich][ilms].order; icoef++)
                s->cdlms[ich][ilms].lms_updates[icoef + recent] /= 2;
        else
            for (icoef = 0; icoef < s->cdlms[ich][ilms].order; icoef++)
                s->cdlms[ich][ilms].lms_updates[icoef] /= 2;
    }
    s->update_speed[ich] = 8;
}