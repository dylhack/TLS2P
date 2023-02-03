#include <stdio.h>
#include "gas.h"

#define TLS2P_MAX_BUFFER 10_000

int main() {
  char* addr = "localhost";
  uint16_t port = 10001;
  int socket_fd = get_socket(addr, port);
  if (socket_fd == -1) {
    return -1;
  }
  char* output = command(socket_fd, GET_INVENTORY);
  printf("%s", output);
  return 0;
}
