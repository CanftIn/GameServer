#ifndef __PACKET_H__
#define __PACKET_H__

#include "BaseBuffer.h"

#pragma pack(push)
#pragma pack(1)

struct PacketHead {
  unsigned short MsgId;
};

#pragma pack(pop)

#define DEFAULT_PACKET_BUFFER_SIZE 1024 * 10

class Packet : public Buffer {
 public:
  Packet();
  Packet(const int msg_id);
  ~Packet();

  template <class Proto>
  Proto ParseProto() {
    Proto proto;
    proto.ParsePartialFromArray(GetBuffer(), GetDataLength());
    return proto;
  }

  template <class Proto>
  void SerializeBuffer(Proto& proto) {
    auto total = proto.ByteSizeLong();
    while (GetEmptySize() < total) {
      ReAllocBuffer();
    }

    proto.SerializePartialToArray(GetBuffer(), total);
    FillData(total);
  }

  void Dispose() override;

  void AddBuffer(const char* buffer, const unsigned int size);
  unsigned short GetDataLength() const;
  int GetMsgId() const;

  void FillData(unsigned int size);
  void ReAllocBuffer();

 private:
  int _msg_id;
};

#endif