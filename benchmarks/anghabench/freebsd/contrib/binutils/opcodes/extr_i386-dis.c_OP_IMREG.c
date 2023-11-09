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
 int DFLAG ; 
 char* INTERNAL_DISASSEMBLER_ERROR ; 
 int PREFIX_DATA ; 
 int REX_W ; 
 int /*<<< orphan*/  USED_REX (int) ; 
#define  ah_reg 159 
#define  al_reg 158 
#define  ax_reg 157 
#define  bh_reg 156 
#define  bl_reg 155 
#define  bp_reg 154 
#define  bx_reg 153 
#define  ch_reg 152 
#define  cl_reg 151 
#define  cs_reg 150 
#define  cx_reg 149 
#define  dh_reg 148 
#define  di_reg 147 
#define  dl_reg 146 
#define  ds_reg 145 
#define  dx_reg 144 
#define  eAX_reg 143 
#define  eBP_reg 142 
#define  eBX_reg 141 
#define  eCX_reg 140 
#define  eDI_reg 139 
#define  eDX_reg 138 
#define  eSI_reg 137 
#define  eSP_reg 136 
#define  es_reg 135 
#define  fs_reg 134 
#define  gs_reg 133 
#define  indir_dx_reg 132 
 int /*<<< orphan*/  intel_syntax ; 
 char** names16 ; 
 char** names32 ; 
 char** names64 ; 
 char** names8 ; 
 char** names8rex ; 
 char** names_seg ; 
 int /*<<< orphan*/  oappend (char const*) ; 
 int prefixes ; 
 int rex ; 
#define  si_reg 131 
#define  sp_reg 130 
#define  ss_reg 129 
 int used_prefixes ; 
#define  z_mode_ax_reg 128 

__attribute__((used)) static void
OP_IMREG (int code, int sizeflag)
{
  const char *s;

  switch (code)
    {
    case indir_dx_reg:
      if (intel_syntax)
	s = "dx";
      else
	s = "(%dx)";
      break;
    case ax_reg: case cx_reg: case dx_reg: case bx_reg:
    case sp_reg: case bp_reg: case si_reg: case di_reg:
      s = names16[code - ax_reg];
      break;
    case es_reg: case ss_reg: case cs_reg:
    case ds_reg: case fs_reg: case gs_reg:
      s = names_seg[code - es_reg];
      break;
    case al_reg: case ah_reg: case cl_reg: case ch_reg:
    case dl_reg: case dh_reg: case bl_reg: case bh_reg:
      USED_REX (0);
      if (rex)
	s = names8rex[code - al_reg];
      else
	s = names8[code - al_reg];
      break;
    case eAX_reg: case eCX_reg: case eDX_reg: case eBX_reg:
    case eSP_reg: case eBP_reg: case eSI_reg: case eDI_reg:
      USED_REX (REX_W);
      if (rex & REX_W)
	s = names64[code - eAX_reg];
      else if (sizeflag & DFLAG)
	s = names32[code - eAX_reg];
      else
	s = names16[code - eAX_reg];
      used_prefixes |= (prefixes & PREFIX_DATA);
      break;
    case z_mode_ax_reg:
      if ((rex & REX_W) || (sizeflag & DFLAG))
	s = *names32;
      else
	s = *names16;
      if (!(rex & REX_W))
	used_prefixes |= (prefixes & PREFIX_DATA);
      break;
    default:
      s = INTERNAL_DISASSEMBLER_ERROR;
      break;
    }
  oappend (s);
}