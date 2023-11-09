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
struct TYPE_2__ {int /*<<< orphan*/  (* elsct_send ) (struct fc_lport*,int /*<<< orphan*/ ,struct fc_frame*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct fc_lport*,int) ;} ;
struct fc_lport {int r_a_tov; int e_d_tov; scalar_t__ vport; TYPE_1__ tt; scalar_t__ port_id; scalar_t__ point_to_multipoint; int /*<<< orphan*/  lp_mutex; } ;
struct fc_frame {int dummy; } ;
struct fc_els_flogi {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  ELS_FDISC ; 
 int /*<<< orphan*/  ELS_FLOGI ; 
 int /*<<< orphan*/  FC_FID_FLOGI ; 
 int /*<<< orphan*/  FC_LPORT_DBG (struct fc_lport*,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  LPORT_ST_FLOGI ; 
 struct fc_frame* fc_frame_alloc (struct fc_lport*,int) ; 
 int /*<<< orphan*/  fc_lport_enter_ready (struct fc_lport*) ; 
 void fc_lport_error (struct fc_lport*,struct fc_frame*) ; 
 int /*<<< orphan*/  fc_lport_flogi_resp ; 
 int /*<<< orphan*/  fc_lport_state (struct fc_lport*) ; 
 int /*<<< orphan*/  fc_lport_state_enter (struct fc_lport*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  lockdep_assert_held (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  stub1 (struct fc_lport*,int /*<<< orphan*/ ,struct fc_frame*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct fc_lport*,int) ; 

__attribute__((used)) static void fc_lport_enter_flogi(struct fc_lport *lport)
{
	struct fc_frame *fp;

	lockdep_assert_held(&lport->lp_mutex);

	FC_LPORT_DBG(lport, "Entered FLOGI state from %s state\n",
		     fc_lport_state(lport));

	fc_lport_state_enter(lport, LPORT_ST_FLOGI);

	if (lport->point_to_multipoint) {
		if (lport->port_id)
			fc_lport_enter_ready(lport);
		return;
	}

	fp = fc_frame_alloc(lport, sizeof(struct fc_els_flogi));
	if (!fp)
		return fc_lport_error(lport, fp);

	if (!lport->tt.elsct_send(lport, FC_FID_FLOGI, fp,
				  lport->vport ? ELS_FDISC : ELS_FLOGI,
				  fc_lport_flogi_resp, lport,
				  lport->vport ? 2 * lport->r_a_tov :
				  lport->e_d_tov))
		fc_lport_error(lport, NULL);
}