#pragma once

#include "Disposable.h"

#include <map>

#include <errno.h>
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#include <arpa/inet.h>
#include <netinet/in.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/tcp.h>

#define SOCKET int
#define INVALID_SOCKET -1

#define _sock_init()
#define _sock_nonblock(sockfd)                   \
  do {                                           \
    int flags = ::fcntl(sockfd, F_GETFL, 0);     \
    ::fcntl(sockfd, F_SETFL flags | O_NONBLOCK); \
  } while(0)

#define _sock_exit()
#define _sock_err() errno
#define _sock_close(sockfd) ::close(sockfd)
#define _sock_is_blocked() (errno == EAGAIN || errno == 0)


class ConnectObj;

class Network : public IDisposable {
 public:
  void Dispose() override;
  bool Select();

  SOCKET GetSocket() const { return _masterSocket; }

 protected:
  static void SetSocketOpt(SOCKET socket);
  SOCKET CreateSocket();

 protected:
  SOCKET _masterSocket{ INVALID_SOCKET };
  std::map<SOCKET, ConnectObj*> _connects;
  fd_set readfds, writefds, exceptfds;
};