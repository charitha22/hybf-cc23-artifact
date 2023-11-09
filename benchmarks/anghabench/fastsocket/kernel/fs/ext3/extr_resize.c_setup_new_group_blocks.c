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
struct super_block {int dummy; } ;
struct ext3_sb_info {scalar_t__ s_groups_count; int s_itb_per_group; int /*<<< orphan*/  s_resize_lock; TYPE_2__** s_group_desc; TYPE_1__* s_es; } ;
struct ext3_new_group_data {scalar_t__ group; int block_bitmap; int inode_bitmap; int inode_table; int /*<<< orphan*/  blocks_count; } ;
struct buffer_head {int /*<<< orphan*/  b_data; int /*<<< orphan*/  b_size; } ;
typedef  struct buffer_head handle_t ;
typedef  int ext3_grpblk_t ;
typedef  int ext3_fsblk_t ;
struct TYPE_4__ {int /*<<< orphan*/  b_data; } ;
struct TYPE_3__ {int /*<<< orphan*/  s_reserved_gdt_blocks; } ;

/* Variables and functions */
 int EBUSY ; 
 int EIO ; 
 int /*<<< orphan*/  EXT3_BLOCKS_PER_GROUP (struct super_block*) ; 
 int /*<<< orphan*/  EXT3_INODES_PER_GROUP (struct super_block*) ; 
 int /*<<< orphan*/  EXT3_MAX_TRANS_DATA ; 
 struct ext3_sb_info* EXT3_SB (struct super_block*) ; 
 scalar_t__ IS_ERR (struct buffer_head*) ; 
 int PTR_ERR (struct buffer_head*) ; 
 struct buffer_head* bclean (struct buffer_head*,struct super_block*,int) ; 
 int /*<<< orphan*/  brelse (struct buffer_head*) ; 
 scalar_t__ ext3_bg_has_super (struct super_block*,scalar_t__) ; 
 unsigned long ext3_bg_num_gdb (struct super_block*,scalar_t__) ; 
 int /*<<< orphan*/  ext3_debug (char*,int,...) ; 
 int ext3_group_first_block_no (struct super_block*,scalar_t__) ; 
 int /*<<< orphan*/  ext3_journal_dirty_metadata (struct buffer_head*,struct buffer_head*) ; 
 int ext3_journal_get_write_access (struct buffer_head*,struct buffer_head*) ; 
 struct buffer_head* ext3_journal_start_sb (struct super_block*,int /*<<< orphan*/ ) ; 
 int ext3_journal_stop (struct buffer_head*) ; 
 int /*<<< orphan*/  ext3_set_bit (int,int /*<<< orphan*/ ) ; 
 int extend_or_restart_transaction (struct buffer_head*,int,struct buffer_head*) ; 
 int le16_to_cpu (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  lock_buffer (struct buffer_head*) ; 
 int /*<<< orphan*/  mark_bitmap_end (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 struct buffer_head* sb_getblk (struct super_block*,int) ; 
 int /*<<< orphan*/  set_buffer_uptodate (struct buffer_head*) ; 
 int /*<<< orphan*/  unlock_buffer (struct buffer_head*) ; 

__attribute__((used)) static int setup_new_group_blocks(struct super_block *sb,
				  struct ext3_new_group_data *input)
{
	struct ext3_sb_info *sbi = EXT3_SB(sb);
	ext3_fsblk_t start = ext3_group_first_block_no(sb, input->group);
	int reserved_gdb = ext3_bg_has_super(sb, input->group) ?
		le16_to_cpu(sbi->s_es->s_reserved_gdt_blocks) : 0;
	unsigned long gdblocks = ext3_bg_num_gdb(sb, input->group);
	struct buffer_head *bh;
	handle_t *handle;
	ext3_fsblk_t block;
	ext3_grpblk_t bit;
	int i;
	int err = 0, err2;

	/* This transaction may be extended/restarted along the way */
	handle = ext3_journal_start_sb(sb, EXT3_MAX_TRANS_DATA);

	if (IS_ERR(handle))
		return PTR_ERR(handle);

	mutex_lock(&sbi->s_resize_lock);
	if (input->group != sbi->s_groups_count) {
		err = -EBUSY;
		goto exit_journal;
	}

	if (IS_ERR(bh = bclean(handle, sb, input->block_bitmap))) {
		err = PTR_ERR(bh);
		goto exit_journal;
	}

	if (ext3_bg_has_super(sb, input->group)) {
		ext3_debug("mark backup superblock %#04lx (+0)\n", start);
		ext3_set_bit(0, bh->b_data);
	}

	/* Copy all of the GDT blocks into the backup in this group */
	for (i = 0, bit = 1, block = start + 1;
	     i < gdblocks; i++, block++, bit++) {
		struct buffer_head *gdb;

		ext3_debug("update backup group %#04lx (+%d)\n", block, bit);

		err = extend_or_restart_transaction(handle, 1, bh);
		if (err)
			goto exit_bh;

		gdb = sb_getblk(sb, block);
		if (!gdb) {
			err = -EIO;
			goto exit_bh;
		}
		if ((err = ext3_journal_get_write_access(handle, gdb))) {
			brelse(gdb);
			goto exit_bh;
		}
		lock_buffer(gdb);
		memcpy(gdb->b_data, sbi->s_group_desc[i]->b_data, gdb->b_size);
		set_buffer_uptodate(gdb);
		unlock_buffer(gdb);
		ext3_journal_dirty_metadata(handle, gdb);
		ext3_set_bit(bit, bh->b_data);
		brelse(gdb);
	}

	/* Zero out all of the reserved backup group descriptor table blocks */
	for (i = 0, bit = gdblocks + 1, block = start + bit;
	     i < reserved_gdb; i++, block++, bit++) {
		struct buffer_head *gdb;

		ext3_debug("clear reserved block %#04lx (+%d)\n", block, bit);

		err = extend_or_restart_transaction(handle, 1, bh);
		if (err)
			goto exit_bh;

		if (IS_ERR(gdb = bclean(handle, sb, block))) {
			err = PTR_ERR(bh);
			goto exit_bh;
		}
		ext3_journal_dirty_metadata(handle, gdb);
		ext3_set_bit(bit, bh->b_data);
		brelse(gdb);
	}
	ext3_debug("mark block bitmap %#04x (+%ld)\n", input->block_bitmap,
		   input->block_bitmap - start);
	ext3_set_bit(input->block_bitmap - start, bh->b_data);
	ext3_debug("mark inode bitmap %#04x (+%ld)\n", input->inode_bitmap,
		   input->inode_bitmap - start);
	ext3_set_bit(input->inode_bitmap - start, bh->b_data);

	/* Zero out all of the inode table blocks */
	for (i = 0, block = input->inode_table, bit = block - start;
	     i < sbi->s_itb_per_group; i++, bit++, block++) {
		struct buffer_head *it;

		ext3_debug("clear inode block %#04lx (+%d)\n", block, bit);

		err = extend_or_restart_transaction(handle, 1, bh);
		if (err)
			goto exit_bh;

		if (IS_ERR(it = bclean(handle, sb, block))) {
			err = PTR_ERR(it);
			goto exit_bh;
		}
		ext3_journal_dirty_metadata(handle, it);
		brelse(it);
		ext3_set_bit(bit, bh->b_data);
	}

	err = extend_or_restart_transaction(handle, 2, bh);
	if (err)
		goto exit_bh;

	mark_bitmap_end(input->blocks_count, EXT3_BLOCKS_PER_GROUP(sb),
			bh->b_data);
	ext3_journal_dirty_metadata(handle, bh);
	brelse(bh);

	/* Mark unused entries in inode bitmap used */
	ext3_debug("clear inode bitmap %#04x (+%ld)\n",
		   input->inode_bitmap, input->inode_bitmap - start);
	if (IS_ERR(bh = bclean(handle, sb, input->inode_bitmap))) {
		err = PTR_ERR(bh);
		goto exit_journal;
	}

	mark_bitmap_end(EXT3_INODES_PER_GROUP(sb), EXT3_BLOCKS_PER_GROUP(sb),
			bh->b_data);
	ext3_journal_dirty_metadata(handle, bh);
exit_bh:
	brelse(bh);

exit_journal:
	mutex_unlock(&sbi->s_resize_lock);
	if ((err2 = ext3_journal_stop(handle)) && !err)
		err = err2;

	return err;
}