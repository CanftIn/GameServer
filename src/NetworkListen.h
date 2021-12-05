#ifndef __NETWORKLISTEN_H__
#define __NETWORKLISTEN_H__

#include "Network.h"
#include "InetAddress.h"

class NetworkListen : public Network {
 public:
  bool Listen(const InetAddress& ia);
  bool Update();

 protected:
  virtual int Accept();
};

#endif