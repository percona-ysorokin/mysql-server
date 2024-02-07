/*
   Copyright (c) 2004, 2024, Oracle and/or its affiliates.

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

#include <ndb_global.h>
#include <InputStream.hpp>
#include <OutputStream.hpp>
#include <SocketAuthenticator.hpp>

const char *SocketAuthenticator::error(int result) {
  return (result < AuthOk) ? "Socket Auth failure" : "Success";
}

int SocketAuthSimple::client_authenticate(const NdbSocket &sockfd) {
  SocketOutputStream s_output(sockfd);
  SocketInputStream s_input(sockfd);

  // Write username and password
  s_output.println("ndbd");
  s_output.println("ndbd passwd");

  char buf[16];

  // Read authentication result
  if (s_input.gets(buf, sizeof(buf)) == nullptr) return -1;
  buf[sizeof(buf) - 1] = 0;

  // Verify authentication result
  if (strncmp("ok", buf, 2) == 0) return 0;

  return -1;
}

int SocketAuthSimple::server_authenticate(const NdbSocket &sockfd) {
  SocketOutputStream s_output(sockfd);
  SocketInputStream s_input(sockfd);

  char buf[256];

  // Read username
  if (s_input.gets(buf, sizeof(buf)) == nullptr) return -1;
  buf[sizeof(buf) - 1] = 0;

  // Read password
  if (s_input.gets(buf, sizeof(buf)) == nullptr) return -1;
  buf[sizeof(buf) - 1] = 0;

  // Write authentication result
  s_output.println("ok");

  return AuthOk;
}
