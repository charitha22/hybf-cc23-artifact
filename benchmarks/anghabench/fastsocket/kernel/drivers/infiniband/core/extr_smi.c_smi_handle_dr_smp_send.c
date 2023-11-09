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
typedef  scalar_t__ u8 ;
struct ib_smp {scalar_t__ hop_ptr; scalar_t__ hop_cnt; int* initial_path; scalar_t__ dr_dlid; int* return_path; scalar_t__ dr_slid; } ;
typedef  enum smi_action { ____Placeholder_smi_action } smi_action ;

/* Variables and functions */
 scalar_t__ IB_LID_PERMISSIVE ; 
 int IB_SMI_DISCARD ; 
 int IB_SMI_HANDLE ; 
 scalar_t__ IB_SMP_MAX_PATH_HOPS ; 
 scalar_t__ RDMA_NODE_IB_SWITCH ; 
 int /*<<< orphan*/  ib_get_smp_direction (struct ib_smp*) ; 

enum smi_action smi_handle_dr_smp_send(struct ib_smp *smp,
				       u8 node_type, int port_num)
{
	u8 hop_ptr, hop_cnt;

	hop_ptr = smp->hop_ptr;
	hop_cnt = smp->hop_cnt;

	/* See section 14.2.2.2, Vol 1 IB spec */
	/* C14-6 -- valid hop_cnt values are from 0 to 63 */
	if (hop_cnt >= IB_SMP_MAX_PATH_HOPS)
		return IB_SMI_DISCARD;

	if (!ib_get_smp_direction(smp)) {
		/* C14-9:1 */
		if (hop_cnt && hop_ptr == 0) {
			smp->hop_ptr++;
			return (smp->initial_path[smp->hop_ptr] ==
				port_num ? IB_SMI_HANDLE : IB_SMI_DISCARD);
		}

		/* C14-9:2 */
		if (hop_ptr && hop_ptr < hop_cnt) {
			if (node_type != RDMA_NODE_IB_SWITCH)
				return IB_SMI_DISCARD;

			/* smp->return_path set when received */
			smp->hop_ptr++;
			return (smp->initial_path[smp->hop_ptr] ==
				port_num ? IB_SMI_HANDLE : IB_SMI_DISCARD);
		}

		/* C14-9:3 -- We're at the end of the DR segment of path */
		if (hop_ptr == hop_cnt) {
			/* smp->return_path set when received */
			smp->hop_ptr++;
			return (node_type == RDMA_NODE_IB_SWITCH ||
				smp->dr_dlid == IB_LID_PERMISSIVE ?
				IB_SMI_HANDLE : IB_SMI_DISCARD);
		}

		/* C14-9:4 -- hop_ptr = hop_cnt + 1 -> give to SMA/SM */
		/* C14-9:5 -- Fail unreasonable hop pointer */
		return (hop_ptr == hop_cnt + 1 ? IB_SMI_HANDLE : IB_SMI_DISCARD);

	} else {
		/* C14-13:1 */
		if (hop_cnt && hop_ptr == hop_cnt + 1) {
			smp->hop_ptr--;
			return (smp->return_path[smp->hop_ptr] ==
				port_num ? IB_SMI_HANDLE : IB_SMI_DISCARD);
		}

		/* C14-13:2 */
		if (2 <= hop_ptr && hop_ptr <= hop_cnt) {
			if (node_type != RDMA_NODE_IB_SWITCH)
				return IB_SMI_DISCARD;

			smp->hop_ptr--;
			return (smp->return_path[smp->hop_ptr] ==
				port_num ? IB_SMI_HANDLE : IB_SMI_DISCARD);
		}

		/* C14-13:3 -- at the end of the DR segment of path */
		if (hop_ptr == 1) {
			smp->hop_ptr--;
			/* C14-13:3 -- SMPs destined for SM shouldn't be here */
			return (node_type == RDMA_NODE_IB_SWITCH ||
				smp->dr_slid == IB_LID_PERMISSIVE ?
				IB_SMI_HANDLE : IB_SMI_DISCARD);
		}

		/* C14-13:4 -- hop_ptr = 0 -> should have gone to SM */
		if (hop_ptr == 0)
			return IB_SMI_HANDLE;

		/* C14-13:5 -- Check for unreasonable hop pointer */
		return IB_SMI_DISCARD;
	}
}