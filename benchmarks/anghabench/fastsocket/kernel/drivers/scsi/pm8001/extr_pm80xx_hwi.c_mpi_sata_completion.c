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
typedef  int u8 ;
typedef  size_t u32 ;
struct task_status_struct {size_t residual; int buf_valid_size; void* stat; void* resp; void* open_rej_reason; scalar_t__ buf; } ;
struct set_dev_bits_fis {int dummy; } ;
struct sata_completion_resp {size_t* sata_resp; int /*<<< orphan*/  param; int /*<<< orphan*/  tag; int /*<<< orphan*/  status; } ;
struct TYPE_4__ {int /*<<< orphan*/  use_ncq; int /*<<< orphan*/  dma_xfer; } ;
struct sas_task {int task_state_flags; int /*<<< orphan*/  (* task_done ) (struct sas_task*) ;int /*<<< orphan*/  task_state_lock; scalar_t__ uldd_task; TYPE_2__ ata_task; int /*<<< orphan*/  data_dir; struct task_status_struct task_status; TYPE_1__* dev; int /*<<< orphan*/  lldd_task; } ;
struct pm8001_hba_info {int /*<<< orphan*/  lock; struct pm8001_ccb_info* ccb_info; } ;
struct pm8001_device {int id; int /*<<< orphan*/  running_req; } ;
struct pm8001_ccb_info {struct pm8001_device* device; struct sas_task* task; } ;
struct pio_setup_fis {int dummy; } ;
struct dev_to_host_fis {int dummy; } ;
struct ata_task_resp {int frame_len; int /*<<< orphan*/ * ending_fis; } ;
struct TYPE_3__ {struct pm8001_device* lldd_dev; } ;

/* Variables and functions */
#define  IO_ABORTED 157 
#define  IO_DS_IN_ERROR 156 
#define  IO_DS_IN_RECOVERY 155 
#define  IO_DS_NON_OPERATIONAL 154 
#define  IO_NO_DEVICE 153 
#define  IO_OPEN_CNX_ERROR_BAD_DESTINATION 152 
#define  IO_OPEN_CNX_ERROR_BREAK 151 
#define  IO_OPEN_CNX_ERROR_CONNECTION_RATE_NOT_SUPPORTED 150 
#define  IO_OPEN_CNX_ERROR_HW_RESOURCE_BUSY 149 
#define  IO_OPEN_CNX_ERROR_IT_NEXUS_LOSS 148 
#define  IO_OPEN_CNX_ERROR_IT_NEXUS_LOSS_NO_DEST 147 
#define  IO_OPEN_CNX_ERROR_IT_NEXUS_LOSS_OPEN_COLLIDE 146 
#define  IO_OPEN_CNX_ERROR_IT_NEXUS_LOSS_OPEN_TMO 145 
#define  IO_OPEN_CNX_ERROR_IT_NEXUS_LOSS_PATHWAY_BLOCKED 144 
#define  IO_OPEN_CNX_ERROR_PROTOCOL_NOT_SUPPORTED 143 
#define  IO_OPEN_CNX_ERROR_STP_RESOURCES_BUSY 142 
#define  IO_OPEN_CNX_ERROR_WRONG_DESTINATION 141 
#define  IO_OPEN_CNX_ERROR_ZONE_VIOLATION 140 
#define  IO_PORT_IN_RESET 139 
#define  IO_SUCCESS 138 
#define  IO_UNDERFLOW 137 
#define  IO_XFER_ERROR_ACK_NAK_TIMEOUT 136 
#define  IO_XFER_ERROR_BREAK 135 
#define  IO_XFER_ERROR_DMA 134 
#define  IO_XFER_ERROR_NAK_RECEIVED 133 
#define  IO_XFER_ERROR_PHY_NOT_READY 132 
#define  IO_XFER_ERROR_REJECTED_NCQ_MODE 131 
#define  IO_XFER_ERROR_SATA_LINK_TIMEOUT 130 
#define  IO_XFER_OPEN_RETRY_BACKOFF_THRESHOLD_REACHED 129 
#define  IO_XFER_OPEN_RETRY_TIMEOUT 128 
 int NCQ_ABORT_ALL_FLAG ; 
 int NCQ_READ_LOG_FLAG ; 
 int /*<<< orphan*/  PCI_DMA_FROMDEVICE ; 
 int /*<<< orphan*/  PM8001_FAIL_DBG (struct pm8001_hba_info*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  PM8001_IO_DBG (struct pm8001_hba_info*,int /*<<< orphan*/ ) ; 
 void* SAM_STAT_GOOD ; 
 void* SAS_ABORTED_TASK ; 
 void* SAS_DATA_UNDERRUN ; 
 void* SAS_DEV_NO_RESPONSE ; 
 void* SAS_INTERRUPTED ; 
 void* SAS_NAK_R_ERR ; 
 void* SAS_OPEN_REJECT ; 
 void* SAS_OPEN_TO ; 
 void* SAS_OREJ_BAD_DEST ; 
 void* SAS_OREJ_CONN_RATE ; 
 void* SAS_OREJ_EPROTO ; 
 void* SAS_OREJ_RSVD_CONT0 ; 
 void* SAS_OREJ_RSVD_RETRY ; 
 void* SAS_OREJ_UNKNOWN ; 
 void* SAS_OREJ_WRONG_DEST ; 
 void* SAS_PHY_DOWN ; 
 void* SAS_PROTO_RESPONSE ; 
 void* SAS_QUEUE_FULL ; 
 int SAS_STATUS_BUF_SIZE ; 
 int SAS_TASK_AT_INITIATOR ; 
 void* SAS_TASK_COMPLETE ; 
 int SAS_TASK_STATE_ABORTED ; 
 int SAS_TASK_STATE_DONE ; 
 int SAS_TASK_STATE_PENDING ; 
 void* SAS_TASK_UNDELIVERED ; 
 size_t le32_to_cpu (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mb () ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ *,size_t*,int) ; 
 int /*<<< orphan*/  pm8001_ccb_task_free (struct pm8001_hba_info*,struct sas_task*,struct pm8001_ccb_info*,size_t) ; 
 int /*<<< orphan*/  pm8001_handle_event (struct pm8001_hba_info*,struct pm8001_device*,int const) ; 
 int /*<<< orphan*/  pm8001_printk (char*,...) ; 
 int /*<<< orphan*/  pm8001_tag_free (struct pm8001_hba_info*,size_t) ; 
 int /*<<< orphan*/  pm80xx_send_abort_all (struct pm8001_hba_info*,struct pm8001_device*) ; 
 int /*<<< orphan*/  sas_free_task (struct sas_task*) ; 
 int /*<<< orphan*/  spin_lock_irq (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irq (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  stub1 (struct sas_task*) ; 
 int /*<<< orphan*/  stub2 (struct sas_task*) ; 
 int /*<<< orphan*/  stub3 (struct sas_task*) ; 
 int /*<<< orphan*/  stub4 (struct sas_task*) ; 
 int /*<<< orphan*/  stub5 (struct sas_task*) ; 
 int /*<<< orphan*/  stub6 (struct sas_task*) ; 
 int /*<<< orphan*/  stub7 (struct sas_task*) ; 
 scalar_t__ unlikely (int) ; 

__attribute__((used)) static void
mpi_sata_completion(struct pm8001_hba_info *pm8001_ha, void *piomb)
{
	struct sas_task *t;
	struct pm8001_ccb_info *ccb;
	u32 param;
	u32 status;
	u32 tag;
	struct sata_completion_resp *psataPayload;
	struct task_status_struct *ts;
	struct ata_task_resp *resp ;
	u32 *sata_resp;
	struct pm8001_device *pm8001_dev;
	unsigned long flags;

	psataPayload = (struct sata_completion_resp *)(piomb + 4);
	status = le32_to_cpu(psataPayload->status);
	tag = le32_to_cpu(psataPayload->tag);

	if (!tag) {
		PM8001_FAIL_DBG(pm8001_ha,
			pm8001_printk("tag null\n"));
		return;
	}
	ccb = &pm8001_ha->ccb_info[tag];
	param = le32_to_cpu(psataPayload->param);
	if (ccb) {
		t = ccb->task;
		pm8001_dev = ccb->device;
	} else {
		PM8001_FAIL_DBG(pm8001_ha,
			pm8001_printk("ccb null\n"));
		return;
	}

	if (t) {
		if (t->dev && (t->dev->lldd_dev))
			pm8001_dev = t->dev->lldd_dev;
	} else {
		PM8001_FAIL_DBG(pm8001_ha,
			pm8001_printk("task null\n"));
		return;
	}

	if ((pm8001_dev && !(pm8001_dev->id & NCQ_READ_LOG_FLAG))
		&& unlikely(!t || !t->lldd_task || !t->dev)) {
		PM8001_FAIL_DBG(pm8001_ha,
			pm8001_printk("task or dev null\n"));
		return;
	}

	ts = &t->task_status;
	if (!ts) {
		PM8001_FAIL_DBG(pm8001_ha,
			pm8001_printk("ts null\n"));
		return;
	}

	switch (status) {
	case IO_SUCCESS:
		PM8001_IO_DBG(pm8001_ha, pm8001_printk("IO_SUCCESS\n"));
		if (param == 0) {
			ts->resp = SAS_TASK_COMPLETE;
			ts->stat = SAM_STAT_GOOD;
			/* check if response is for SEND READ LOG */
			if (pm8001_dev &&
				(pm8001_dev->id & NCQ_READ_LOG_FLAG)) {
				/* set new bit for abort_all */
				pm8001_dev->id |= NCQ_ABORT_ALL_FLAG;
				/* clear bit for read log */
				pm8001_dev->id = pm8001_dev->id & 0x7FFFFFFF;
				pm80xx_send_abort_all(pm8001_ha, pm8001_dev);
				/* Free the tag */
				pm8001_tag_free(pm8001_ha, tag);
				sas_free_task(t);
				return;
			}
		} else {
			u8 len;
			ts->resp = SAS_TASK_COMPLETE;
			ts->stat = SAS_PROTO_RESPONSE;
			ts->residual = param;
			PM8001_IO_DBG(pm8001_ha,
				pm8001_printk("SAS_PROTO_RESPONSE len = %d\n",
				param));
			sata_resp = &psataPayload->sata_resp[0];
			resp = (struct ata_task_resp *)ts->buf;
			if (t->ata_task.dma_xfer == 0 &&
			t->data_dir == PCI_DMA_FROMDEVICE) {
				len = sizeof(struct pio_setup_fis);
				PM8001_IO_DBG(pm8001_ha,
				pm8001_printk("PIO read len = %d\n", len));
			} else if (t->ata_task.use_ncq) {
				len = sizeof(struct set_dev_bits_fis);
				PM8001_IO_DBG(pm8001_ha,
					pm8001_printk("FPDMA len = %d\n", len));
			} else {
				len = sizeof(struct dev_to_host_fis);
				PM8001_IO_DBG(pm8001_ha,
				pm8001_printk("other len = %d\n", len));
			}
			if (SAS_STATUS_BUF_SIZE >= sizeof(*resp)) {
				resp->frame_len = len;
				memcpy(&resp->ending_fis[0], sata_resp, len);
				ts->buf_valid_size = sizeof(*resp);
			} else
				PM8001_IO_DBG(pm8001_ha,
					pm8001_printk("response to large\n"));
		}
		if (pm8001_dev)
			pm8001_dev->running_req--;
		break;
	case IO_ABORTED:
		PM8001_IO_DBG(pm8001_ha,
			pm8001_printk("IO_ABORTED IOMB Tag\n"));
		ts->resp = SAS_TASK_COMPLETE;
		ts->stat = SAS_ABORTED_TASK;
		if (pm8001_dev)
			pm8001_dev->running_req--;
		break;
		/* following cases are to do cases */
	case IO_UNDERFLOW:
		/* SATA Completion with error */
		PM8001_IO_DBG(pm8001_ha,
			pm8001_printk("IO_UNDERFLOW param = %d\n", param));
		ts->resp = SAS_TASK_COMPLETE;
		ts->stat = SAS_DATA_UNDERRUN;
		ts->residual = param;
		if (pm8001_dev)
			pm8001_dev->running_req--;
		break;
	case IO_NO_DEVICE:
		PM8001_IO_DBG(pm8001_ha,
			pm8001_printk("IO_NO_DEVICE\n"));
		ts->resp = SAS_TASK_UNDELIVERED;
		ts->stat = SAS_PHY_DOWN;
		break;
	case IO_XFER_ERROR_BREAK:
		PM8001_IO_DBG(pm8001_ha,
			pm8001_printk("IO_XFER_ERROR_BREAK\n"));
		ts->resp = SAS_TASK_COMPLETE;
		ts->stat = SAS_INTERRUPTED;
		break;
	case IO_XFER_ERROR_PHY_NOT_READY:
		PM8001_IO_DBG(pm8001_ha,
			pm8001_printk("IO_XFER_ERROR_PHY_NOT_READY\n"));
		ts->resp = SAS_TASK_COMPLETE;
		ts->stat = SAS_OPEN_REJECT;
		ts->open_rej_reason = SAS_OREJ_RSVD_RETRY;
		break;
	case IO_OPEN_CNX_ERROR_PROTOCOL_NOT_SUPPORTED:
		PM8001_IO_DBG(pm8001_ha, pm8001_printk(
			"IO_OPEN_CNX_ERROR_PROTOCOL_NOT_SUPPORTED\n"));
		ts->resp = SAS_TASK_COMPLETE;
		ts->stat = SAS_OPEN_REJECT;
		ts->open_rej_reason = SAS_OREJ_EPROTO;
		break;
	case IO_OPEN_CNX_ERROR_ZONE_VIOLATION:
		PM8001_IO_DBG(pm8001_ha,
			pm8001_printk("IO_OPEN_CNX_ERROR_ZONE_VIOLATION\n"));
		ts->resp = SAS_TASK_COMPLETE;
		ts->stat = SAS_OPEN_REJECT;
		ts->open_rej_reason = SAS_OREJ_UNKNOWN;
		break;
	case IO_OPEN_CNX_ERROR_BREAK:
		PM8001_IO_DBG(pm8001_ha,
			pm8001_printk("IO_OPEN_CNX_ERROR_BREAK\n"));
		ts->resp = SAS_TASK_COMPLETE;
		ts->stat = SAS_OPEN_REJECT;
		ts->open_rej_reason = SAS_OREJ_RSVD_CONT0;
		break;
	case IO_OPEN_CNX_ERROR_IT_NEXUS_LOSS:
	case IO_XFER_OPEN_RETRY_BACKOFF_THRESHOLD_REACHED:
	case IO_OPEN_CNX_ERROR_IT_NEXUS_LOSS_OPEN_TMO:
	case IO_OPEN_CNX_ERROR_IT_NEXUS_LOSS_NO_DEST:
	case IO_OPEN_CNX_ERROR_IT_NEXUS_LOSS_OPEN_COLLIDE:
	case IO_OPEN_CNX_ERROR_IT_NEXUS_LOSS_PATHWAY_BLOCKED:
		PM8001_IO_DBG(pm8001_ha,
			pm8001_printk("IO_OPEN_CNX_ERROR_IT_NEXUS_LOSS\n"));
		ts->resp = SAS_TASK_COMPLETE;
		ts->stat = SAS_DEV_NO_RESPONSE;
		if (!t->uldd_task) {
			pm8001_handle_event(pm8001_ha,
				pm8001_dev,
				IO_OPEN_CNX_ERROR_IT_NEXUS_LOSS);
			ts->resp = SAS_TASK_UNDELIVERED;
			ts->stat = SAS_QUEUE_FULL;
			pm8001_ccb_task_free(pm8001_ha, t, ccb, tag);
			mb();/*in order to force CPU ordering*/
			spin_unlock_irq(&pm8001_ha->lock);
			t->task_done(t);
			spin_lock_irq(&pm8001_ha->lock);
			return;
		}
		break;
	case IO_OPEN_CNX_ERROR_BAD_DESTINATION:
		PM8001_IO_DBG(pm8001_ha,
			pm8001_printk("IO_OPEN_CNX_ERROR_BAD_DESTINATION\n"));
		ts->resp = SAS_TASK_UNDELIVERED;
		ts->stat = SAS_OPEN_REJECT;
		ts->open_rej_reason = SAS_OREJ_BAD_DEST;
		if (!t->uldd_task) {
			pm8001_handle_event(pm8001_ha,
				pm8001_dev,
				IO_OPEN_CNX_ERROR_IT_NEXUS_LOSS);
			ts->resp = SAS_TASK_UNDELIVERED;
			ts->stat = SAS_QUEUE_FULL;
			pm8001_ccb_task_free(pm8001_ha, t, ccb, tag);
			mb();/*ditto*/
			spin_unlock_irq(&pm8001_ha->lock);
			t->task_done(t);
			spin_lock_irq(&pm8001_ha->lock);
			return;
		}
		break;
	case IO_OPEN_CNX_ERROR_CONNECTION_RATE_NOT_SUPPORTED:
		PM8001_IO_DBG(pm8001_ha, pm8001_printk(
			"IO_OPEN_CNX_ERROR_CONNECTION_RATE_NOT_SUPPORTED\n"));
		ts->resp = SAS_TASK_COMPLETE;
		ts->stat = SAS_OPEN_REJECT;
		ts->open_rej_reason = SAS_OREJ_CONN_RATE;
		break;
	case IO_OPEN_CNX_ERROR_STP_RESOURCES_BUSY:
		PM8001_IO_DBG(pm8001_ha, pm8001_printk(
			"IO_OPEN_CNX_ERROR_STP_RESOURCES_BUSY\n"));
		ts->resp = SAS_TASK_COMPLETE;
		ts->stat = SAS_DEV_NO_RESPONSE;
		if (!t->uldd_task) {
			pm8001_handle_event(pm8001_ha,
				pm8001_dev,
				IO_OPEN_CNX_ERROR_STP_RESOURCES_BUSY);
			ts->resp = SAS_TASK_UNDELIVERED;
			ts->stat = SAS_QUEUE_FULL;
			pm8001_ccb_task_free(pm8001_ha, t, ccb, tag);
			mb();/* ditto*/
			spin_unlock_irq(&pm8001_ha->lock);
			t->task_done(t);
			spin_lock_irq(&pm8001_ha->lock);
			return;
		}
		break;
	case IO_OPEN_CNX_ERROR_WRONG_DESTINATION:
		PM8001_IO_DBG(pm8001_ha,
			pm8001_printk("IO_OPEN_CNX_ERROR_WRONG_DESTINATION\n"));
		ts->resp = SAS_TASK_COMPLETE;
		ts->stat = SAS_OPEN_REJECT;
		ts->open_rej_reason = SAS_OREJ_WRONG_DEST;
		break;
	case IO_XFER_ERROR_NAK_RECEIVED:
		PM8001_IO_DBG(pm8001_ha,
			pm8001_printk("IO_XFER_ERROR_NAK_RECEIVED\n"));
		ts->resp = SAS_TASK_COMPLETE;
		ts->stat = SAS_NAK_R_ERR;
		break;
	case IO_XFER_ERROR_ACK_NAK_TIMEOUT:
		PM8001_IO_DBG(pm8001_ha,
			pm8001_printk("IO_XFER_ERROR_ACK_NAK_TIMEOUT\n"));
		ts->resp = SAS_TASK_COMPLETE;
		ts->stat = SAS_NAK_R_ERR;
		break;
	case IO_XFER_ERROR_DMA:
		PM8001_IO_DBG(pm8001_ha,
			pm8001_printk("IO_XFER_ERROR_DMA\n"));
		ts->resp = SAS_TASK_COMPLETE;
		ts->stat = SAS_ABORTED_TASK;
		break;
	case IO_XFER_ERROR_SATA_LINK_TIMEOUT:
		PM8001_IO_DBG(pm8001_ha,
			pm8001_printk("IO_XFER_ERROR_SATA_LINK_TIMEOUT\n"));
		ts->resp = SAS_TASK_UNDELIVERED;
		ts->stat = SAS_DEV_NO_RESPONSE;
		break;
	case IO_XFER_ERROR_REJECTED_NCQ_MODE:
		PM8001_IO_DBG(pm8001_ha,
			pm8001_printk("IO_XFER_ERROR_REJECTED_NCQ_MODE\n"));
		ts->resp = SAS_TASK_COMPLETE;
		ts->stat = SAS_DATA_UNDERRUN;
		break;
	case IO_XFER_OPEN_RETRY_TIMEOUT:
		PM8001_IO_DBG(pm8001_ha,
			pm8001_printk("IO_XFER_OPEN_RETRY_TIMEOUT\n"));
		ts->resp = SAS_TASK_COMPLETE;
		ts->stat = SAS_OPEN_TO;
		break;
	case IO_PORT_IN_RESET:
		PM8001_IO_DBG(pm8001_ha,
			pm8001_printk("IO_PORT_IN_RESET\n"));
		ts->resp = SAS_TASK_COMPLETE;
		ts->stat = SAS_DEV_NO_RESPONSE;
		break;
	case IO_DS_NON_OPERATIONAL:
		PM8001_IO_DBG(pm8001_ha,
			pm8001_printk("IO_DS_NON_OPERATIONAL\n"));
		ts->resp = SAS_TASK_COMPLETE;
		ts->stat = SAS_DEV_NO_RESPONSE;
		if (!t->uldd_task) {
			pm8001_handle_event(pm8001_ha, pm8001_dev,
					IO_DS_NON_OPERATIONAL);
			ts->resp = SAS_TASK_UNDELIVERED;
			ts->stat = SAS_QUEUE_FULL;
			pm8001_ccb_task_free(pm8001_ha, t, ccb, tag);
			mb();/*ditto*/
			spin_unlock_irq(&pm8001_ha->lock);
			t->task_done(t);
			spin_lock_irq(&pm8001_ha->lock);
			return;
		}
		break;
	case IO_DS_IN_RECOVERY:
		PM8001_IO_DBG(pm8001_ha,
			pm8001_printk("IO_DS_IN_RECOVERY\n"));
		ts->resp = SAS_TASK_COMPLETE;
		ts->stat = SAS_DEV_NO_RESPONSE;
		break;
	case IO_DS_IN_ERROR:
		PM8001_IO_DBG(pm8001_ha,
			pm8001_printk("IO_DS_IN_ERROR\n"));
		ts->resp = SAS_TASK_COMPLETE;
		ts->stat = SAS_DEV_NO_RESPONSE;
		if (!t->uldd_task) {
			pm8001_handle_event(pm8001_ha, pm8001_dev,
					IO_DS_IN_ERROR);
			ts->resp = SAS_TASK_UNDELIVERED;
			ts->stat = SAS_QUEUE_FULL;
			pm8001_ccb_task_free(pm8001_ha, t, ccb, tag);
			mb();/*ditto*/
			spin_unlock_irq(&pm8001_ha->lock);
			t->task_done(t);
			spin_lock_irq(&pm8001_ha->lock);
			return;
		}
		break;
	case IO_OPEN_CNX_ERROR_HW_RESOURCE_BUSY:
		PM8001_IO_DBG(pm8001_ha,
			pm8001_printk("IO_OPEN_CNX_ERROR_HW_RESOURCE_BUSY\n"));
		ts->resp = SAS_TASK_COMPLETE;
		ts->stat = SAS_OPEN_REJECT;
		ts->open_rej_reason = SAS_OREJ_RSVD_RETRY;
	default:
		PM8001_IO_DBG(pm8001_ha,
			pm8001_printk("Unknown status 0x%x\n", status));
		/* not allowed case. Therefore, return failed status */
		ts->resp = SAS_TASK_COMPLETE;
		ts->stat = SAS_DEV_NO_RESPONSE;
		break;
	}
	spin_lock_irqsave(&t->task_state_lock, flags);
	t->task_state_flags &= ~SAS_TASK_STATE_PENDING;
	t->task_state_flags &= ~SAS_TASK_AT_INITIATOR;
	t->task_state_flags |= SAS_TASK_STATE_DONE;
	if (unlikely((t->task_state_flags & SAS_TASK_STATE_ABORTED))) {
		spin_unlock_irqrestore(&t->task_state_lock, flags);
		PM8001_FAIL_DBG(pm8001_ha,
			pm8001_printk("task 0x%p done with io_status 0x%x"
			" resp 0x%x stat 0x%x but aborted by upper layer!\n",
			t, status, ts->resp, ts->stat));
		pm8001_ccb_task_free(pm8001_ha, t, ccb, tag);
	} else if (t->uldd_task) {
		spin_unlock_irqrestore(&t->task_state_lock, flags);
		pm8001_ccb_task_free(pm8001_ha, t, ccb, tag);
		mb();/* ditto */
		spin_unlock_irq(&pm8001_ha->lock);
		t->task_done(t);
		spin_lock_irq(&pm8001_ha->lock);
	} else if (!t->uldd_task) {
		spin_unlock_irqrestore(&t->task_state_lock, flags);
		pm8001_ccb_task_free(pm8001_ha, t, ccb, tag);
		mb();/*ditto*/
		spin_unlock_irq(&pm8001_ha->lock);
		t->task_done(t);
		spin_lock_irq(&pm8001_ha->lock);
	}
}