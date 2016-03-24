/* BFD library support routines for the VC4 architecture.
   Copyright (C) 1999-2016 Free Software Foundation, Inc.

   This file is part of BFD, the Binary File Descriptor library.

   This program is free software; you can redistribute it and/or modify
   it under the terms of the GNU General Public License as published by
   the Free Software Foundation; either version 3 of the License, or
   (at your option) any later version.

   This program is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
   GNU General Public License for more details.

   You should have received a copy of the GNU General Public License
   along with this program; if not, write to the Free Software
   Foundation, Inc., 51 Franklin Street - Fifth Floor, Boston,
   MA 02110-1301, USA.  */

#include "sysdep.h"
#include "bfd.h"
#include "libbfd.h"

#define N(bits_word, bits_addr, align, machine, print, default, next)	\
{									\
	bits_word,	       	/* bits in a word.  */			\
	bits_addr,		/* bits in an address.  */		\
	8,			/* 8 bits in a byte.  */		\
	bfd_arch_vc4,							\
	machine,		/* Machine number.  */			\
	"vc4",			/* Architecture name.   */		\
	print,			/* Printable name.  */			\
	align,			/* Section align power.  */		\
	default,		/* Is this the default ?  */		\
	bfd_default_compatible,						\
	bfd_default_scan,						\
	bfd_arch_default_fill,						\
	next								\
}

const bfd_arch_info_type bfd_vc4_arch[] =
{
	/* the main CPU */
	N (32, 32, 2, bfd_mach_vc4, "vc4", TRUE, & bfd_vc4_arch[1]),
	N (32, 32, 4, bfd_mach_vc4qpu, "vc4-qpu", FALSE, 0)
};
