/*
   Copyright (c) 2011, 2023, Oracle and/or its affiliates.

   This program is free software; you can redistribute it and/or modify
   it under the terms of the GNU General Public License, version 2.0,
   as published by the Free Software Foundation.

   This program is designed to work with certain software (including
   but not limited to OpenSSL) that is licensed under separate terms,
   as designated in a particular file or component or in included license
   documentation.  The authors of MySQL hereby grant you an additional
   permission to link the program and your derivative works with the
   separately licensed software that they have either included with
   the program or referenced in the documentation.

   This program is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
   GNU General Public License, version 2.0, for more details.

   You should have received a copy of the GNU General Public License
   along with this program; if not, write to the Free Software
   Foundation, Inc., 51 Franklin St, Fifth Floor, Boston, MA 02110-1301  USA
*/

#ifndef NDB_EVENT_DATA_H
#define NDB_EVENT_DATA_H

#include <my_global.h> // my_alloc.h
#include <my_alloc.h> // MEM_ROOT

#include <ndbapi/ndbapi_limits.h>

#include "ndb_bitmap.h"

class Ndb_event_data
{
public:
  Ndb_event_data(); // Not implemented
  Ndb_event_data(const Ndb_event_data&); // Not implemented
  Ndb_event_data(struct NDB_SHARE *the_share);

  ~Ndb_event_data();

  MEM_ROOT mem_root;
  struct TABLE *shadow_table;
  struct NDB_SHARE *share;
  union NdbValue *ndb_value[2];

  // Bitmap with all primary key columns, used for "minimal bitmap"
  MY_BITMAP *pk_bitmap;
  my_bitmap_map pk_bitbuf[(NDB_MAX_ATTRIBUTES_IN_TABLE +
                            8*sizeof(my_bitmap_map) - 1) /
                           (8*sizeof(my_bitmap_map))];

  // Bitmap with all primary key columns not being a character data type.
  // Note that char PK columns may compare-as-equal even if not being binary
  // identical. Thus they can not be eliminated from a "minimal bitmap".
  MY_BITMAP *pk_nonchar_bitmap;
  my_bitmap_map pk_nonchar_bitbuf[(NDB_MAX_ATTRIBUTES_IN_TABLE +
                                    8*sizeof(my_bitmap_map) - 1) /
                                   (8*sizeof(my_bitmap_map))];

  void print(const char* where, FILE* file) const;
  void init_pk_bitmap();
  void generate_minimal_bitmap(MY_BITMAP *before, MY_BITMAP *after);
};

#endif
