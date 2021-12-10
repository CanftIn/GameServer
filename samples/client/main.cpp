#include <string>
#include <memory>

#include "Client.h"
#include "utils/Log.h"

int main(int argc, char** argv) {
  InetAddress ia("127.0.0.1", 2333);

  std::unique_ptr<Client> clnt{ new Client(ia, 1) };
  if (!clnt->Connect()) {
    Log::Error("client connect failed.");
  } else {
    clnt->Update();
    clnt->DataHandler();
  
    if (clnt->IsCompleted()) {
      Log::Error("client is not completed.");
    }
  }

  return 0;
}