#include <am.h>
#include <nemu.h>
#include<stdio.h>
#define SYNC_ADDR (VGACTL_ADDR + 4)
#define N   32
void __am_gpu_init() 
{
/*
  int w = io_read(AM_GPU_CONFIG).width;
  int h = io_read(AM_GPU_CONFIG).height;
  int i;

  uint32_t *fb = (uint32_t *)(uintptr_t)FB_ADDR;
  for (i = 0; i < w * h; i ++) fb[i] = (0xbbbbbbbb)&i;
  outl(SYNC_ADDR, 1);
    */ 
}

void __am_gpu_config(AM_GPU_CONFIG_T *cfg) 
{
  
  *cfg = (AM_GPU_CONFIG_T) 
  {
    .present = true, .has_accel = false,
    .width=inw(VGACTL_ADDR+2),
    .height=inw(VGACTL_ADDR),
    .vmemsz = 0
  };


}

void __am_gpu_fbdraw(AM_GPU_FBDRAW_T *ctl) 
{

    int width = io_read(AM_GPU_CONFIG).width;
    int x=ctl->x;
    int y=ctl->y;
    int w=ctl->w;
    int h=ctl->h;
    uintptr_t *pixels=ctl->pixels;

    int cnt=0;

    for(int i=y;i<y+h;i++)
    {
      for(int j=x;j<x+w;j++)
      {
        outl(FB_ADDR+4*(i*width+j),*(pixels+cnt));
        //printf("%d\n",*(pixels+cnt));
        cnt++ ;
      }
    }



    if (ctl->sync) 
    {
      outl(SYNC_ADDR, 1);
    }

}

void __am_gpu_status(AM_GPU_STATUS_T *status) 
{
  status->ready = true;
}
