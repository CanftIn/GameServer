#include "Thread.h"

bool Thread::Start() {
  _is_run = true;
  _thread = std::thread([this]() {
    while (_is_run) {
      Update();
    }
  });
  return true;
}

void Thread::Stop() {
  if (_is_run) {
    _is_run = false;
  }
}

void Thread::Dispose() {
  Stop();

  if (_thread.joinable()) {
    _thread.join();
  }
}

void Thread::Update() {
  
}