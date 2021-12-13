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
#include "Common.h"

#ifdef EPOLL
#include <sys/epoll.h>
#endif

class ConnectObj;

class Network : public IDisposable {
 public:
  void Dispose() override;

  SOCKET GetSocket() const { return _master_socket; }

 protected:
  static void SetSocketOpt(SOCKET socket);
  SOCKET CreateSocket();
  void CreateConnectObj(SOCKET socket);

#ifdef EPOLL
  void InitEpoll();
  void Epoll();
  void AddEvent(int epollfd, int fd, int flag);
  void ModifyEvent(int epollfd, int fd, int flag);
  void DeleteEvent(int epollfd, int fd);
#else
  bool Select();
#endif

 protected:
  SOCKET _master_socket;
  std::map<SOCKET, ConnectObj*> _connects;

#ifdef EPOLL
#define MAX_CLIENT 5120
#define MAX_EVENT  5120
  struct epoll_event _events[MAX_EVENT]; // events slot
  int _epfd; // epoll instance descriptor
  int _main_sock_event_idx;
#else
  fd_set _readfds, _writefds, _exceptfds;
#endif
};

#endif
