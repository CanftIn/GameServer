#ifndef __BASEBUFFER_H__
#define __BASEBUFFER_H__

#include "Disposable.h"

#define ADD_SIZE 100
#define MAX_SIZE 1024 * 1024

class Buffer : public IDisposable {
 public:
  Buffer()
    : _buffer{nullptr},
      _beg_idx{0},
      _end_idx{0},
      _buf_size{0}
    {}

  Buffer(const unsigned int buf_size)
    : _buffer{new char[buf_size]},
      _beg_idx{0},
      _end_idx{0},
      _buf_size{buf_size}
  {}

  virtual unsigned int GetEmptySize();
  void ReAllocBuffer(unsigned int data_length);
  unsigned int GetEndIdx() const {
    return _end_idx;
  }

  unsigned int GetBegIdx() const {
    return _beg_idx;
  }

  unsigned int GetTotalSize() const {
    return _buf_size;
  }

  void CleanBuffer() {
    if (_buffer != nullptr) {
      delete[] _buffer;
    }

    _beg_idx = 0;
    _end_idx = 0;
    _buf_size = 0;
  }

  char* GetBuffer() const {
    return _buffer;
  }

 protected:
  char* _buffer;
  unsigned int _beg_idx;
  unsigned int _end_idx;
  unsigned int _buf_size;
};

#endif
