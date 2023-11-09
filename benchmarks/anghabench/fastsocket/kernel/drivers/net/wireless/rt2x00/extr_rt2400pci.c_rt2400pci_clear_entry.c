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
typedef  int /*<<< orphan*/  u32 ;
struct skb_frame_desc {int skb_dma; } ;
struct queue_entry_priv_mmio {int /*<<< orphan*/  desc; } ;
struct queue_entry {TYPE_2__* skb; TYPE_1__* queue; struct queue_entry_priv_mmio* priv_data; } ;
struct TYPE_4__ {int len; } ;
struct TYPE_3__ {scalar_t__ qid; } ;

/* Variables and functions */
 scalar_t__ QID_RX ; 
 int /*<<< orphan*/  RXD_W0_OWNER_NIC ; 
 int /*<<< orphan*/  RXD_W1_BUFFER_ADDRESS ; 
 int /*<<< orphan*/  RXD_W2_BUFFER_LENGTH ; 
 int /*<<< orphan*/  TXD_W0_OWNER_NIC ; 
 int /*<<< orphan*/  TXD_W0_VALID ; 
 struct skb_frame_desc* get_skb_frame_desc (TYPE_2__*) ; 
 int /*<<< orphan*/  rt2x00_desc_read (int /*<<< orphan*/ ,int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  rt2x00_desc_write (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rt2x00_set_field32 (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void rt2400pci_clear_entry(struct queue_entry *entry)
{
	struct queue_entry_priv_mmio *entry_priv = entry->priv_data;
	struct skb_frame_desc *skbdesc = get_skb_frame_desc(entry->skb);
	u32 word;

	if (entry->queue->qid == QID_RX) {
		rt2x00_desc_read(entry_priv->desc, 2, &word);
		rt2x00_set_field32(&word, RXD_W2_BUFFER_LENGTH, entry->skb->len);
		rt2x00_desc_write(entry_priv->desc, 2, word);

		rt2x00_desc_read(entry_priv->desc, 1, &word);
		rt2x00_set_field32(&word, RXD_W1_BUFFER_ADDRESS, skbdesc->skb_dma);
		rt2x00_desc_write(entry_priv->desc, 1, word);

		rt2x00_desc_read(entry_priv->desc, 0, &word);
		rt2x00_set_field32(&word, RXD_W0_OWNER_NIC, 1);
		rt2x00_desc_write(entry_priv->desc, 0, word);
	} else {
		rt2x00_desc_read(entry_priv->desc, 0, &word);
		rt2x00_set_field32(&word, TXD_W0_VALID, 0);
		rt2x00_set_field32(&word, TXD_W0_OWNER_NIC, 0);
		rt2x00_desc_write(entry_priv->desc, 0, word);
	}
}