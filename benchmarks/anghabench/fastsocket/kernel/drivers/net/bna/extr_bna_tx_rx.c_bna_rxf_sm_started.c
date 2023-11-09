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
struct bna_rxf {int /*<<< orphan*/  flags; } ;
typedef  enum bna_rxf_event { ____Placeholder_bna_rxf_event } bna_rxf_event ;

/* Variables and functions */
 int /*<<< orphan*/  BNA_RXF_F_PAUSED ; 
#define  RXF_E_CONFIG 131 
#define  RXF_E_FAIL 130 
#define  RXF_E_PAUSE 129 
#define  RXF_E_STOP 128 
 int /*<<< orphan*/  bfa_fsm_set_state (struct bna_rxf*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bfa_sm_fault (int) ; 
 int /*<<< orphan*/  bna_rxf_cfg_reset (struct bna_rxf*) ; 
 int /*<<< orphan*/  bna_rxf_fltr_clear (struct bna_rxf*) ; 
 int /*<<< orphan*/  bna_rxf_sm_cfg_wait ; 
 int /*<<< orphan*/  bna_rxf_sm_fltr_clr_wait ; 
 int /*<<< orphan*/  bna_rxf_sm_paused ; 
 int /*<<< orphan*/  bna_rxf_sm_stopped ; 

__attribute__((used)) static void
bna_rxf_sm_started(struct bna_rxf *rxf, enum bna_rxf_event event)
{
	switch (event) {
	case RXF_E_STOP:
	case RXF_E_FAIL:
		bna_rxf_cfg_reset(rxf);
		bfa_fsm_set_state(rxf, bna_rxf_sm_stopped);
		break;

	case RXF_E_CONFIG:
		bfa_fsm_set_state(rxf, bna_rxf_sm_cfg_wait);
		break;

	case RXF_E_PAUSE:
		rxf->flags |= BNA_RXF_F_PAUSED;
		if (!bna_rxf_fltr_clear(rxf))
			bfa_fsm_set_state(rxf, bna_rxf_sm_paused);
		else
			bfa_fsm_set_state(rxf, bna_rxf_sm_fltr_clr_wait);
		break;

	default:
		bfa_sm_fault(event);
	}
}