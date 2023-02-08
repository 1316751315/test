#include<stdio.h>
#include <unistd.h>
#include "coreTypes.h"
#include "Apml_fdk.h"
#include <time.h>
#include <sys/stat.h>
#define LINE_NUM 2000

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
//Core-specific read CPUID
static APML_DEV_CTL ctl;
int main(int argc , char* argv[])
{
    int ret=0;
    FILE* fp;
    time_t timep;
    struct tm *p;
    uint32 reg_val_h, reg_val_l;
    uint32 count=0;
    char c;

    ret = apml_init_fdk(&ctl,0);
    if(ret != 0)
    {
        printf("apml_init_fdk error ret=%d\n",ret);
        return -1;
    }

    mkdir("/usr/log",0755);
    fp = fopen("/usr/log/apml_msr.log","a+");

    //获取当前文件行数
    while ((c = fgetc(fp)) != EOF) {
        if (c == '\n') {
            count++;
        }
    }

    //超过设定行阈值，删除文件重新创建新文件
    if((argc == 1) && ((count + (sizeof(reg_list)/sizeof(uint32))) > LINE_NUM))
    {
        fclose(fp);
        remove("/usr/log/apml_msr.log");
        fp = fopen("/usr/log/apml_msr.log","a+");
    }



    //获取当前时间
    time(&timep);
    p=gmtime(&timep);
    //存储读取日志
    if(argc > 1)
    {
        //read simple register value
        uint32 reg = strtol(argv[1]);
        if(1+count > LINE_NUM)
        {
            fclose(fp);
            remove("/usr/log/apml_msr.log");
            fp = fopen("/usr/log/apml_msr.log","a+");
        }
        ret = apml_read_msr_value(&ctl,0,&reg_val_h,&reg_val_l,reg,0);
        if (ret != APML_SUCCESS) {
            printf("apml_read_msr_value register:0x%x failed! res=%d\n",reg, ret);
            fprintf(fp, "%d-%d-%d %d:%d:%d    register:0x%x    status:failed\n",1900+p->tm_year, 1+p->tm_mon, p->tm_mday, 8+p->tm_hour,p->tm_min,p->tm_sec,reg);
        }
        fprintf(fp, "%d-%d-%d %d:%d:%d    register:0x%x    value:0x%08x%08x\n",1900+p->tm_year, 1+p->tm_mon, p->tm_mday, 8+p->tm_hour,p->tm_min,p->tm_sec,reg,reg_val_h,reg_val_l);
    }
    else{
        for(int i=0; i<(sizeof(reg_list)/sizeof(uint32)); i++)
        {
            ret = apml_read_msr_value(&ctl,0,&reg_val_h,&reg_val_l,reg_list[i],0);
            if (ret != APML_SUCCESS) {
                printf("apml_read_msr_value  register:0x%x failed! res=%d\n",reg_list[i],ret);
                fprintf(fp, "%d-%d-%d %d:%d:%d    register:0x%x    status:failed\n",1900+p->tm_year, 1+p->tm_mon, p->tm_mday, 8+p->tm_hour,p->tm_min,p->tm_sec,reg_list[i]);
            }
            fprintf(fp, "%d-%d-%d %d:%d:%d    register:0x%x    value:0x%08x%08x\n",1900+p->tm_year, 1+p->tm_mon, p->tm_mday, 8+p->tm_hour,p->tm_min,p->tm_sec,reg_list[i],reg_val_h,reg_val_l);
        }
    }
    fclose(fp);



#ifdef READ_CPUID_EN
    uint32 eax_val= 0, ebx_val=0, ecx_val=0, edx_val=0;
    ret = apml_read_cpuid(&ctl, 0,  0,  0, &eax_val, &ebx_val, &ecx_val, &edx_val,0);
    if(ret != 0)
    {
        printf("apml_read_cpuid error ret=%d\n",ret);
    }
#endif

#ifdef READ_PSTATE //access the P-State Status Register
    uint32 value=0;
    uint8 tmp8=0;
    ret = apml_read_rmi_reg(&ctl, 0, 0, 0x41, &tmp8,0);
    if(ret != 0)
    {
        printf("read register 0x41 faild! tmp8:0x%x\n",tmp8);
    }
    printf("read register 0x41 value:0x%x\n",tmp8);
    if(ret != 0)
    {
        tmp8=0;
    }
    ret = apml_read_max_pstate(&ctl,tmp8,&value,0);
    if(ret != 0)
    {
        printf("apml_read_max_pstate error ret=%d\n",ret);
    }
#endif

    ret=apml_close_fdk(&ctl,0);
    return ret;
}