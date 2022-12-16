#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <stdint.h>
#include <time.h>
#include <pthread.h>
//#include <alsa/asoundlib.h>

#include <signal.h>
#include <stdarg.h>
#include <string.h>
#include <unistd.h>
#include <sys/time.h>
#include "txz_engine.h"
#define NN 128
#define TAIL 1024

short audio_buf[160];//max 320 points

void* cmdInst;
int endflag=0;
static int cmdruncount = 100;
long cmd_time = 0;
long cmd_start = 0;

int32_t cmd_setpara()
{
    /* CMD configure */
    cmd_uint16_t cmd_shift_frames = 1; // 1 (0~10)
    cmd_uint16_t cmd_smooth_frames = 1; // 1 (0~30)
    cmd_uint16_t cmd_lock_frames = 1; // 1 (0~100)
    cmd_uint16_t cmd_post_max_frames = 35; // 35 (0~100)
    cmd_float32_t cmd_threshold = 0.50; // 0.70f (0.0f~1.0f)
    //printf("cmd threshod = %f\n", cmd_threshold);

    if (CMD_CODE_NORMAL != txzEngineSetConfig(cmdInst, cmd_shiftFrames, &cmd_shift_frames)) {
        printf( "txzEngineSetConfig cmd_shiftFrames error.\n");
            return -1;
        }
        if (CMD_CODE_NORMAL != txzEngineSetConfig(cmdInst, cmd_smoothFrames, &cmd_smooth_frames)) {
            printf( "txzEngineSetConfig cmd_smoothFrames error.\n");
            return -1;
        }
        if (CMD_CODE_NORMAL != txzEngineSetConfig(cmdInst, cmd_lockFrames, &cmd_lock_frames)) {
            printf( "txzEngineSetConfig cmd_lockFrames error.\n");
            return -1;
        }
        if (CMD_CODE_NORMAL != txzEngineSetConfig(cmdInst, cmd_postMaxFrames, &cmd_post_max_frames)) {
            printf( "txzEngineSetConfig cmd_postMaxFrames error.\n");
            return -1;
        }
        if (CMD_CODE_NORMAL != txzEngineSetConfig(cmdInst, cmd_thresHold, &cmd_threshold)) {
            printf( "txzEngineSetConfig cmd_threshold error.\n");
            return -1;
        }
        printf("txzEngineSetConfig ok\n");
        return 0;

}

int uv_cmd_init()
{
    txzEngineCreate(&cmdInst);
    if (NULL == cmdInst)
    {
        printf("txzEngineCreate err \n");
        return -1;
    }

    if (CMD_CODE_NORMAL != txzEngineInit(cmdInst))
    {
        printf("txzEngineInit err \n");
        return -1;
    }
    cmd_setpara();
    printf("txzEngineInit ok \n");
    return 0;
}


static void sig_handle(int signo)
{
    if(signo==SIGINT)
    {
        endflag=1;
    }

    return;
}

static  long get_current_time_us()
{
    struct timeval tv;
    gettimeofday(&tv,NULL);
    return tv.tv_sec * 1000000 + tv.tv_usec;
}


int main(int argc, char **argv)
{

    int ret;
    short rec_buf[160] = {0};
    FILE *rec_fd = NULL;
    FILE *write_fd = NULL;

    int count=0;
    cmd_uint16_t cmdIndex=0;

    float cmd_confidence=0;
    const char* commands = NULL;
    int cmdret;
    const char *filename = argv[1];
    int cmdcount;

    printf("demo start \n");
    if(signal(SIGINT,sig_handle) == SIG_ERR)
    {
        printf("signal err \n");
        return -1;
    }
    printf("demo 1111 \n");
    cmdret=uv_cmd_init();
    if(cmdret!=0) 
    {
        printf("uv_cmd_init err \n");
        return -1;
    }

    if(filename != NULL)
    {
        rec_fd = fopen(argv[1], "r");
        if (!rec_fd)
            return -1;
    }
    
    /*write_fd = fopen("/mnt/cmd.pcm", "w");
    if (!write_fd)
        return -1;*/
        

    count=0;

    cmdcount=0;
    int len = 0;

    txzEngineReset(cmdInst);
    while(1)
    {

        if(filename != NULL)
        {
            len = fread(rec_buf,1,320,rec_fd);
        }
        if (len < 320)
        {
            //fseek(rec_fd,0,SEEK_SET);
            break;
        }
    
        cmdIndex=0;
        //cmdcount++;
        cmd_confidence=0;
        //fwrite(rec_buf, 320, 1, write_fd); 
        cmd_start = get_current_time_us();
        cmdret=txzEngineProcess(cmdInst, rec_buf, 160, &cmdIndex,&cmd_confidence);
        cmd_time += get_current_time_us() - cmd_start;
        cmdruncount--;
        if (cmdruncount <= 0)
        {
            printf("cmd_time = %ld\n", cmd_time);
            cmdruncount = 100;
            cmd_time = 0;
        }
        if(cmdret!= CMD_CODE_NORMAL) 
        {
            printf("txzEngineProcess error, ret=%d \n",ret);
            txzEngineReset(cmdInst);
        }
        else
        {
            if (cmdIndex > 0) 
            {
                txzEngineGetName(cmdIndex, &commands);
                printf(" cmdIndex=%d , command:<%s> ,confidence=%f\n", cmdIndex,commands,cmd_confidence);
                txzEngineReset(cmdInst);
                cmdcount=0;
            }
         }

     /* if(cmdcount>1500)
        {
            cmdReset(cmdInst);
            printf("change to kws \n");
            cmdcount=0;
        }
       */
    }

exit:
        if(filename != NULL)    
        {        
            if (rec_fd)
                fclose(rec_fd);
        }
        /*
        if (write_fd)
        fclose(write_fd);
        */
        txzEngineDesrtoy(&cmdInst);

        return ret;
}
