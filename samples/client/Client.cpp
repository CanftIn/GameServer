#include "Client.h"

#include "Common.h"
#include "Packet.h"
#include "utils/Log.h"


void Client::DataHandler() {
  if (_is_completed) return ;

  if (!IsConnected()) return ;

  if (_idx < _msg_count) {
    if (_last_msg.empty()) {
      _last_msg = "this is a test msg.";

      Proto::TestMsg proto_msg;
      proto_msg.set_index(_idx);
      proto_msg.set_msg(_last_msg.c_str());
      Log::Info("send. size: " + std::to_string(_last_msg.length()) + " msg: " + _last_msg);

      Packet packet(Proto::MsgId::SendData);
      packet.SerializeBuffer(proto_msg);
      SendPacket(&packet);
    } else {
      if (HasRecvData()) {
        Packet* packet = GetRecvPacket();
        if (packet != nullptr) {
          Proto::TestMsg proto_msg = packet->ParseProto<Proto::TestMsg>();
          Log::Info("recv. size: " + proto_msg.msg());

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