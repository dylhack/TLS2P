#ifndef INC_GAS_PUMP_H
#define INC_GAS_PUMP_H

#include <arpa/inet.h>
#include <sys/socket.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>

const char* GAS_PUMP_GET_INVENTORY = "200";
const char* GAS_PUMP_GET_VERSION = "I90200";
const char* GAS_PUMP_SHIFT_REPORT = "I20400";
const char* GAS_PUMP_GET_DELIVERY = "I20200";
const char* GAS_PUMP_GET_LEAK = "I20300";
const char* GAS_PUMP_GET_STATUS = "I20500";
const char* GAS_PUMP_GET_ALARM = "I30200";
const char* GAS_PUMP_ALARM_RESET = "IS00300";
const char* GAS_PUMP_GET_RELAY = "I40600";
const char* GAS_PUMP_RESET = "IS00100";
const char* GAS_PUMP_CLEAR_RESET = "IS00200";
const char* GAS_PUMP_GET_SENSOR = "I30100";
const char* GAS_PUMP_GET_SENSOR_DIAG = "IB0100";
const char* GAS_PUMP_GET_TANK_ALARM = "I20600";
const char* GAS_PUMP_GET_TANK_DIAG = "IA0100";
const char* GAS_PUMP_GET_SYSTEM_STATUS = "I10100";

const unsigned int GAS_PUMP_MAX_RESPONSE_LEN = 2047;

const uint32_t E_GAS_PUMP_MISSING_IP_ADDR = 0x70000001;
const uint32_t E_GAS_PUMP_MISSING_TCP_PORT = 0x70000002;
const uint32_t E_GAS_PUMP_MISSING_NO_CONNECTION = 0x70000003;
const uint32_t E_GAS_PUMP_MISSING_ALREADY_CONNECTED = 0x70000004;
const uint32_t E_GAS_PUMP_INCOMPLETE_READ = 0x70000005;

typedef struct GAS_PUMP_ {
  const char* ip_address;
  uint16_t port;
  int socket;
  struct sockaddr_in server;
  char last_response[GAS_PUMP_MAX_RESPONSE_LEN + 1];
} t_gas_pump;

t_gas_pump* create_gas_pump(const char* ip_address, const uint16_t port);
void destroy_gas_pump(t_gas_pump* pump);

uint32_t connect_to_pump(t_gas_pump* pump);
uint32_t send_command_to_pump(t_gas_pump* pump, const char* cmd);
uint32_t connect_and_send_command_to_pump(t_gas_pump* pump, const char* cmd);

#endif
