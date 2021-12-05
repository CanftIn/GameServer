#include "NetworkListen.h"

#include "ConnectObj.h"

bool NetworkListen::Listen(const InetAddress& ia) {
  _master_socket = CreateSocket();
  if (_master_socket == INVALID_SOCKET) {
    return false;
  }

  if (!sockets::bindOrDie(_master_socket, ia.getSockAddrInet())) {
    return false;
  }

  if (!sockets::listenOrDie(_master_socket)) {
    return false;
  }

  return true;
}

int NetworkListen::Accept() {
  struct sockaddr sockclnt;
  socklen_t sock_len = sizeof(sockclnt);

  int rs = 0;

  while (true) {
    SOCKET socket = ::accept(_master_socket, &sockclnt, &sock_len);
    if (socket == INVALID_SOCKET) {
      return rs;
    }

    SetSocketOpt(socket);

    ConnectObj* conn_obj = new ConnectObj(this, socket);
    _connects.insert(std::make_pair(socket, conn_obj));

    ++rs;
  }
}

bool NetworkListen::Update() {
  bool br = Select();

  if (FD_ISSET(_master_socket, &_readfds)) {
    Accept();
  }

  return br;
}