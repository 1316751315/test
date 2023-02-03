#include<stdio.h>
#include <unistd.h>
#include "coreTypes.h"
#include "Apml_fdk.h"

uint32 reg_list[]={0xc0002001,0xc0002002,0xc0002003,0xc0002011,0xc0002012,0xc0002013,0xc0002021,0xc0002022,0xc0002023,0xc0002031,0xc0002032,0xc0002033,0xc0002041, \
0xc0002042,0xc0002043,0xc0002051,0xc0002052,0xc0002053,0xc0002061,0xc0002062,0xc0002063,0xc0002071,0xc0002072,0xc0002073,0xc0002081,0xc0002082,0xc0002083, \
0xc0002091,0xc0002092,0xc0002093,0xc00020a1,0xc00020a2,0xc00020a3,0xc00020b1,0xc00020b2,0xc00020b3,0xc00020c1,0xc00020c2,0xc00020c3,0xc00020d1,0xc00020d2,0xc00020d3, \
0xc00020e1,0xc00020e2,0xc00020e3,0xc00020f1,0xc00020f2,0xc00020f3,0xc0002101,0xc0002102,0xc0002103,0xc0002111,0xc0002112,0xc0002113,0xc0002121,0xc0002122,0xc0002123, \
0xc0002131,0xc0002132,0xc0002133,0xc0002141,0xc0002142,0xc0002143,0xc0002151,0xc0002152,0xc0002153,0xc0002161,0xc0002162,0xc0002163,0xc0002001,0xc0002002,0xc0002003, \
0xc0002011,0xc0002012,0xc0002013,0xc0002021,0xc0002022,0xc0002023,0xc0002031,0xc0002032,0xc0002033,0xc0002041,0xc0002042,0xc0002043,0xc0002051,0xc0002052,0xc0002053, \
0xc0002061,0xc0002062,0xc0002063,0xc0002071,0xc0002072,0xc0002073,0xc0002081,0xc0002082,0xc0002083,0xc0002091,0xc0002092,0xc0002093,0xc00020a1,0xc00020a2,0xc00020a3, \
0xc00020b1,0xc00020b2,0xc00020b3,0xc00020c1,0xc00020c2,0xc00020c3,0xc00020d1,0xc00020d2,0xc00020d3,0xc00020e1,0xc00020e2,0xc00020e3,0xc00020f1,0xc00020f2,0xc00020f3, \
0xc0002101,0xc0002102,0xc0002103,0xc0002111,0xc0002112,0xc0002113,0xc0002121,0xc0002122,0xc0002123,0xc0002131,0xc0002132,0xc0002133,0xc0002141,0xc0002142,0xc0002143, \
0xc0002151,0xc0002152,0xc0002153,0xc0002161,0xc0002162,0xc0002163};
//uint32 reg_list[]={0xc0002001,0xc0002021};
//Core-specific read CPUID
static APML_DEV_CTL ctl;
int main(int argc , char** agrv)
{
    int ret=0;
    uint32 eax_val= 0, ebx_val=0, ecx_val=0, edx_val=0;
    ret = apml_init_fdk(&ctl,0);
    if(ret != 0)
    {
        printf("apml_init_fdk error ret=%d\n",ret);
        return -1;
    }
    ret = apml_read_cpuid(&ctl, 0,  0,  0, &eax_val, &ebx_val, &ecx_val, &edx_val,0);
    if(ret != 0)
    {
        printf("apml_read_cpuid error ret=%d\n",ret);
    }
#if 0
    for(int i=0; i<(sizeof(reg_list)/4); i++)
    {
        ret = apml_read_msr_value(&ctl,0,reg_list[i],0);
	    if (ret != APML_SUCCESS) {
		    printf("apml_read_msr_value  failed! res=%d\n",ret);
	    }
    }
#endif
    uint8 tmp8;
	/* Read APIC Spin Loop Status Register 0 */
	ret = apml_read_rmi_reg(&ctl, 0, 0, 0x06, &tmp8,0);
    if(ret != 0)
    {
        printf("read APIC Spin Loop Status error ret=%d\n",ret);
    }
    printf("core 0 APIC Spin Loop Status Register 0 :0x%x\n",tmp8);


    ret = apml_read_rmi_reg(&ctl, 0, 0, 0x07, &tmp8,0);
    if(ret != 0)
    {
        printf("read APIC Spin Loop Status error ret=%d\n",ret);
    }
    printf("core 0 APIC Spin Loop Status Register 1 :0x%x\n",tmp8);




    uint32 value=0;
    ret = apml_read_max_pstate(&ctl,0,&value,0);
    if(ret != 0)
    {
        printf("apml_read_max_pstate error ret=%d\n",ret);
    }

    ret=apml_close_fdk(&ctl,0);
    
    //printf("%d\t%d\t%d\t\n",tdp2_watt,base_tdp,processor_tdp);
    return ret;
}