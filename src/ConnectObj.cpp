#include "ConnectObj.h"

#include "utils/Log.h"
#include "Network.h"
#include "NetworkBuffer.h"
#include "Packet.h"
#include "SocketsOps.h"

ConnectObj::ConnectObj(Network* network, int socket)
  : _network(network),
    _socket(socket)
{
  _recv_buf = new RecvNetworkBuffer(DEFAULT_RECV_BUFFER_SIZE);
  _send_buf = new SendNetworkBuffer(DEFAULT_SEND_BUFFER_SIZE);
}

ConnectObj::~ConnectObj() {
  delete _recv_buf;
  delete _send_buf;
}

void ConnectObj::Dispose() {
  Log::Info("close socket:" + std::to_string(_socket));
  sockets::close(_socket);

  _recv_buf->Dispose();
  _send_buf->Dispose();
}

bool ConnectObj::HasRecvData() const {
  return _recv_buf->HasData();
}

Packet* ConnectObj::GetRecvPacket() const {
  return _recv_buf->GetPacket();
}

bool ConnectObj::Recv() const {
  char* buffer = nullptr;
  while (true) {
    if (_recv_buf->GetEmptySize() < (sizeof(PacketHead) + sizeof(TotalSizeType))) {
      _recv_buf->ReAllocBuffer();
    }

    const int empty_size = _recv_buf->GetBuffer(buffer);
    const int data_size = ::recv(_socket, buffer, empty_size, 0);
    if (data_size > 0) {
      Log::Info("recv size: " + std::to_string(data_size));
      _recv_buf->FillData(data_size);
    }
    else if (data_size == 0) {
      Log::Info("recv size: " + std::to_string(data_size) + " error: " + std::to_string(errno));
      return false;
    }
    else {
      const auto socket_err = errno;
      if (socket_err == EINTR || socket_err == EWOULDBLOCK || socket_err == EAGAIN) {
        return true;
      }
      Log::Error("recv size: " + std::to_string(data_size) + " error: " + std::to_string(errno));
      return false;
    }
  }
}

bool ConnectObj::HasSendData() const {
  return _send_buf->HasData();
}

void ConnectObj::SendPacket(Packet* packet) const {
  _send_buf->AddPacket(packet);
}

bool ConnectObj::Send() const {
  while (true) {
    char* buffer = nullptr;
    const int need_send_size = _send_buf->GetBuffer(buffer);

    if (need_send_size <= 0) {
      return true;
    }

    const int size = ::send(_socket, buffer, need_send_size, 0);
    if (size > 0) {
      _send_buf->RemoveData(size);

      if (size < need_send_size) {
        return true;
      }
    }

    if (size == -1) {
      const auto socket_err = errno;
      Log::Error("need_send_size: " + std::to_string(need_send_size) + " error: " + std::to_string(socket_err));
      return false;
    }
  }
}