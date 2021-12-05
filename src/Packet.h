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