#ifndef __CONNECTOBJ_H__
#define __CONNECTOBJ_H__

#include "Disposable.h"

class Network;
class RecvNetworkBuffer;
class SendNetworkBuffer;
class Packet;

class ConnectObj : public IDisposable {
 public:
  ConnectObj(Network* network, int socket);
  ~ConnectObj() override;

  void Dispose() override;
  int GetSocket() const { return _socket; }
  bool HasRecvData() const;
  Packet* GetRecvPacket() const;
  bool Recv() const;

  bool HasSendData() const;
  void SendPacket(Packet* pPacket) const;
  bool Send() const;

 protected:
  Network* _network;
  const int _socket;
  RecvNetworkBuffer* _recv_buf;
  SendNetworkBuffer* _send_buf;
};

#endif
