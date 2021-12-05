#include "NetworkConnect.h"
#include "SocketsOps.h"
#include "ConnectObj.h"
#include "utils/Log.h"

bool NetworkConnect::Connect(const InetAddress& ia) {
  _master_socket = CreateSocket();
  if (_master_socket == INVALID_SOCKET) {
    return false;
  }

  if (sockets::connect(_master_socket, ia.getSockAddrInet())) {
    ConnectObj* conn_obj = new ConnectObj(this, _master_socket);
    _connects.insert(std::make_pair(_master_socket, conn_obj));
  }

  return true;
}

bool NetworkConnect::Update() {
  const bool br = Select();

  if (!IsConnected()) {
    if (FD_ISSET(_master_socket, &_exceptfds)) {
      Log::Error("connect except. socket: " + std::to_string(_master_socket) + " reconnect.");

      Dispose();
      Connect(_ia);
      return br;
    }

    if (FD_ISSET(_master_socket, &_readfds) || FD_ISSET(_master_socket, &_writefds)) {
      int opt_val = -1;
      socklen_t opt_len = sizeof(opt_val);
      const int rs = ::getsockopt(_master_socket, SOL_SOCKET, SO_ERROR, (char*)(&opt_val), &opt_len);
      if (rs == 0 && opt_val == 0) {
        ConnectObj* conn_obj = new ConnectObj(this, _master_socket);
        _connects.insert(std::make_pair(_master_socket, conn_obj));
      } else {
        Log::Error("connect failed. socket: " + std::to_string(_master_socket) + " reconnect.");

        Dispose();
        Connect(_ia);
      }
    }
  }

  return br;
}

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