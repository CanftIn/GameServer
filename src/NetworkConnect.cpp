#include "NetworkConnect.h"
#include "SocketsOps.h"
#include "ConnectObj.h"
#include "utils/Log.h"

bool NetworkConnect::Connect() {
  _master_socket = CreateSocket();
  if (_master_socket == INVALID_SOCKET) {
    return false;
  }

  if (sockets::connect(_master_socket, _ia.getSockAddrInet())) {
    ConnectObj* conn_obj = new ConnectObj(this, _master_socket);
    _connects.insert(std::make_pair(_master_socket, conn_obj));
  }

#ifdef EPOLL
  Log::Info("epoll model");
  InitEpoll();
#else
  Log::Info("select model");
#endif

  return true;
}

void NetworkConnect::TryCreateConnectObj() {
  int opt_val = -1;
  socklen_t opt_len = sizeof(opt_val);
  const int rs = ::getsockopt(_master_socket, SOL_SOCKET, SO_ERROR, (char*)(&opt_val), &opt_len);
  if (rs == 0 && opt_val == 0) {
    CreateConnectObj(_master_socket);
  } else {
    Log::Error("connect failed. socket: " + std::to_string(_master_socket) + " reconnect.");

    Dispose();
  }
}

#ifdef EPOLL

void NetworkConnect::Update() {
  if (_master_socket == INVALID_SOCKET) {
    if (!Connect()) return;

    Log::Info("reconnect socket: " + std::to_string(_master_socket));
  }
  
  Epoll();

  if (IsConnected()) return;

  if (_main_sock_event_idx >= 0) {
    int fd = _events[_main_sock_event_idx].data.fd;
    if (fd != _master_socket) return;

    if (_events[_main_sock_event_idx].events & EPOLLIN ||
        _events[_main_sock_event_idx].events & EPOLLOUT)
    {
      TryCreateConnectObj();
    }
  }
}

#else

void NetworkConnect::Update() {
  if (_master_socket == INVALID_SOCKET) {
    if (!Connect()) return;

    Log::Info("reconnect socket: " + std::to_string(_master_socket));
  }
  
  Select();

  if (!IsConnected()) {
    if (FD_ISSET(_master_socket, &_exceptfds)) {
      Log::Error("connect except. socket: " + std::to_string(_master_socket) + " reconnect.");

      Dispose();
    }

    if (FD_ISSET(_master_socket, &_readfds) || FD_ISSET(_master_socket, &_writefds)) {
      TryCreateConnectObj();
    }
  }
}

#endif

bool NetworkConnect::HasRecvData() {
  int size = _connects.size();
  if (size <= 0) return false;

  if (size != 1) {
    Log::Error("NetworkConnector has two connect!");
    return false;
  }

  ConnectObj* conn_obj = GetConnectObj();
  if (conn_obj == nullptr) return false;

  return conn_obj->HasRecvData();
}

Packet* NetworkConnect::GetRecvPacket() {
  ConnectObj* conn_obj = GetConnectObj();
  if (conn_obj == nullptr) return nullptr;

  return conn_obj->GetRecvPacket();
}

void NetworkConnect::SendPacket(Packet* packet) {
  ConnectObj* conn_obj = GetConnectObj();
  if (conn_obj == nullptr) return;

  conn_obj->SendPacket(packet);
}

bool NetworkConnect::IsConnected() const {
  return _connects.size() > 0;
}

ConnectObj* NetworkConnect::GetConnectObj() {
  auto it = _connects.find(_master_socket);
  if (it == _connects.end()) {
    Log::Error("NetworkConnect connect == nullptr");
    return nullptr;
  }
  return it->second;
}