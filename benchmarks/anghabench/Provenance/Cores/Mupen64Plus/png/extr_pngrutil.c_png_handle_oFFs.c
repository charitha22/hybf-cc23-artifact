#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_12__   TYPE_2__ ;
typedef  struct TYPE_11__   TYPE_1__ ;

/* Type definitions */
typedef  int png_uint_32 ;
typedef  TYPE_1__* png_structrp ;
typedef  int /*<<< orphan*/  png_int_32 ;
typedef  TYPE_2__* png_inforp ;
typedef  int png_byte ;
struct TYPE_12__ {int valid; } ;
struct TYPE_11__ {int mode; } ;

/* Variables and functions */
 int PNG_HAVE_IDAT ; 
 int PNG_HAVE_IHDR ; 
 int PNG_INFO_oFFs ; 
 int /*<<< orphan*/  png_chunk_benign_error (TYPE_1__*,char*) ; 
 int /*<<< orphan*/  png_chunk_error (TYPE_1__*,char*) ; 
 scalar_t__ png_crc_finish (TYPE_1__*,int) ; 
 int /*<<< orphan*/  png_crc_read (TYPE_1__*,int*,int) ; 
 int /*<<< orphan*/  png_debug (int,char*) ; 
 int /*<<< orphan*/  png_get_int_32 (int*) ; 
 int /*<<< orphan*/  png_set_oFFs (TYPE_1__*,TYPE_2__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 

void /* PRIVATE */
png_handle_oFFs(png_structrp png_ptr, png_inforp info_ptr, png_uint_32 length)
{
   png_byte buf[9];
   png_int_32 offset_x, offset_y;
   int unit_type;

   png_debug(1, "in png_handle_oFFs");

   if ((png_ptr->mode & PNG_HAVE_IHDR) == 0)
      png_chunk_error(png_ptr, "missing IHDR");

   else if ((png_ptr->mode & PNG_HAVE_IDAT) != 0)
   {
      png_crc_finish(png_ptr, length);
      png_chunk_benign_error(png_ptr, "out of place");
      return;
   }

   else if (info_ptr != NULL && (info_ptr->valid & PNG_INFO_oFFs) != 0)
   {
      png_crc_finish(png_ptr, length);
      png_chunk_benign_error(png_ptr, "duplicate");
      return;
   }

   if (length != 9)
   {
      png_crc_finish(png_ptr, length);
      png_chunk_benign_error(png_ptr, "invalid");
      return;
   }

   png_crc_read(png_ptr, buf, 9);

   if (png_crc_finish(png_ptr, 0) != 0)
      return;

   offset_x = png_get_int_32(buf);
   offset_y = png_get_int_32(buf + 4);
   unit_type = buf[8];
   png_set_oFFs(png_ptr, info_ptr, offset_x, offset_y, unit_type);
}