/* Copyright (c) 2013-2018 the Civetweb developers
 * Copyright (c) 2013 No Face Press, LLC
 * License http://opensource.org/licenses/mit-license.php MIT License
 */

 // Simple example program on how to use Embedded C++ interface.

#include "CivetServer.h"
#include <cstring>
#include <vector>

#ifdef _WIN32
#include <windows.h>
#else
#include <unistd.h>
#endif

#define DOCUMENT_ROOT "./website"
#define PORT "80"
#define EXAMPLE_URI "/example"
#define EXIT_URI "/exit"




/* Exit flag for main loop */
volatile bool exitNow = false;


class ExitHandler : public CivetHandler
{
public:
   bool
	  handleGet(CivetServer* server, struct mg_connection* conn)
   {
	  mg_printf(conn,
		 "HTTP/1.1 200 OK\r\nContent-Type: "
		 "text/plain\r\nConnection: close\r\n\r\n");
	  mg_printf(conn, "Bye!\n");
	  exitNow = true;
	  return true;
   }
};

int
main(int argc, char* argv[])
{
   mg_init_library(0);

   const char* options[] = {
	   "document_root", DOCUMENT_ROOT, "listening_ports", PORT, 0 };

   std::vector<std::string> cpp_options;
   for (int i = 0; i < (sizeof(options) / sizeof(options[0]) - 1); i++) {
	  cpp_options.push_back(options[i]);
   }

   CivetServer server(cpp_options);

   printf("Run example at http://localhost:%s%s\n", PORT, EXAMPLE_URI);
   printf("Exit at http://localhost:%s%s\n", PORT, EXIT_URI);

   while (!exitNow) {
#ifdef _WIN32
	  Sleep(1000);
#else
	  sleep(1);
#endif
   }

   printf("Bye!\n");
   mg_exit_library();

   return 0;
}