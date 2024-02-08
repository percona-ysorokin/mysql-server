# -*- cperl -*-
# Copyright (c) 2004, 2023, Oracle and/or its affiliates.
# Use is subject to license terms.
# 
# This program is free software; you can redistribute it and/or modify
# it under the terms of the GNU General Public License, version 2.0,
# as published by the Free Software Foundation.
#
# This program is designed to work with certain software (including
# but not limited to OpenSSL) that is licensed under separate terms,
# as designated in a particular file or component or in included license
# documentation.  The authors of MySQL hereby grant you an additional
# permission to link the program and your derivative works with the
# separately licensed software that they have either included with
# the program or referenced in the documentation.
#
# This program is distributed in the hope that it will be useful,
# but WITHOUT ANY WARRANTY; without even the implied warranty of
# MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
# GNU General Public License, version 2.0, for more details.
#
# You should have received a copy of the GNU General Public License
# along with this program; if not, write to the Free Software
# Foundation, Inc., 51 Franklin St, Fifth Floor, Boston, MA  02110-1301  USA

# This is a library file used by the Perl version of mysql-test-run,
# and is part of the translation of the Bourne shell script with the
# same name.

use strict;

sub mtr_match_prefix ($$);
sub mtr_match_extension ($$);
sub mtr_match_any_exact ($$);

##############################################################################
#
#  
#
##############################################################################

# Match a prefix and return what is after the prefix

sub mtr_match_prefix ($$) {
  my $string= shift;
  my $prefix= shift;

  if ( $string =~ /^\Q$prefix\E(.*)$/ ) # strncmp
  {
    return $1;
  }
  else
  {
    return undef;		# NULL
  }
}


# Match extension and return the name without extension

sub mtr_match_extension ($$) {
  my $file= shift;
  my $ext=  shift;

  if ( $file =~ /^(.*)\.\Q$ext\E$/ ) # strchr+strcmp or something
  {
    return $1;
  }
  else
  {
    return undef;                       # NULL
  }
}


# Match a substring anywere in a string

sub mtr_match_substring ($$) {
  my $string= shift;
  my $substring= shift;

  if ( $string =~ /(.*)\Q$substring\E(.*)$/ ) # strncmp
  {
    return $1;
  }
  else
  {
    return undef;		# NULL
  }
}


sub mtr_match_any_exact ($$) {
  my $string= shift;
  my $mlist=  shift;

  foreach my $m (@$mlist)
  {
    if ( $string eq $m )
    {
      return 1;
    }
  }
  return 0;
}

1;
