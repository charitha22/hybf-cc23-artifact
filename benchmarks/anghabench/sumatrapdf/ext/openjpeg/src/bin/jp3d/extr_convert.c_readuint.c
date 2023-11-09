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
typedef  int /*<<< orphan*/  FILE ;

/* Variables and functions */
 int /*<<< orphan*/  fread (unsigned char*,int,int,int /*<<< orphan*/ *) ; 

unsigned int readuint(FILE * f, int bigendian)
{
    unsigned char c1, c2, c3, c4;
    fread(&c1, 1, 1, f);
    fread(&c2, 1, 1, f);
    fread(&c3, 1, 1, f);
    fread(&c4, 1, 1, f);
    if (bigendian) {
        return (c1 << 24) + (c2 << 16) + (c3 << 8) + c4;
    } else {
        return (c4 << 24) + (c3 << 16) + (c2 << 8) + c1;
    }
}