#ifndef __NETWORKCONNECT_H__
#define __NETWORKCONNECT_H__

#include "Network.h"
#include "InetAddress.h"

class ConnectObj;
class Packet;

class NetworkConnect : public Network {
 public:
  bool Connect(const InetAddress& ia);
  bool Update();

  bool HasRecvData();
  Packet* GetRecvPacket();
  void SendPacket(Packet* packet);
  bool IsConnected() const;

 private:
  ConnectObj* GetConnectObj();

 private:
  InetAddress _ia;
};

#endif