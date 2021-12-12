#include "Network.h"
#include "ConnectObj.h"

#include "utils/Log.h"

void Network::Dispose() {
  for (auto it = _connects.begin(); it != _connects.end(); ++it) {
    it->second->Dispose();
    delete it->second;
  }
  _connects.clear();

  //sockets::close(_master_socket);
  _master_socket = -1;
}

void Network::SetSocketOpt(SOCKET socket) {
  bool is_reuse = true;
  setsockopt(socket, SOL_SOCKET, SO_REUSEADDR, (void *)&is_reuse, sizeof(is_reuse));

  int timeout = 3000;
  setsockopt(socket, SOL_SOCKET, SO_SNDTIMEO, (void *)&timeout, sizeof(timeout));
  setsockopt(socket, SOL_SOCKET, SO_RCVTIMEO, (void *)&timeout, sizeof(timeout));

  int keepAlive = 1;
  socklen_t optlen = sizeof(keepAlive);

  int keepIdle = 60 * 2;	// 在socket 没有交互后 多久 开始发送侦测包
  int keepInterval = 10;	// 多次发送侦测包之间的间隔
  int keepCount = 5;		// 侦测包个数

  setsockopt(socket, SOL_SOCKET, SO_KEEPALIVE, (void *)&keepAlive, optlen);
  if (getsockopt(socket, SOL_SOCKET, SO_KEEPALIVE, &keepAlive, &optlen) < 0)
  {
    std::cout << "getsockopt SO_KEEPALIVE failed." << std::endl;
  }

  setsockopt(socket, SOL_TCP, TCP_KEEPIDLE, (void *)&keepIdle, optlen);
  if (getsockopt(socket, SOL_TCP, TCP_KEEPIDLE, &keepIdle, &optlen) < 0)
  {
    std::cout << "getsockopt TCP_KEEPIDLE failed." << std::endl;
  }

  setsockopt(socket, SOL_TCP, TCP_KEEPINTVL, (void *)&keepInterval, optlen);
  setsockopt(socket, SOL_TCP, TCP_KEEPCNT, (void *)&keepCount, optlen);

  sockets::setNonBlockAndCloseOnExec(socket);
}

SOCKET Network::CreateSocket() {
  SOCKET socket = ::socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
  if (socket == INVALID_SOCKET)
  {
    Log::Error("::socket failed. err:" + std::to_string(errno));
    return socket;
  }

  SetSocketOpt(socket);
  return socket;
}

bool Network::Select() {
  FD_ZERO(&_readfds);
  FD_ZERO(&_writefds);
  FD_ZERO(&_exceptfds);

  FD_SET(_master_socket, &_readfds);
  FD_SET(_master_socket, &_writefds);
  FD_SET(_master_socket, &_exceptfds);

  SOCKET fd_max = _master_socket;

  for (auto it = _connects.begin(); it != _connects.end(); ++it) {
    if (it->first > fd_max) {
      fd_max = it->first;
    }

    FD_SET(it->first, &_readfds);
    FD_SET(it->first, &_exceptfds);

    if (it->second->HasSendData()) {
      FD_SET(it->first, &_writefds);
    } else {
      if (_master_socket == it->first) {
        FD_CLR(_master_socket, &_writefds);
      }
    }
  }

  struct timeval timeout;
  timeout.tv_sec = 0;
  timeout.tv_usec = 50 * 1000;

  int nfds = ::select(fd_max + 1, &_readfds, &_writefds, &_exceptfds, &timeout);
  if (nfds <= 0) {
    return true;
  }

  for (auto it = _connects.begin(); it != _connects.end(); ++it) {
    if (FD_ISSET(it->first, &_exceptfds)) {
      Log::Error("socket except! socket: " + std::to_string(it->first));
      it->second->Dispose();
      delete it->second;
      it = _connects.erase(it);
      continue;
    }

    if (FD_ISSET(it->first, &_readfds)) {
      if (!it->second->Recv()) {
        it->second->Dispose();
        delete it->second;
        it = _connects.erase(it);
        continue;
      }
    }

    if (FD_ISSET(it->first, &_writefds)) {
      if (!it->second->Send()) {
        it->second->Dispose();
        delete it->second;
        it = _connects.erase(it);
        continue;
      }
    }
  }
  
  return true;
}