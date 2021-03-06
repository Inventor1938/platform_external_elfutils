/* Check whether DIE has specific attribute, integrating DW_AT_abstract_origin.
   Copyright (C) 2005 Red Hat, Inc.
   This file is part of elfutils.

   This file is free software; you can redistribute it and/or modify
   it under the terms of either

     * the GNU Lesser General Public License as published by the Free
       Software Foundation; either version 3 of the License, or (at
       your option) any later version

   or

     * the GNU General Public License as published by the Free
       Software Foundation; either version 2 of the License, or (at
       your option) any later version

   or both in parallel, as here.

   elfutils is distributed in the hope that it will be useful, but
   WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
   General Public License for more details.

   You should have received copies of the GNU General Public License and
   the GNU Lesser General Public License along with this program.  If
   not, see <http://www.gnu.org/licenses/>.  */

#ifdef HAVE_CONFIG_H
# include <config.h>
#endif

#include <dwarf.h>
#include "libdwP.h"

int
dwarf_hasattr_integrate (Dwarf_Die *die, unsigned int search_name)
{
  Dwarf_Die die_mem;

  do
    {
      if (INTUSE(dwarf_hasattr) (die, search_name))
	return 1;

      Dwarf_Attribute attr_mem;
      Dwarf_Attribute *attr = INTUSE(dwarf_attr) (die, DW_AT_abstract_origin,
						  &attr_mem);
      if (attr == NULL)
	attr = INTUSE(dwarf_attr) (die, DW_AT_specification, &attr_mem);
      if (attr == NULL)
	break;

      die = INTUSE(dwarf_formref_die) (attr, &die_mem);
    }
  while (die != NULL);

  return 0;
}
