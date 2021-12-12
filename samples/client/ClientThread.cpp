#include "ClientThread.h"
#include "Client.h"

#include "utils/Log.h"

ClientThread::ClientThread(int msg_count) {
  _msg_count = msg_count;
  _client = nullptr;
}

void ClientThread::Update() {
  if (_client == nullptr) {
    InetAddress ia("127.0.0.1", 2333);

    _client = std::unique_ptr<Client>(new Client(ia, _msg_count));
    if (!_client->Connect()) {
      Log::Error("client connect failed.");
    } 

  } else {
    _client->Update();
    _client->DataHandler();
  
    if (_client->IsCompleted()) {
      Thread::Stop();
    }
  }

  std::this_thread::sleep_for(std::chrono::milliseconds(10));
}

void ClientThread::Dispose() {
  if (_client != nullptr) {
    _client->Dispose();
  }

  Thread::Dispose();
}