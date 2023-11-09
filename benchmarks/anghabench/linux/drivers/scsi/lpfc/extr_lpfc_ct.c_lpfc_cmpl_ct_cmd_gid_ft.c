#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_19__   TYPE_9__ ;
typedef  struct TYPE_18__   TYPE_8__ ;
typedef  struct TYPE_17__   TYPE_7__ ;
typedef  struct TYPE_16__   TYPE_6__ ;
typedef  struct TYPE_15__   TYPE_5__ ;
typedef  struct TYPE_14__   TYPE_4__ ;
typedef  struct TYPE_13__   TYPE_3__ ;
typedef  struct TYPE_12__   TYPE_2__ ;
typedef  struct TYPE_11__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ uint32_t ;
struct lpfc_vport {scalar_t__ fc_ns_retry; int load_flag; int fc_flag; int gidft_inp; scalar_t__ fc_rscn_id_cnt; scalar_t__ num_disc_nodes; scalar_t__ port_state; } ;
struct TYPE_18__ {scalar_t__ CmdRsp; } ;
struct TYPE_17__ {TYPE_8__ bits; } ;
struct TYPE_12__ {int /*<<< orphan*/  Fc4Type; } ;
struct TYPE_13__ {TYPE_2__ gid; } ;
struct lpfc_sli_ct_request {scalar_t__ ReasonCode; scalar_t__ Explanation; TYPE_7__ CommandResponse; TYPE_3__ un; } ;
struct lpfc_nodelist {int dummy; } ;
struct TYPE_11__ {struct lpfc_nodelist* ndlp; struct lpfc_iocbq* rsp_iocb; } ;
struct TYPE_14__ {scalar_t__ bdeSize; } ;
struct TYPE_15__ {TYPE_4__ bdl; } ;
struct TYPE_16__ {scalar_t__* ulpWord; TYPE_5__ genreq64; } ;
struct TYPE_19__ {scalar_t__ ulpStatus; TYPE_6__ un; } ;
struct lpfc_iocbq {TYPE_1__ context_un; TYPE_9__ iocb; scalar_t__ context2; scalar_t__ context1; struct lpfc_vport* vport; } ;
struct lpfc_hba {int dummy; } ;
struct lpfc_dmabuf {scalar_t__ virt; } ;
struct Scsi_Host {int /*<<< orphan*/  host_lock; } ;
typedef  TYPE_9__ IOCB_t ;

/* Variables and functions */
 int FC_RSCN_DEFERRED ; 
 int FC_RSCN_MODE ; 
 int FC_UNLOADING ; 
 int /*<<< orphan*/  FC_VPORT_FAILED ; 
 int IOERR_NO_RESOURCES ; 
 int IOERR_PARAM_MASK ; 
 int IOSTAT_LOCAL_REJECT ; 
 int /*<<< orphan*/  KERN_ERR ; 
 int /*<<< orphan*/  KERN_INFO ; 
 int /*<<< orphan*/  LOG_DISCOVERY ; 
 int /*<<< orphan*/  LOG_ELS ; 
 scalar_t__ LPFC_DISC_AUTH ; 
 int /*<<< orphan*/  LPFC_DISC_TRC_CT ; 
 scalar_t__ LPFC_MAX_NS_RETRY ; 
 int /*<<< orphan*/  SLI_CTNS_GID_FT ; 
 scalar_t__ SLI_CT_NO_FC4_TYPES ; 
 int /*<<< orphan*/  SLI_CT_RESPONSE_FS_ACC ; 
 int /*<<< orphan*/  SLI_CT_RESPONSE_FS_RJT ; 
 scalar_t__ SLI_CT_UNABLE_TO_PERFORM_REQ ; 
 scalar_t__ be16_to_cpu (int /*<<< orphan*/ ) ; 
 scalar_t__ cpu_to_be16 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  lpfc_ct_free_iocb (struct lpfc_hba*,struct lpfc_iocbq*) ; 
 int /*<<< orphan*/  lpfc_debugfs_disc_trc (struct lpfc_vport*,int /*<<< orphan*/ ,char*,scalar_t__,scalar_t__,scalar_t__) ; 
 int /*<<< orphan*/  lpfc_disc_start (struct lpfc_vport*) ; 
 scalar_t__ lpfc_els_chk_latt (struct lpfc_vport*) ; 
 int /*<<< orphan*/  lpfc_els_flush_rscn (struct lpfc_vport*) ; 
 int /*<<< orphan*/  lpfc_els_handle_rscn (struct lpfc_vport*) ; 
 scalar_t__ lpfc_error_lost_link (TYPE_9__*) ; 
 int lpfc_get_gidft_type (struct lpfc_vport*,struct lpfc_iocbq*) ; 
 int lpfc_ns_cmd (struct lpfc_vport*,int /*<<< orphan*/ ,scalar_t__,int) ; 
 int /*<<< orphan*/  lpfc_ns_rsp (struct lpfc_vport*,struct lpfc_dmabuf*,int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  lpfc_printf_vlog (struct lpfc_vport*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,...) ; 
 struct Scsi_Host* lpfc_shost_from_vport (struct lpfc_vport*) ; 
 int /*<<< orphan*/  lpfc_vport_set_state (struct lpfc_vport*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spin_lock_irq (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spin_unlock_irq (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
lpfc_cmpl_ct_cmd_gid_ft(struct lpfc_hba *phba, struct lpfc_iocbq *cmdiocb,
			struct lpfc_iocbq *rspiocb)
{
	struct lpfc_vport *vport = cmdiocb->vport;
	struct Scsi_Host *shost = lpfc_shost_from_vport(vport);
	IOCB_t *irsp;
	struct lpfc_dmabuf *outp;
	struct lpfc_dmabuf *inp;
	struct lpfc_sli_ct_request *CTrsp;
	struct lpfc_sli_ct_request *CTreq;
	struct lpfc_nodelist *ndlp;
	int rc, type;

	/* First save ndlp, before we overwrite it */
	ndlp = cmdiocb->context_un.ndlp;

	/* we pass cmdiocb to state machine which needs rspiocb as well */
	cmdiocb->context_un.rsp_iocb = rspiocb;
	inp = (struct lpfc_dmabuf *) cmdiocb->context1;
	outp = (struct lpfc_dmabuf *) cmdiocb->context2;
	irsp = &rspiocb->iocb;

	lpfc_debugfs_disc_trc(vport, LPFC_DISC_TRC_CT,
		 "GID_FT cmpl:     status:x%x/x%x rtry:%d",
		irsp->ulpStatus, irsp->un.ulpWord[4], vport->fc_ns_retry);

	/* Don't bother processing response if vport is being torn down. */
	if (vport->load_flag & FC_UNLOADING) {
		if (vport->fc_flag & FC_RSCN_MODE)
			lpfc_els_flush_rscn(vport);
		goto out;
	}

	if (lpfc_els_chk_latt(vport)) {
		lpfc_printf_vlog(vport, KERN_INFO, LOG_DISCOVERY,
				 "0216 Link event during NS query\n");
		if (vport->fc_flag & FC_RSCN_MODE)
			lpfc_els_flush_rscn(vport);
		lpfc_vport_set_state(vport, FC_VPORT_FAILED);
		goto out;
	}
	if (lpfc_error_lost_link(irsp)) {
		lpfc_printf_vlog(vport, KERN_INFO, LOG_DISCOVERY,
				 "0226 NS query failed due to link event\n");
		if (vport->fc_flag & FC_RSCN_MODE)
			lpfc_els_flush_rscn(vport);
		goto out;
	}

	spin_lock_irq(shost->host_lock);
	if (vport->fc_flag & FC_RSCN_DEFERRED) {
		vport->fc_flag &= ~FC_RSCN_DEFERRED;
		spin_unlock_irq(shost->host_lock);

		/* This is a GID_FT completing so the gidft_inp counter was
		 * incremented before the GID_FT was issued to the wire.
		 */
		vport->gidft_inp--;

		/*
		 * Skip processing the NS response
		 * Re-issue the NS cmd
		 */
		lpfc_printf_vlog(vport, KERN_INFO, LOG_ELS,
				 "0151 Process Deferred RSCN Data: x%x x%x\n",
				 vport->fc_flag, vport->fc_rscn_id_cnt);
		lpfc_els_handle_rscn(vport);

		goto out;
	}
	spin_unlock_irq(shost->host_lock);

	if (irsp->ulpStatus) {
		/* Check for retry */
		if (vport->fc_ns_retry < LPFC_MAX_NS_RETRY) {
			if (irsp->ulpStatus != IOSTAT_LOCAL_REJECT ||
			    (irsp->un.ulpWord[4] & IOERR_PARAM_MASK) !=
			    IOERR_NO_RESOURCES)
				vport->fc_ns_retry++;

			type = lpfc_get_gidft_type(vport, cmdiocb);
			if (type == 0)
				goto out;

			/* CT command is being retried */
			vport->gidft_inp--;
			rc = lpfc_ns_cmd(vport, SLI_CTNS_GID_FT,
					 vport->fc_ns_retry, type);
			if (rc == 0)
				goto out;
		}
		if (vport->fc_flag & FC_RSCN_MODE)
			lpfc_els_flush_rscn(vport);
		lpfc_vport_set_state(vport, FC_VPORT_FAILED);
		lpfc_printf_vlog(vport, KERN_ERR, LOG_ELS,
				 "0257 GID_FT Query error: 0x%x 0x%x\n",
				 irsp->ulpStatus, vport->fc_ns_retry);
	} else {
		/* Good status, continue checking */
		CTreq = (struct lpfc_sli_ct_request *) inp->virt;
		CTrsp = (struct lpfc_sli_ct_request *) outp->virt;
		if (CTrsp->CommandResponse.bits.CmdRsp ==
		    cpu_to_be16(SLI_CT_RESPONSE_FS_ACC)) {
			lpfc_printf_vlog(vport, KERN_INFO, LOG_DISCOVERY,
					 "0208 NameServer Rsp Data: x%x x%x "
					 "sz x%x\n",
					 vport->fc_flag,
					 CTreq->un.gid.Fc4Type,
					 irsp->un.genreq64.bdl.bdeSize);

			lpfc_ns_rsp(vport,
				    outp,
				    CTreq->un.gid.Fc4Type,
				    (uint32_t) (irsp->un.genreq64.bdl.bdeSize));
		} else if (CTrsp->CommandResponse.bits.CmdRsp ==
			   be16_to_cpu(SLI_CT_RESPONSE_FS_RJT)) {
			/* NameServer Rsp Error */
			if ((CTrsp->ReasonCode == SLI_CT_UNABLE_TO_PERFORM_REQ)
			    && (CTrsp->Explanation == SLI_CT_NO_FC4_TYPES)) {
				lpfc_printf_vlog(vport, KERN_INFO,
					LOG_DISCOVERY,
					"0269 No NameServer Entries "
					"Data: x%x x%x x%x x%x\n",
					CTrsp->CommandResponse.bits.CmdRsp,
					(uint32_t) CTrsp->ReasonCode,
					(uint32_t) CTrsp->Explanation,
					vport->fc_flag);

				lpfc_debugfs_disc_trc(vport, LPFC_DISC_TRC_CT,
				"GID_FT no entry  cmd:x%x rsn:x%x exp:x%x",
				(uint32_t)CTrsp->CommandResponse.bits.CmdRsp,
				(uint32_t) CTrsp->ReasonCode,
				(uint32_t) CTrsp->Explanation);
			} else {
				lpfc_printf_vlog(vport, KERN_INFO,
					LOG_DISCOVERY,
					"0240 NameServer Rsp Error "
					"Data: x%x x%x x%x x%x\n",
					CTrsp->CommandResponse.bits.CmdRsp,
					(uint32_t) CTrsp->ReasonCode,
					(uint32_t) CTrsp->Explanation,
					vport->fc_flag);

				lpfc_debugfs_disc_trc(vport, LPFC_DISC_TRC_CT,
				"GID_FT rsp err1  cmd:x%x rsn:x%x exp:x%x",
				(uint32_t)CTrsp->CommandResponse.bits.CmdRsp,
				(uint32_t) CTrsp->ReasonCode,
				(uint32_t) CTrsp->Explanation);
			}


		} else {
			/* NameServer Rsp Error */
			lpfc_printf_vlog(vport, KERN_ERR, LOG_DISCOVERY,
					"0241 NameServer Rsp Error "
					"Data: x%x x%x x%x x%x\n",
					CTrsp->CommandResponse.bits.CmdRsp,
					(uint32_t) CTrsp->ReasonCode,
					(uint32_t) CTrsp->Explanation,
					vport->fc_flag);

			lpfc_debugfs_disc_trc(vport, LPFC_DISC_TRC_CT,
				"GID_FT rsp err2  cmd:x%x rsn:x%x exp:x%x",
				(uint32_t)CTrsp->CommandResponse.bits.CmdRsp,
				(uint32_t) CTrsp->ReasonCode,
				(uint32_t) CTrsp->Explanation);
		}
		vport->gidft_inp--;
	}

	lpfc_printf_vlog(vport, KERN_INFO, LOG_DISCOVERY,
			 "4216 GID_FT cmpl inp %d disc %d\n",
			 vport->gidft_inp, vport->num_disc_nodes);

	/* Link up / RSCN discovery */
	if ((vport->num_disc_nodes == 0) &&
	    (vport->gidft_inp == 0)) {
		/*
		 * The driver has cycled through all Nports in the RSCN payload.
		 * Complete the handling by cleaning up and marking the
		 * current driver state.
		 */
		if (vport->port_state >= LPFC_DISC_AUTH) {
			if (vport->fc_flag & FC_RSCN_MODE) {
				lpfc_els_flush_rscn(vport);
				spin_lock_irq(shost->host_lock);
				vport->fc_flag |= FC_RSCN_MODE; /* RSCN still */
				spin_unlock_irq(shost->host_lock);
			}
			else
				lpfc_els_flush_rscn(vport);
		}

		lpfc_disc_start(vport);
	}
out:
	cmdiocb->context_un.ndlp = ndlp; /* Now restore ndlp for free */
	lpfc_ct_free_iocb(phba, cmdiocb);
	return;
}