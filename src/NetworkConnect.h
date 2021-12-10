#ifndef __NETWORKCONNECT_H__
#define __NETWORKCONNECT_H__

#include "Network.h"
#include "InetAddress.h"

class ConnectObj;
class Packet;

class NetworkConnect : public Network {
 public:
  NetworkConnect()
    : _ia(2333) 
  {}
  NetworkConnect(const InetAddress& ia)
    : _ia(ia) 
  {}
  bool Connect();
  bool Update();

  bool HasRecvData();
  Packet* GetRecvPacket();
  void SendPacket(Packet* packet);
  bool IsConnected() const;

 private:
  ConnectObj* GetConnectObj();

 protected:
  InetAddress _ia;
};

#endif