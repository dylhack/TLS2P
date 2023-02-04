#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>

#include "gas_pump.h"

#define MAX_RESPONSE_BUFF 1024 * 1024
#define TLS2P_MAX_BUFFER 10_000

void usage(const char* pname);

int
main(int argc, const char** argv) {
  if(argc < 3) {
    usage(argv[0]);

    return -1;
  }

  const char* dest_addr = argv[1];
  const char* cmd = argv[2];

  uint16_t port = 0;
  if(argc == 4) {
    port = strtoul(argv[3], NULL, 0);
  }
  else { 
    port = 10001;
  }

  t_gas_pump* pump = create_gas_pump(dest_addr, port);
  if(pump == NULL) {
    fprintf(stderr, "Unable to create gas pump object.\n");
    return -1;
  }

  int r = connect_and_send_command_to_pump(pump, cmd);
  if(r == 0) {
    printf("%s", pump->last_response);
  }
  else {
    fprintf(stderr, "Unable to connect/send command: 0x%0d\n", r);
  }

  destroy_gas_pump(pump);

  return 0;
}

void
usage(const char* pname)
{
  fprintf(stderr, "usage: %s <ip_address> <command> {port}\n", pname);
}
