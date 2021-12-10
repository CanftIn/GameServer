#include <iostream>

#include "Client.h"
#include "Packet.h"
#include "utils/Log.h"


void Client::DataHandler() {
  if (_is_completed) return ;

  if (!IsConnected()) return ;

  if (_idx < _msg_count) {
    if (_last_msg.empty()) {
      _last_msg = "this is a test msg.";
      Log::Info("send. size: " + std::to_string(_last_msg.length()) + " msg: " + _last_msg);

      Packet* packet = new Packet(1);
      packet->AddBuffer(_last_msg.c_str(), _last_msg.length());
      SendPacket(packet);
      delete packet;
    } else {
      if (HasRecvData()) {
        Packet* packet = GetRecvPacket();
        if (packet != nullptr) {
          const std::string msg(packet->GetBuffer(), packet->GetDataLength());
          Log::Info("recv. size: " + std::to_string(packet->GetDataLength()));

          if (msg != _last_msg) {
            Log::Error("Error!!!");
          }

          _last_msg = "";
          ++_idx;
          delete packet;
        }
      }
    }
  } else {
    _is_completed = true;
  }
}