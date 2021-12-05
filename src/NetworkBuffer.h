#ifndef __NETWORKBUFFER_H__
#define __NETWORKBUFFER_H__

#include "BaseBuffer.h"

// default 128KB
#define DEFAULT_SEND_BUFFER_SIZE	1024 * 128
#define DEFAULT_RECV_BUFFER_SIZE	1024 * 128

class Packet;

using TotalSizeType = unsigned short;

class NetworkBuffer : public Buffer {
 public:
  explicit NetworkBuffer(const unsigned int size);
  virtual ~NetworkBuffer();

  bool HasData() const;

  unsigned int GetEmptySize() override;

  unsigned int GetWriteSize() const;

  unsigned int GetReadSize() const;

  void FillData(unsigned int size);
  void RemoveData(unsigned int size);
  void ReAllocBuffer();

 protected:
  unsigned int _avail_size; // data length
};

class RecvNetworkBuffer : public NetworkBuffer {
 public:
  explicit RecvNetworkBuffer(const unsigned int size);
  void Dispose() override;
  int GetBuffer(char*& buffer) const;
  Packet* GetPacket();

 private:
  void MemcpyFromBuffer(char* p_void, const unsigned int size);
};

class SendNetworkBuffer : public NetworkBuffer {
 public:
  explicit SendNetworkBuffer(const unsigned int size);
  void Dispose() override;
  int GetBuffer(char*& buffer) const;
  void AddPacket(Packet* packet);

 private:
  void MemcpyToBuffer(char* p_void, const unsigned int size);
};

#endif
