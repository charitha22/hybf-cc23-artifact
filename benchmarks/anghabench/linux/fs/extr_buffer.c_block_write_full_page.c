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
struct writeback_control {int dummy; } ;
struct page {scalar_t__ const index; TYPE_1__* mapping; } ;
struct inode {int dummy; } ;
typedef  scalar_t__ pgoff_t ;
typedef  int loff_t ;
typedef  int /*<<< orphan*/  get_block_t ;
struct TYPE_2__ {struct inode* host; } ;

/* Variables and functions */
 int PAGE_SHIFT ; 
 int PAGE_SIZE ; 
 int __block_write_full_page (struct inode* const,struct page*,int /*<<< orphan*/ *,struct writeback_control*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  do_invalidatepage (struct page*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  end_buffer_async_write ; 
 int i_size_read (struct inode* const) ; 
 int /*<<< orphan*/  unlock_page (struct page*) ; 
 int /*<<< orphan*/  zero_user_segment (struct page*,unsigned int,int) ; 

int block_write_full_page(struct page *page, get_block_t *get_block,
			struct writeback_control *wbc)
{
	struct inode * const inode = page->mapping->host;
	loff_t i_size = i_size_read(inode);
	const pgoff_t end_index = i_size >> PAGE_SHIFT;
	unsigned offset;

	/* Is the page fully inside i_size? */
	if (page->index < end_index)
		return __block_write_full_page(inode, page, get_block, wbc,
					       end_buffer_async_write);

	/* Is the page fully outside i_size? (truncate in progress) */
	offset = i_size & (PAGE_SIZE-1);
	if (page->index >= end_index+1 || !offset) {
		/*
		 * The page may have dirty, unmapped buffers.  For example,
		 * they may have been added in ext3_writepage().  Make them
		 * freeable here, so the page does not leak.
		 */
		do_invalidatepage(page, 0, PAGE_SIZE);
		unlock_page(page);
		return 0; /* don't care */
	}

	/*
	 * The page straddles i_size.  It must be zeroed out on each and every
	 * writepage invocation because it may be mmapped.  "A file is mapped
	 * in multiples of the page size.  For a file that is not a multiple of
	 * the  page size, the remaining memory is zeroed when mapped, and
	 * writes to that region are not written out to the file."
	 */
	zero_user_segment(page, offset, PAGE_SIZE);
	return __block_write_full_page(inode, page, get_block, wbc,
							end_buffer_async_write);
}