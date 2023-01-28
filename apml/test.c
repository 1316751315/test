#include<stdio.h>
#include "coreTypes.h"
#include "Apml_fdk.h"

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
    printf("%d\t%d\t%d\t%d\n",eax_val,ebx_val,ecx_val,edx_val);
    //MSR test
    uint8 pstat=0;
    ret = apml_read_pstate(&ctl,0,0,&pstat,0);
    if(ret != 0)
    {
        printf("apml_read_pstate error ret=%d\n",ret);
    }
    printf("apml_read_pstate:: pstat=0x%d\n",pstat);



    ret=apml_close_fdk(&ctl,0);
    
    //printf("%d\t%d\t%d\t\n",tdp2_watt,base_tdp,processor_tdp);
    return ret;
}