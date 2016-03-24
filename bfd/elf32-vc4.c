/* VC4-specific support for 32-bit ELF
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
   Foundation, Inc., 51 Franklin Street - Fifth Floor,
   Boston, MA 02110-1301, USA.  */

#include "sysdep.h"
#include "bfd.h"
#include "libbfd.h"
#include "elf-bfd.h"
#include "elf/vc4.h"
#include "bfd_stdint.h"

static void
vc4_info_to_howto_rela (bfd *abfd ATTRIBUTE_UNUSED, arelent *cache_ptr,
			Elf_Internal_Rela *dst);
static bfd_boolean
vc4_elf_relocate_section (bfd *output_bfd,
			  struct bfd_link_info *info, bfd *input_bfd,
			  asection *input_section, bfd_byte *contents,
			  Elf_Internal_Rela *relocs,
			  Elf_Internal_Sym *local_syms,
			  asection **local_sections);
static asection *
vc4_elf_gc_mark_hook (asection *sec, struct bfd_link_info *info,
		      Elf_Internal_Rela *rel, struct elf_link_hash_entry *h,
		      Elf_Internal_Sym *sym);
static reloc_howto_type *
vc4_reloc_name_lookup (bfd *abfd ATTRIBUTE_UNUSED, const char *r_name);
static reloc_howto_type *
vc4_reloc_type_lookup (bfd *abfd ATTRIBUTE_UNUSED,
		       bfd_reloc_code_real_type code);
static bfd_boolean
vc4_elf_check_relocs (bfd *abfd, struct bfd_link_info *info,
		      asection *sec, const Elf_Internal_Rela *relocs);

#define ELF_ARCH		bfd_arch_vc4
#define ELF_MACHINE_CODE	EM_VIDEOCORE4
#define ELF_MAXPAGESIZE		0x1000

#define TARGET_LITTLE_SYM       vc4_elf32_vec
#define TARGET_LITTLE_NAME	"elf32-vc4"

#define elf_info_to_howto			vc4_info_to_howto_rela
#define elf_info_to_howto_rel			NULL
#define elf_backend_relocate_section		vc4_elf_relocate_section
#define elf_backend_gc_mark_hook		vc4_elf_gc_mark_hook
#define elf_backend_check_relocs		vc4_elf_check_relocs
#define elf_backend_rela_normal			1

#define elf_backend_can_gc_sections		1

#define bfd_elf32_bfd_reloc_type_lookup		vc4_reloc_type_lookup
#define bfd_elf32_bfd_reloc_name_lookup		vc4_reloc_name_lookup

/*
#define bfd_elf32_bfd_set_private_flags		vc4_elf_set_private_flags
#define bfd_elf32_bfd_copy_private_bfd_data	vc4_elf_copy_private_bfd_data
#define bfd_elf32_bfd_merge_private_bfd_data	vc4_elf_merge_private_bfd_data
#define bfd_elf32_bfd_print_private_bfd_data	vc4_elf_print_private_bfd_data
#define elf_backend_post_process_headers	vc4_elf_post_process_headers
*/

#include "elf32-target.h"

/* Set the howto pointer for a VISIUM ELF reloc.  */

static void
vc4_info_to_howto_rela (bfd *abfd ATTRIBUTE_UNUSED,
			arelent *cache_ptr ATTRIBUTE_UNUSED,
			Elf_Internal_Rela *dst ATTRIBUTE_UNUSED)
{
}

/* Look through the relocs for a section during the first phase.
   Since we don't do .gots or .plts, we just need to consider the
   virtual table relocs for gc.  */

static bfd_boolean
vc4_elf_check_relocs (bfd *abfd ATTRIBUTE_UNUSED,
		      struct bfd_link_info *info ATTRIBUTE_UNUSED,
		      asection *sec ATTRIBUTE_UNUSED,
		      const Elf_Internal_Rela *relocs ATTRIBUTE_UNUSED)
{
	return FALSE;
}

/* Relocate a VC4 ELF section.  */

static bfd_boolean
vc4_elf_relocate_section (bfd *output_bfd ATTRIBUTE_UNUSED,
			  struct bfd_link_info *info ATTRIBUTE_UNUSED,
			  bfd *input_bfd ATTRIBUTE_UNUSED,
			  asection *input_section ATTRIBUTE_UNUSED,
			  bfd_byte *contents ATTRIBUTE_UNUSED,
			  Elf_Internal_Rela *relocs ATTRIBUTE_UNUSED,
			  Elf_Internal_Sym *local_syms ATTRIBUTE_UNUSED,
			  asection **local_sections ATTRIBUTE_UNUSED)
{
	return FALSE;
}


/* This function is called during section gc to discover the section a
   to which a particular relocation refers.  Return the section that
   should be marked against GC for a given relocation.  */

static asection *
vc4_elf_gc_mark_hook (asection *sec ATTRIBUTE_UNUSED,
		      struct bfd_link_info *info ATTRIBUTE_UNUSED,
		      Elf_Internal_Rela *rel ATTRIBUTE_UNUSED,
		      struct elf_link_hash_entry *h ATTRIBUTE_UNUSED,
		      Elf_Internal_Sym *sym ATTRIBUTE_UNUSED)
{
	return NULL;
}

static reloc_howto_type *
vc4_reloc_type_lookup (bfd *abfd ATTRIBUTE_UNUSED,
		       bfd_reloc_code_real_type code ATTRIBUTE_UNUSED)
{
	return NULL;
}

static reloc_howto_type *
vc4_reloc_name_lookup (bfd *abfd ATTRIBUTE_UNUSED,
		       const char *r_name ATTRIBUTE_UNUSED)
{
	return NULL;
}
