#include <am.h>
#include <nemu.h>
#include<stdio.h>
#define SYNC_ADDR (VGACTL_ADDR + 4)

void __am_gpu_init() 
{

}

void __am_gpu_config(AM_GPU_CONFIG_T *cfg) 
{
  *cfg = (AM_GPU_CONFIG_T) 
  {
    .present = true, .has_accel = false,
    .width=inw(VGACTL_ADDR+2),
    .height=inw(VGACTL_ADDR),
    //.width = 0, .height = 0,
    .vmemsz = 0
  };
}

void __am_gpu_fbdraw(AM_GPU_FBDRAW_T *ctl) 
{
  if (ctl->sync) 
  {
    outl(SYNC_ADDR, 1);
  }

  for(int i=(ctl->y);i<(ctl->y)+(ctl->h);i++)
  {
    for(int j=(ctl->x);j<(ctl->x)+(ctl->w);j++)
    {
      printf("%d  %d  %d\n",i,j,(uint32_t)(ctl->pixels));
      outl(FB_ADDR+i*(ctl->w)+j,(uint32_t)(ctl->pixels));
      
    }
  }
  //outl()

//(x,y),地址为base+(y-1)*width+(x-1)

}

void __am_gpu_status(AM_GPU_STATUS_T *status) 
{
  status->ready = true;
}
