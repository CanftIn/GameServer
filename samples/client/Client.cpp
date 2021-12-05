#include <iostream>

#include "Network.h"

int main(int argc, char** argv) {
  SOCKET socket = ::socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
  if (socket == INVALID_SOCKET)
  {
    std::cout << "::socket failed. err:" << errno << std::endl;
    return 1;
  }

  sockaddr_in addr;
  memset(&addr, 0, sizeof(sockaddr_in));
  addr.sin_family = AF_INET;
  addr.sin_port = htons(2333);
  ::inet_pton(AF_INET, "127.0.0.1", &addr.sin_addr.s_addr);

  if (::connect(socket, (struct sockaddr *)&addr, sizeof(sockaddr)) < 0)
  {
    std::cout << "::connect failed. err:" << errno << std::endl;
    return 1;
  }

  std::string msg = "ping";
  ::send(socket, msg.c_str(), msg.length(), 0);

  std::cout << "::send." << msg.c_str() << std::endl;

  char buffer[1024];
  memset(&buffer, 0, sizeof(buffer));
  ::recv(socket, buffer, sizeof(buffer), 0);
  std::cout << "::recv." << buffer << std::endl;

  ::close(socket);
  return 0;
}