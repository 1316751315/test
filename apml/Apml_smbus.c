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


int32 apml_smbus_write_data(char *busname, int32 addr, int8 *reg, int8 len)
{
	int fd = -1, ret = -1;
	unsigned int i=0;
	struct i2c_msg msgs;
	struct i2c_rdwr_ioctl_data packets;
	
	packets.nmsgs = 1;
	packets.msgs = &msgs;

	fd = open(busname, O_RDWR)
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



int32 apml_smbus_read_byte(char *busname, int32 addr, int8 *reg, int8 *data, int8 wlen, int8 rlen)
{
	struct i2c_msg msgs[2];
	struct i2c_rdwr_ioctl_data packets;

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
	
	int ret = ioctl(busFd, I2C_RDWR, &packets);
	if (ret < 0)
	{
		goto end;
	}
end:
    return ret;
	

}