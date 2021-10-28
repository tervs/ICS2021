#include <device/map.h>
#include <device/alarm.h>
#include <utils.h>

static uint32_t *rtc_port_base = NULL;

static void rtc_io_handler(uint32_t offset, int len, bool is_write) 
{
  assert(offset == 0 || offset == 4);
  if (!is_write && offset == 4) {
    uint64_t us = get_time();
    rtc_port_base[0] = (uint32_t)us;
    rtc_port_base[1] = us >> 32;
  }
}

#ifndef CONFIG_TARGET_AM
static void timer_intr() 
{
  if (nemu_state.state == NEMU_RUNNING) {
    extern void dev_raise_intr();
    dev_raise_intr();//此函数无定义
  }
}
#endif

void init_timer() 
{
  rtc_port_base = (uint32_t *)new_space(8);
  //得到了该设备空间的初始地址.是真机的地址.
#ifdef CONFIG_HAS_PORT_IO
  add_pio_map ("rtc", CONFIG_RTC_PORT, rtc_port_base, 8, rtc_io_handler);
#else
  add_mmio_map("rtc", CONFIG_RTC_MMIO, rtc_port_base, 8, rtc_io_handler);//将该设备加入映射中, 即maps数组.
 //调用rtc_io_handler.实际上初次调用,初始化而已,整个handler结构都没有被调用,仅仅是将函数附加到结构体中.以后将在第一次读写的时候初次赋值
#endif                                         
  IFNDEF(CONFIG_TARGET_AM, add_alarm_handle(timer_intr));
  //但是最后调用的这个是啥玩意?
  //进行定时器(alarm)相关的初始化工作
}
