/* tc-vc4.h -- Header file for tc-vc4.c.
   Copyright 2012 Free Software Foundation, Inc.

   This file is part of GAS, the GNU Assembler.

   GAS is free software; you can redistribute it and/or modify
   it under the terms of the GNU General Public License as published by
   the Free Software Foundation; either version 3, or (at your option)
   any later version.

   GAS is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
   GNU General Public License for more details.

   You should have received a copy of the GNU General Public License
   along with GAS; see the file COPYING.  If not, write to
   the Free Software Foundation, 51 Franklin Street - Fifth Floor,
   Boston, MA 02110-1301, USA.  */

#include <inttypes.h>

#define TC_VC4
#define TARGET_ARCH		bfd_arch_vc4

#define TARGET_FORMAT		"elf32-vc4"
#define TARGET_BYTES_BIG_ENDIAN	0

extern const char vc4_comment_chars [];
#define tc_comment_chars 	vc4_comment_chars

#define LOCAL_LABELS_FB 	1

#define DIFF_EXPR_OK    	1

#define WORKING_DOT_WORD

#define MD_APPLY_SYM_VALUE(FIX)	0

#define md_operand(x)
#define MD_PCREL_FROM_SECTION(FIXP, SEC) vc4_pcrel_from_section (FIXP, SEC)
extern long vc4_pcrel_from_section (struct fix *, segT);
