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
struct bna_rxf {int flags; } ;
typedef  enum bna_rxf_event { ____Placeholder_bna_rxf_event } bna_rxf_event ;

/* Variables and functions */
 int BNA_RXF_F_PAUSED ; 
#define  RXF_E_CONFIG 133 
#define  RXF_E_FAIL 132 
#define  RXF_E_PAUSE 131 
#define  RXF_E_RESUME 130 
#define  RXF_E_START 129 
#define  RXF_E_STOP 128 
 int /*<<< orphan*/  bfa_fsm_set_state (struct bna_rxf*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bfa_sm_fault (int) ; 
 int /*<<< orphan*/  bna_rxf_sm_cfg_wait ; 
 int /*<<< orphan*/  bna_rxf_sm_paused ; 
 int /*<<< orphan*/  call_rxf_cam_fltr_cbfn (struct bna_rxf*) ; 
 int /*<<< orphan*/  call_rxf_pause_cbfn (struct bna_rxf*) ; 
 int /*<<< orphan*/  call_rxf_resume_cbfn (struct bna_rxf*) ; 
 int /*<<< orphan*/  call_rxf_start_cbfn (struct bna_rxf*) ; 
 int /*<<< orphan*/  call_rxf_stop_cbfn (struct bna_rxf*) ; 

__attribute__((used)) static void
bna_rxf_sm_stopped(struct bna_rxf *rxf, enum bna_rxf_event event)
{
	switch (event) {
	case RXF_E_START:
		if (rxf->flags & BNA_RXF_F_PAUSED) {
			bfa_fsm_set_state(rxf, bna_rxf_sm_paused);
			call_rxf_start_cbfn(rxf);
		} else
			bfa_fsm_set_state(rxf, bna_rxf_sm_cfg_wait);
		break;

	case RXF_E_STOP:
		call_rxf_stop_cbfn(rxf);
		break;

	case RXF_E_FAIL:
		/* No-op */
		break;

	case RXF_E_CONFIG:
		call_rxf_cam_fltr_cbfn(rxf);
		break;

	case RXF_E_PAUSE:
		rxf->flags |= BNA_RXF_F_PAUSED;
		call_rxf_pause_cbfn(rxf);
		break;

	case RXF_E_RESUME:
		rxf->flags &= ~BNA_RXF_F_PAUSED;
		call_rxf_resume_cbfn(rxf);
		break;

	default:
		bfa_sm_fault(event);
	}
}