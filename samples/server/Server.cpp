#include "Server.h"

#include <iostream>

#include "Packet.h"
#include "ConnectObj.h"

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
    std::cout << "Accept: " + std::to_string(_accept_count) + "\trecv count: " \
      + std::to_string(_recv_count) + "\tsend count: " + std::to_string(_send_count) << std::endl;
  }

  return true;
}

void Server::HandleOne(ConnectObj* conn_obj) {
  while (conn_obj->HasRecvData()) {
    Packet* packet = conn_obj->GetRecvPacket();
    if (packet == nullptr)
      break;
  

    std::string msg(packet->GetBuffer(), packet->GetDataLength());
    std::cout << "recv size: " + std::to_string(msg.length()) + " msg: " + msg << std::endl;
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