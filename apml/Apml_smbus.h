#ifndef APML_SMBUS_1
#define APML_SMBUS_1
#include "coreTypes.h"
int32 apml_smbus_write_data(char *busname, int32 addr, int8 *reg, int8 len);
int32 apml_smbus_read_byte(char *busname, int32 addr, int8 *reg, int8 *data, int8 wlen, int8 rlen);


#endif 
