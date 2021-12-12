#include <string>
#include <memory>

#include "Client.h"
#include "ClientThread.h"
#include "utils/Log.h"

int main(int argc, char** argv) {
  ClientThread* thread = new ClientThread(1);
  thread->Start();

  bool is_done = false;

  while (!is_done) {
    if (!thread->IsRun()) {
      thread->Dispose();
      delete thread;
      is_done = true;
    }
  }

  return 0;
}