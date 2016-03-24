/* This is the machine dependent code of the VC4 Assembler.

   Copyright (C) 2005-2016 Free Software Foundation, Inc.

   This file is part of GAS, the GNU Assembler.

   GAS is free software; you can redistribute it and/or modify
   it under the terms of the GNU General Public License as published by
   the Free Software Foundation; either version 2, or (at your option)
   any later version.

   GAS is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
   GNU General Public License for more details.

   You should have received a copy of the GNU General Public License
   along with GAS; see the file COPYING.  If not, write to
   the Free Software Foundation, 59 Temple Place - Suite 330,
   Boston, MA 02111-1307, USA. */

#include "as.h"
#include "safe-ctype.h"
#include "subsegs.h"
#include "obstack.h"

#include "opcode/vc4.h"
#include "elf/vc4.h"
#include "dwarf2dbg.h"
#include "dw2gencfi.h"

/* This string holds the chars that always start a comment. If the
   pre-processor is disabled, these aren't very useful. The macro
   tc_comment_chars points to this.  */
const char vc4_comment_chars[] = "!;";

/* This array holds the chars that only start a comment at the beginning
   of a line.  If the line seems to have the form '# 123 filename' .line
   and .file directives will appear in the pre-processed output. Note that
   input_file.c hand checks for '#' at the beginning of the first line of
   the input file. This is because the compiler outputs #NO_APP at the
   beginning of its output. Also note that comments like this one will
   always work.  */
const char line_comment_chars[] = "#!;";
const char line_separator_chars[] = "";

/* Chars that can be used to separate mantissa from exponent in floating point
   numbers.  */
const char EXP_CHARS[] = "eE";

/* Chars that mean this number is a floating point constant, as in
   "0f12.456" or "0d1.2345e12".

   ...Also be aware that MAXIMUM_NUMBER_OF_CHARS_FOR_FLOAT may have to be
   changed in read.c. Ideally it shouldn't have to know about it at all,
   but nothing is ideal around here.  */
const char FLT_CHARS[] = "rRsSfFdDxXeE";

/* The size of a relocation record.  */
const int md_reloc_size = 8;

/* The parse options.  */
const char *md_shortopts = "m:";

struct option md_longopts[] =
{
  {NULL, no_argument, NULL, 0}
};

size_t md_longopts_size = sizeof (md_longopts);

struct vc4_option_table
{
  char *option;			/* Option name to match.  */
  char *help;			/* Help information.  */
  int *var;			/* Variable to change.  */
  int value;			/* To what to change it.  */
  char *deprecated;		/* If non-null, print this message. */
};


struct vc4_long_option_table
{
  const char *option;			/* Substring to match.  */
  const char *help;			/* Help information.  */
  int (*func) (char *subopt);	/* Function to decode sub-option.  */
  const char *deprecated;		/* If non-null, print this message.  */
};

static struct vc4_option_table vc4_opts[] =
{
  {NULL, NULL, NULL, 0, NULL}
};

static struct vc4_long_option_table vc4_long_opts[] =
{
  {NULL, NULL, NULL, NULL}
};

int
md_parse_option (int c, char *arg)
{
  struct vc4_option_table *opt;
  struct vc4_long_option_table *lopt;

  switch (c)
    {
    case 'a':
      /* Listing option.  Just ignore these, we don't support additional
         ones.  */
      return 0;

    default:
      for (opt = vc4_opts; opt->option != NULL; opt++)
	{
	  if (c == opt->option[0]
	      && ((arg == NULL && opt->option[1] == 0)
		  || strcmp (arg, opt->option + 1) == 0))
	    {
	      /* If the option is deprecated, tell the user.  */
	      if (opt->deprecated != NULL)
		as_tsktsk ("option `-%c%s' is deprecated: %s", c,
			   arg ? arg : "", opt->deprecated);

	      if (opt->var != NULL)
		*opt->var = opt->value;

	      return 1;
	    }
	}

      for (lopt = vc4_long_opts; lopt->option != NULL; lopt++)
	{
	  /* These options are expected to have an argument.  */
	  if (c == lopt->option[0]
	      && arg != NULL
	      && strncmp (arg, lopt->option + 1,
			  strlen (lopt->option + 1)) == 0)
	    {
	      /* If the option is deprecated, tell the user.  */
	      if (lopt->deprecated != NULL)
		as_tsktsk ("option `-%c%s' is deprecated: %s", c, arg,
			   lopt->deprecated);

	      /* Call the sup-option parser.  */
	      return lopt->func (arg + strlen (lopt->option) - 1);
	    }
	}

      return 0;
    }

  return 1;
}

void
md_show_usage (FILE * fp)
{
  struct vc4_option_table *opt;
  struct vc4_long_option_table *lopt;

  fprintf (fp, " VC4-specific assembler options:\n");

  for (opt = vc4_opts; opt->option != NULL; opt++)
    if (opt->help != NULL)
      fprintf (fp, "  -%-23s%s\n", opt->option, opt->help);

  for (lopt = vc4_long_opts; lopt->option != NULL; lopt++)
    if (lopt->help != NULL)
      fprintf (fp, "  -%s%s\n", lopt->option, lopt->help);

}

/* Align a section.  */
valueT
md_section_align (asection *seg, valueT addr)
{
  int align = bfd_get_section_alignment (stdoutput, seg);

  return ((addr + (1 << align) - 1) & -(1 << align));
}

void
md_number_to_chars (char *buf, valueT val, int n)
{
  number_to_chars_bigendian (buf, val, n);
}

symbolS *
md_undefined_symbol (char *name ATTRIBUTE_UNUSED)
{
  return 0;
}

/* This function is called when the assembler starts up. It is called
   after the options have been parsed and the output file has been
   opened.  */
void
md_begin (void)
{
}

/* This table describes all the machine specific pseudo-ops the assembler
   has to support. The fields are:

   1: Pseudo-op name without dot.
   2: Function to call to execute this pseudo-op.
   3: Integer arg to pass to the function.  */

const pseudo_typeS md_pseudo_table[] =
{
  {"skip", s_space, 0},
  {"align", s_align_bytes, 0},
  {"noopt", s_ignore, 0},
  {"optim", s_ignore, 0},
  {0, 0, 0}
};

char *
md_atof (int type ATTRIBUTE_UNUSED,
	 char *litP ATTRIBUTE_UNUSED,
	 int *sizeP ATTRIBUTE_UNUSED)
{
	return NULL;
}

/* This is the main function in this file. It takes a line of assembly language
   source code and assembles it. Note, labels and pseudo ops have already
   been removed, so too has leading white space. */
void
md_assemble (char *str0 ATTRIBUTE_UNUSED)
{
}

/* Convert a machine dependent frag.  */
void
md_convert_frag (bfd *abfd ATTRIBUTE_UNUSED,
		 segT sec ATTRIBUTE_UNUSED,
		 fragS *fragP ATTRIBUTE_UNUSED)
{
}

/* Apply a fixS to the frags, now that we know the value it ought to
   hold.  */
void
md_apply_fix (fixS * fixP ATTRIBUTE_UNUSED,
	      valueT * value ATTRIBUTE_UNUSED,
	      segT segment ATTRIBUTE_UNUSED)
{
}

/* Return the estimate of the size of a machine dependent frag
   before any relaxing is done.  It may also create any necessary
   relocations.  */
int
md_estimate_size_before_relax (fragS * fragP,
			       segT segment ATTRIBUTE_UNUSED)
{
  fragP->fr_var = 4;

  return 4;
}

/* The location from which a PC relative jump should be calculated,
   given a PC relative jump reloc.  */
long vc4_pcrel_from_section(struct fix * fixP, segT sec)
{
	if (fixP->fx_addsy != (symbolS *) NULL
	    && (!S_IS_DEFINED (fixP->fx_addsy)
		|| S_GET_SEGMENT (fixP->fx_addsy) != sec))
	{
		/* The symbol is undefined (or is defined but not in this section).
		   Let the linker figure it out.  */
		return 0;
	}

	/* Return the address of the instruction.  */
	return fixP->fx_where + fixP->fx_frag->fr_address;
}

/* Translate internal representation of relocation info to BFD target
   format.  */
arelent *
tc_gen_reloc (asection *section ATTRIBUTE_UNUSED,
	      fixS *fixp ATTRIBUTE_UNUSED)
{
	return NULL;
}
