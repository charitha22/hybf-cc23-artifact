#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct bfa_lps_s {int bfa_tag; TYPE_1__* bfa; int /*<<< orphan*/  fdisc; int /*<<< orphan*/  wqe; int /*<<< orphan*/  reqq; } ;
typedef  enum bfa_lps_event { ____Placeholder_bfa_lps_event } bfa_lps_event ;
struct TYPE_5__ {int /*<<< orphan*/  plog; } ;

/* Variables and functions */
#define  BFA_LPS_SM_DELETE 134 
#define  BFA_LPS_SM_FWRSP 133 
#define  BFA_LPS_SM_LOGIN 132 
#define  BFA_LPS_SM_LOGOUT 131 
#define  BFA_LPS_SM_OFFLINE 130 
#define  BFA_LPS_SM_RX_CVL 129 
#define  BFA_LPS_SM_SET_N2N_PID 128 
 int /*<<< orphan*/  BFA_PL_EID_LOGIN ; 
 int /*<<< orphan*/  BFA_PL_MID_LPS ; 
 int /*<<< orphan*/  bfa_lps_free (struct bfa_lps_s*) ; 
 int /*<<< orphan*/  bfa_lps_logout_comp (struct bfa_lps_s*) ; 
 int /*<<< orphan*/  bfa_lps_send_login (struct bfa_lps_s*) ; 
 int /*<<< orphan*/  bfa_lps_sm_login ; 
 int /*<<< orphan*/  bfa_lps_sm_loginwait ; 
 int /*<<< orphan*/  bfa_plog_str (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  bfa_reqq_full (TYPE_1__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bfa_reqq_wait (TYPE_1__*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  bfa_sm_fault (TYPE_1__*,int) ; 
 int /*<<< orphan*/  bfa_sm_set_state (struct bfa_lps_s*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bfa_trc (TYPE_1__*,int) ; 

__attribute__((used)) static void
bfa_lps_sm_init(struct bfa_lps_s *lps, enum bfa_lps_event event)
{
	bfa_trc(lps->bfa, lps->bfa_tag);
	bfa_trc(lps->bfa, event);

	switch (event) {
	case BFA_LPS_SM_LOGIN:
		if (bfa_reqq_full(lps->bfa, lps->reqq)) {
			bfa_sm_set_state(lps, bfa_lps_sm_loginwait);
			bfa_reqq_wait(lps->bfa, lps->reqq, &lps->wqe);
		} else {
			bfa_sm_set_state(lps, bfa_lps_sm_login);
			bfa_lps_send_login(lps);
		}

		if (lps->fdisc)
			bfa_plog_str(lps->bfa->plog, BFA_PL_MID_LPS,
				BFA_PL_EID_LOGIN, 0, "FDISC Request");
		else
			bfa_plog_str(lps->bfa->plog, BFA_PL_MID_LPS,
				BFA_PL_EID_LOGIN, 0, "FLOGI Request");
		break;

	case BFA_LPS_SM_LOGOUT:
		bfa_lps_logout_comp(lps);
		break;

	case BFA_LPS_SM_DELETE:
		bfa_lps_free(lps);
		break;

	case BFA_LPS_SM_RX_CVL:
	case BFA_LPS_SM_OFFLINE:
		break;

	case BFA_LPS_SM_FWRSP:
		/*
		 * Could happen when fabric detects loopback and discards
		 * the lps request. Fw will eventually sent out the timeout
		 * Just ignore
		 */
		break;
	case BFA_LPS_SM_SET_N2N_PID:
		/*
		 * When topology is set to loop, bfa_lps_set_n2n_pid() sends
		 * this event. Ignore this event.
		 */
		break;

	default:
		bfa_sm_fault(lps->bfa, event);
	}
}