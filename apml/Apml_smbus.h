#ifndef APML_SMBUS_1
#define APML_SMBUS_1
#include "coreTypes.h"
uint32 apml_smbus_write_data(char *busname, uint32 addr, uint8 *reg, uint8 len);
uint32 apml_smbus_read_byte(char *busname, uint32 addr, uint8 *reg, uint8 *data, uint8 wlen, uint8 rlen);


#endif 
