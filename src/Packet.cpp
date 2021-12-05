#include "Packet.h"

#include <cstring>

Packet::Packet()
  : _msg_id(0),
    Buffer(DEFAULT_PACKET_BUFFER_SIZE)
{
  CleanBuffer();
}

Packet::Packet(const int msg_id)
  : _msg_id(msg_id),
    Buffer(DEFAULT_PACKET_BUFFER_SIZE)
{
  CleanBuffer();
}

Packet::~Packet() {
  CleanBuffer();
}

void Packet::Dispose() {
  _msg_id = 0;
  _beg_idx = 0;
  _end_idx = 0;
}

void Packet::AddBuffer(const char* buffer, const unsigned int size) {
  while (GetEmptySize() < size) {
    ReAllocBuffer();
  }
  
  ::memcpy(_buffer, buffer, size);
  FillData(size);
}

unsigned short Packet::GetDataLength() const {
  return _end_idx - _beg_idx;
}

int Packet::GetMsgId() const
{
  return _msg_id;
}

void Packet::FillData(const unsigned int size) {
  _end_idx += size;
}

void Packet::ReAllocBuffer() {
  Buffer::ReAllocBuffer(_end_idx - _beg_idx);
}