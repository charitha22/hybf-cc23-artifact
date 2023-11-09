#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int /*<<< orphan*/  port_id; } ;
struct fc_rport_priv {int /*<<< orphan*/  kref; TYPE_2__ ids; struct fc_lport* local_port; } ;
struct TYPE_3__ {int /*<<< orphan*/  (* elsct_send ) (struct fc_lport*,int /*<<< orphan*/ ,struct fc_frame*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct fc_rport_priv*,int) ;} ;
struct fc_lport {int r_a_tov; TYPE_1__ tt; int /*<<< orphan*/  point_to_multipoint; } ;
struct fc_frame {int dummy; } ;
struct fc_els_flogi {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  ELS_FLOGI ; 
 int /*<<< orphan*/  FC_RPORT_DBG (struct fc_rport_priv*,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  RPORT_ST_FLOGI ; 
 struct fc_frame* fc_frame_alloc (struct fc_lport*,int) ; 
 void fc_rport_enter_plogi (struct fc_rport_priv*) ; 
 void fc_rport_error_retry (struct fc_rport_priv*,struct fc_frame*) ; 
 int /*<<< orphan*/  fc_rport_flogi_resp ; 
 int /*<<< orphan*/  fc_rport_state (struct fc_rport_priv*) ; 
 int /*<<< orphan*/  fc_rport_state_enter (struct fc_rport_priv*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kref_get (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  stub1 (struct fc_lport*,int /*<<< orphan*/ ,struct fc_frame*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct fc_rport_priv*,int) ; 

__attribute__((used)) static void fc_rport_enter_flogi(struct fc_rport_priv *rdata)
{
	struct fc_lport *lport = rdata->local_port;
	struct fc_frame *fp;

	if (!lport->point_to_multipoint)
		return fc_rport_enter_plogi(rdata);

	FC_RPORT_DBG(rdata, "Entered FLOGI state from %s state\n",
		     fc_rport_state(rdata));

	fc_rport_state_enter(rdata, RPORT_ST_FLOGI);

	fp = fc_frame_alloc(lport, sizeof(struct fc_els_flogi));
	if (!fp)
		return fc_rport_error_retry(rdata, fp);

	if (!lport->tt.elsct_send(lport, rdata->ids.port_id, fp, ELS_FLOGI,
				  fc_rport_flogi_resp, rdata,
				  2 * lport->r_a_tov))
		fc_rport_error_retry(rdata, NULL);
	else
		kref_get(&rdata->kref);
}