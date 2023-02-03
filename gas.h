#include <stdint.h>

char static GET_INVENTORY[] = "200";
char static GET_VERSION[] = "I90200";
char static SHIFT_REPORT[] = "I20400";
char static GET_DELIVERY[] = "I20200";
char static GET_LEAK[] = "I20300";
char static GET_STATUS[] = "I20500";
char static GET_ALARM[] = "I30200";
char static ALARM_RESET[] = "IS00300";
char static GET_RELAY[] = "I40600";
char static RESET[] = "IS00100";
char static CLEAR_RESET[] = "IS00200";
char static GET_SENSOR[] = "I30100";
char static GET_SENSOR_DIAG[] = "IB0100";
char static GET_TANK_ALARM[] = "I20600";
char static GET_TANK_DIAG[] = "IA0100";
char static GET_SYSTEM_STATUS[] = "I10100";

char* command(int socket_fd, char* command);
int get_socket(char* addr, uint16_t port);
