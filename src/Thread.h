#ifndef __THREAD_H__
#define __THREAD_H__

#include <thread>

#include "Disposable.h"

class Thread : public IDisposable {
 public:
  Thread() : _is_run{false} {}
  
  virtual bool Start();
  void Stop();
  void Dispose() override;
  virtual void Update();

  bool IsRun() const { return _is_run; }

 private:
  bool _is_run;
  std::thread _thread;
};

#endif
