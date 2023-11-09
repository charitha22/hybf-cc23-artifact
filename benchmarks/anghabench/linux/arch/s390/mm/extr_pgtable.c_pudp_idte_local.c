#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct TYPE_2__ {int /*<<< orphan*/  asce; } ;
struct mm_struct {TYPE_1__ context; } ;
typedef  int /*<<< orphan*/  pud_t ;

/* Variables and functions */
 int IDTE_GUEST_ASCE ; 
 int /*<<< orphan*/  IDTE_LOCAL ; 
 int IDTE_NODAT ; 
 scalar_t__ MACHINE_HAS_TLB_GUEST ; 
 int /*<<< orphan*/  __pudp_idte (unsigned long,int /*<<< orphan*/ *,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline void pudp_idte_local(struct mm_struct *mm,
				   unsigned long addr, pud_t *pudp)
{
	if (MACHINE_HAS_TLB_GUEST)
		__pudp_idte(addr, pudp, IDTE_NODAT | IDTE_GUEST_ASCE,
			    mm->context.asce, IDTE_LOCAL);
	else
		__pudp_idte(addr, pudp, 0, 0, IDTE_LOCAL);
}