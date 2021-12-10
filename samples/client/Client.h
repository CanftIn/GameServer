#ifndef __CLIENT_H__
#define __CLIENT_H__

#include "NetworkConnect.h"

#include <string>

class Client : public NetworkConnect {
 public:
  Client(const InetAddress& ia, int msg_count)
    : _msg_count(msg_count),
      _idx(0),
      _is_completed(false),
      _last_msg("")
  {
    _ia = ia;
  }

  void DataHandler();
  bool IsCompleted() const {
    return _is_completed;
  }

 private:
  int _msg_count;
  int _idx;

  bool _is_completed;
  std::string _last_msg;
};

#endif