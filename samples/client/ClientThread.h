#ifndef __CLIENTTHREAD_H__
#define __CLIENTTHREAD_H__

#include "Client.h"
#include "Thread.h"

#include <memory>

class Client;

class ClientThread : public Thread {
 public:
  explicit ClientThread(int msg_count);
  void Update() override;
  void Dispose() override;

 private:
  std::unique_ptr<Client> _client;
  int _msg_count;
};

#endif