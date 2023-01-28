#include <ctype.h>
#include <errno.h>
#include <fcntl.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/ioctl.h>
#include <sys/poll.h>
#include <sys/select.h>
#include <sys/stat.h>
#include <sys/time.h>
#include <sys/types.h>
#include <unistd.h>

#include <linux/i2c.h>
#include <linux/i2c-dev.h>

#include "coreTypes.h"


uint32 apml_smbus_write_data(char *busname, uint32 addr, uint8 *reg, uint8 len)
{
	int fd = -1, ret = -1;
	struct i2c_msg msgs;
	struct i2c_rdwr_ioctl_data packets;
	
	packets.nmsgs = 1;
	packets.msgs = &msgs;

	fd = open(busname, O_RDWR);
	if(fd < 0){
		goto end;
	}
	
	msgs.addr = addr;
	msgs.flags = 0;
	msgs.len = len;
	msgs.buf = reg;

    ret = ioctl(fd, I2C_RDWR, &packets);
	if (ret < 0){
		goto end;
	}
    close(fd);
end:
    return ret;		
}



uint32 apml_smbus_read_byte(char *busname, uint32 addr, uint8 *reg, uint8 *data, uint8 wlen, uint8 rlen)
{
	struct i2c_msg msgs[2];
	struct i2c_rdwr_ioctl_data packets;
	printf("busname=%s  addr=0x%x reg=0x%x wlen=0x%x rlen=0x%x\n",busname,addr,*reg,wlen,rlen);
	int ret = -1;
	int fd = open(busname, O_RDWR);
	if(fd < 0){
		printf("open error!\n");
		goto end;
	}
	packets.nmsgs = 2;
	packets.msgs = msgs;

	msgs[0].addr = addr;
	msgs[0].flags = 0;
	msgs[0].len = wlen;  
	msgs[0].buf = reg;

	msgs[1].addr = addr;
	msgs[1].flags = I2C_M_RD;
	msgs[1].len = rlen;       
	msgs[1].buf = data;
	
	ret = ioctl(fd, I2C_RDWR, &packets);
	if (ret < 0)
	{
		printf("ioctl error!\n");
		goto end;
	}
	close(fd);
end:
    return ret;
	

}