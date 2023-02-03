#include <arpa/inet.h>
#include <sys/socket.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include "gas.h"

#ifndef TLS2P_MAX_BUFFER
#define TLS2P_MAX_BUFFER 1000
#endif

char* command(int socket_fd, char* command) {
  char* result = malloc(TLS2P_MAX_BUFFER);

  // write
  write(socket_fd, command, strlen(command));

  // read output
  int step = 0;
  do {
    read(socket_fd, result, TLS2P_MAX_BUFFER);
    step++;
  } while (step < 3);

  return result;
}

int get_socket(char* addr, uint16_t port) {
  int socket_fd = socket(AF_INET, SOCK_STREAM, 0);
  if (socket_fd == -1) {
    return -1;
  }

  struct sockaddr_in server;
  server.sin_family = AF_INET;
  server.sin_addr.s_addr = inet_addr(addr);
  server.sin_port = htons(port);

  int cdesc = connect(socket_fd, (struct sockaddr *)&server, sizeof(server));
  if (cdesc == -1) {
    return -1;
  }
  return socket_fd;
}
