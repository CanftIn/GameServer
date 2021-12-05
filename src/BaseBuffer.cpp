#include "BaseBuffer.h"

#include <cstring>

#include "utils/Log.h"

unsigned int Buffer::GetEmptySize() {
  return _buf_size - _end_idx;
}

// TODO: if data_length more than (_buf_size+ADD_SIZE) will failed
void Buffer::ReAllocBuffer(const unsigned int data_length) {
  if (_buf_size >= MAX_SIZE) {
    Log::Warn("Buffer::ReAllocBuffer except!");
  }

  char* tmp_buf = new char[_buf_size + ADD_SIZE];
  unsigned int new_end_idx;
  if (_beg_idx < _end_idx) {
    ::memcpy(tmp_buf, _buffer + _beg_idx, _end_idx - _beg_idx);
    new_end_idx = _end_idx - _beg_idx;
  } else {
    if (_beg_idx == _end_idx && data_length <= 0) {
      new_end_idx = 0;
    } else {
      ::memcpy(tmp_buf, _buffer + _beg_idx, _buf_size - _beg_idx);
      new_end_idx = _buf_size - _beg_idx;

      if (_end_idx > 0) {
        ::memcpy(tmp_buf + new_end_idx, _buffer, _end_idx);
        new_end_idx += _end_idx;
      }
    }
  }

  _buf_size += ADD_SIZE;
  delete[] _buffer;
  _buffer = tmp_buf;
  _beg_idx = 0;
  _end_idx = new_end_idx;

  Log::Info("Buffer::ReAllocBuffer._buffer size: " + _buf_size);
}