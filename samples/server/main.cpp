#include "Server.h"

#include <signal.h>

bool is_run = true;

void stop(int signo) {
  is_run = false;
}

int main(int argc, char** argv) {
  ::signal(SIGINT, stop);

  InetAddress ia("127.0.0.1", 2333);

  Server server;
  if (!server.Listen(ia)) {
    return 1;
  }

  while (is_run) {
    if (!server.Update())
      break;

    server.DataHandler();
  }

  server.Dispose();
  
  return 0;
}