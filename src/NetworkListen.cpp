#include "NetworkListen.h"

#include "ConnectObj.h"
#include "utils/Log.h"

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

#ifdef EPOLL
  Log::Info("epoll model");
  InitEpoll();
#else
  Log::Info("select model");
#endif

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

    CreateConnectObj(socket);

    ++rs;
  }
}

#ifndef EPOLL

void NetworkListen::Update() {
  Select();

  if (FD_ISSET(_master_socket, &_readfds)) {
    Accept();
  }
}

#else

void NetworkListen::Update() {
  Epoll();

  if (_main_sock_event_idx >= 0) {
    Accept();
  }
}

#endif
