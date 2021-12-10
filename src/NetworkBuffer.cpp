#include "NetworkBuffer.h"

#include <cstdlib>
#include <iostream>
#include <cstring>

#include "Packet.h"

NetworkBuffer::NetworkBuffer(const unsigned int size)
  : _avail_size(0),
    Buffer(size)
{}

NetworkBuffer::~NetworkBuffer() {
  CleanBuffer();
}

bool NetworkBuffer::HasData() const {
  if (_avail_size <= 0) {
    return false;
  }

  // must have a head
  if (_avail_size < sizeof(PacketHead)) {
    return false;
  }

  return true;
}

unsigned int NetworkBuffer::GetEmptySize() {
  return _buf_size - _avail_size;
}

unsigned int NetworkBuffer::GetWriteSize() const {
  if (_beg_idx <= _end_idx) {
    return _buf_size - _end_idx;
  } else {
    return _beg_idx - _end_idx;
  }
}

unsigned int NetworkBuffer::GetReadSize() const {
  if (_avail_size <= 0) {
    return 0;
  }

  if (_beg_idx < _end_idx) {
    return _end_idx - _beg_idx;
  } else {
    return _buf_size - _beg_idx;
  }
}

void NetworkBuffer::FillData(unsigned int size) {
  _avail_size += size;

  if ((_buf_size - _end_idx) <= size) {
    size -= _buf_size - _end_idx;
    _end_idx = 0;
  }

  _end_idx += size;
}

void NetworkBuffer::RemoveData(unsigned int size) {
  _avail_size -= size;

  if ((_beg_idx + size) >= _buf_size) {
    size -= _buf_size - _beg_idx;
    _beg_idx = 0;
  }

  _beg_idx += size;
}

void NetworkBuffer::ReAllocBuffer() {
  Buffer::ReAllocBuffer(_avail_size);
}

///////////////////////////////////////////////////////

RecvNetworkBuffer::RecvNetworkBuffer(const unsigned int size)
  : NetworkBuffer(size)
{}

void RecvNetworkBuffer::Dispose() {

}

int RecvNetworkBuffer::GetBuffer(char*& buffer) const {
  buffer = _buffer + _end_idx;
  return GetWriteSize();
}

Packet* RecvNetworkBuffer::GetPacket() {
  if (_avail_size < sizeof(TotalSizeType)) {
    return nullptr;
  }

  unsigned short total_size;
  MemcpyFromBuffer(reinterpret_cast<char*>(&total_size), sizeof(TotalSizeType));

  if (_avail_size < total_size) {
    return nullptr;
  }

  RemoveData(sizeof(TotalSizeType));

  PacketHead head;
  MemcpyFromBuffer(reinterpret_cast<char*>(&head), sizeof(PacketHead));
  RemoveData(sizeof(PacketHead));

  Packet* packet = new Packet(head.MsgId);
  const auto data_length = total_size - sizeof(PacketHead) - sizeof(TotalSizeType);
  while (packet->GetTotalSize() < data_length) {
    packet->ReAllocBuffer();
  }

  MemcpyFromBuffer(packet->GetBuffer(), data_length);
  packet->FillData(data_length);
  RemoveData(data_length);

  return packet;
}

void RecvNetworkBuffer::MemcpyFromBuffer(char* p_void, const unsigned int size) {
  const auto read_size = GetReadSize();
  if (read_size < size) {
    ::memcpy(p_void, _buffer + _beg_idx, read_size);
    ::memcpy(p_void + read_size, _buffer, size - read_size);
  } else {
    ::memcpy(p_void, _buffer + _beg_idx, size);
  }
}

//////////////////////////////////////////////////////////

SendNetworkBuffer::SendNetworkBuffer(const unsigned int size)
  : NetworkBuffer(size)
{}

void SendNetworkBuffer::Dispose()
{}

int SendNetworkBuffer::GetBuffer(char*& buffer) const {
  if (_avail_size <= 0) {
    buffer = nullptr;
    return 0;
  }

  if (_beg_idx < _end_idx) {
    buffer = _buffer + _beg_idx;
    return _end_idx - _beg_idx;
  } else {
    buffer = _buffer + _beg_idx;
    return _buf_size - _beg_idx;
  }
}

void SendNetworkBuffer::AddPacket(Packet* packet) {
  const auto data_length = packet->GetDataLength();
  TotalSizeType total_size = data_length + sizeof(PacketHead) + sizeof(TotalSizeType);

  while (GetEmptySize() < total_size) {
    ReAllocBuffer();
  }

  MemcpyToBuffer(reinterpret_cast<char*>(&total_size), sizeof(TotalSizeType));
  
  PacketHead head;
  head.MsgId = packet->GetMsgId();
  MemcpyToBuffer(reinterpret_cast<char*>(&head), sizeof(PacketHead));

  MemcpyToBuffer(packet->GetBuffer(), packet->GetDataLength());
}

void SendNetworkBuffer::MemcpyToBuffer(char* p_void, const unsigned int size) {
  const auto write_size = GetWriteSize();
  if (write_size < size) {
    ::memcpy(_buffer + _end_idx, p_void, write_size);
    ::memcpy(_buffer, p_void + write_size, size - write_size);
  } else {
    ::memcpy(_buffer + _end_idx, p_void, size);
  }
  FillData(size);
}