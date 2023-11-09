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
typedef  int uint8_t ;
typedef  int uint32_t ;

/* Variables and functions */

__attribute__((used)) static
uint32_t read32(uint8_t* arr, int pos,  int swapBytes)
{

    if(!swapBytes) {

        return (arr[pos]   << 24) |
               (arr[pos+1] << 16) |
               (arr[pos+2] << 8) |
                arr[pos+3];
    }

    return arr[pos] |
           (arr[pos+1] << 8) |
           (arr[pos+2] << 16) |
           (arr[pos+3] << 24);
}