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
typedef  int /*<<< orphan*/  PutBitContext ;

/* Variables and functions */
 int /*<<< orphan*/  put_bits (int /*<<< orphan*/ *,int,int) ; 

__attribute__((used)) static inline void put_alpha_run(PutBitContext *pb, int run)
{
    if (run) {
        put_bits(pb, 1, 0);
        if (run < 0x10)
            put_bits(pb, 4, run);
        else
            put_bits(pb, 15, run);
    } else {
        put_bits(pb, 1, 1);
    }
}