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

/* Variables and functions */
 int /*<<< orphan*/  assem_debug (char*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  output_byte (int) ; 
 int /*<<< orphan*/  output_modrm (int,int,int) ; 
 int /*<<< orphan*/  output_rex (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  output_w32 (int) ; 
 int /*<<< orphan*/ * regname ; 

void emit_cmpimm(int rs,int imm)
{
  assem_debug("cmp $%d,%%%s\n",imm,regname[rs]);
  if(rs>=8) output_rex(0,0,0,rs>>3);
  if(imm<128&&imm>=-128) {
    output_byte(0x83);
    output_modrm(3,rs&7,7);
    output_byte(imm);
  }
  else
  {
    output_byte(0x81);
    output_modrm(3,rs&7,7);
    output_w32(imm);
  }
}