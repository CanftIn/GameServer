#ifndef __DISPOSABLE_H__
#define __DISPOSABLE_H__

class IDisposable {
 public:
  virtual ~IDisposable() = default;
  virtual void Dispose() = 0;
};

#endif
