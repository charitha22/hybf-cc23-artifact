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
typedef  int apr_uint64_t ;
typedef  int /*<<< orphan*/  apr_int64_t ;

/* Variables and functions */

__attribute__((used)) static apr_int64_t
decode_int(apr_uint64_t value)
{
  return (apr_int64_t)(value % 2 ? -1 - value / 2 : value / 2);
}