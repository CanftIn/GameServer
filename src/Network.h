#ifndef __NETWORK_H__
#define __NETWORK_H__

#include <sys/types.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <netinet/in.h>
#include <netinet/tcp.h>
#include <unistd.h>
#include <errno.h>

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <iostream>
#include <map>

#include "Disposable.h"
#include "SocketsOps.h"

class ConnectObj;

class Network : public IDisposable {
 public:
  void Dispose() override;
  bool Select();

  SOCKET GetSocket() const { return _master_socket; }

 protected:
  static void SetSocketOpt(SOCKET socket);
  SOCKET CreateSocket();

 protected:
  SOCKET _master_socket;
  std::map<SOCKET, ConnectObj*> _connects;
  fd_set _readfds, _writefds, _exceptfds;
};

#endif
