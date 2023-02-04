#include <errno.h>

#include "gas_pump.h"

uint32_t
connect_to_pump(t_gas_pump* pump)
{
  if(pump->ip_address == NULL) {
    return E_GAS_PUMP_MISSING_IP_ADDR;
  }

  if(pump->port == 0) {
    return E_GAS_PUMP_MISSING_TCP_PORT;
  }

  if(pump->socket != 0) {  
    return E_GAS_PUMP_MISSING_ALREADY_CONNECTED;
  }

  pump->socket = socket(AF_INET, SOCK_STREAM, 0);
  if (pump->socket == -1) {
    return errno;
  }

  pump->server.sin_family = AF_INET;
  pump->server.sin_addr.s_addr = inet_addr(pump->ip_address);
  pump->server.sin_port = htons(pump->port);

  int err = connect(pump->socket, (struct sockaddr *)&pump->server,
      sizeof(pump->server));
  if (err == -1) {
    return errno;
  }

  return 0;
}

uint32_t
send_command_to_pump(t_gas_pump* pump, const char* cmd)
{
  memset(pump->last_response, 0, sizeof(char));
  write(pump->socket, cmd, strlen(cmd));

  int bread = read(pump->socket, pump->last_response,
      GAS_PUMP_MAX_RESPONSE_LEN); 
  int ret = -1;
  switch(bread) {
    case -1:
      return errno;
      break;
    case 0:
      return 0;
    default:
      return E_GAS_PUMP_INCOMPLETE_READ;
      break;
  }

  return ret;
}

uint32_t
connect_and_send_command_to_pump(t_gas_pump* pump, const char* cmd)
{
  int err = connect_to_pump(pump);
  if(err) {
    return err;
  }

  err = send_command_to_pump(pump, cmd);

  return err;
}

t_gas_pump*
create_gas_pump(const char* ip_address, const uint16_t port)
{
  if(ip_address == NULL) {
    return NULL;
  }

  if(port == 0) {
    return NULL;
  }

  t_gas_pump* pump = (t_gas_pump*)malloc(sizeof(t_gas_pump));
  memset((void *)pump, 0, sizeof(t_gas_pump));

  pump->ip_address = ip_address;
  pump->port = port;

  return pump;
}

void
destroy_gas_pump(t_gas_pump* pump)
{
  if(pump == NULL) {
    return;
  }

  if(pump->socket) {
    close(pump->socket);
  }

  free(pump);
}
