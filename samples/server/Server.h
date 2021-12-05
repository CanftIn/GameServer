#ifndef __SERVER_H__
#define __SERVER_H__

#include "NetworkListen.h"

class Server : public NetworkListen {
 public:
  Server();
  bool DataHandler();

 protected:
  void HandleOne(ConnectObj* conn_obj);
  int Accept() override;

 protected:
  int _accept_count;
  int _send_count;
  int _recv_count;
  bool _is_show;
};

#endif