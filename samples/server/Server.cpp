#include "Server.h"

#include <iostream>

#include "Common.h"
#include "Packet.h"
#include "ConnectObj.h"
#include "utils/Log.h"

Server::Server()
  : _accept_count(0),
    _send_count(0),
    _recv_count(0),
    _is_show(true)
{

}

bool Server::DataHandler() {
  for (auto it = _connects.begin(); it != _connects.end(); ++it) {
    ConnectObj* conn_obj = it->second;
    HandleOne(conn_obj);
  }

  if (_is_show) {
    _is_show = false;
    Log::Info("Accept: " + std::to_string(_accept_count) + "\trecv count: " \
      + std::to_string(_recv_count) + "\tsend count: " + std::to_string(_send_count));
  }

  return true;
}

void Server::HandleOne(ConnectObj* conn_obj) {
  while (conn_obj->HasRecvData()) {
    Packet* packet = conn_obj->GetRecvPacket();
    if (packet == nullptr)
      break;

    Proto::TestMsg proto_msg = packet->ParseProto<Proto::TestMsg>();
    Log::Info("recv msg_id: " + std::to_string(packet->GetMsgId()) + 
      ", msg: " + proto_msg.msg() + " idx: " + std::to_string(proto_msg.index()));
    conn_obj->SendPacket(packet);

    ++_recv_count;
    ++_send_count;
    _is_show = true;
  }
}

int Server::Accept() {
  int rs = NetworkListen::Accept();
  _accept_count += rs;
  _is_show = true;
  return rs;
}