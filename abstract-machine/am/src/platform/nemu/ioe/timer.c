#include <am.h>
#include <nemu.h>
#include <stdio.h>



static uint64_t read_time() {
  uint32_t lo = *(volatile uint32_t *)(RTC_ADDR + 0);
  uint32_t hi = *(volatile uint32_t *)(RTC_ADDR + 4);
  uint64_t time = ((uint64_t)hi << 32) | lo;
  return time / 10;
}



//uint32_t start_low;
//uint32_t start_high;
uint64_t start;
void __am_timer_init() 
{
  //start_low=inl(RTC_ADDR);
  //start_high=inl(RTC_ADDR+4);
  start=read_time();

}

void __am_timer_uptime(AM_TIMER_UPTIME_T *uptime) 
{

  //volatile uint64_t now=inll(RTC_ADDR);

  //uint32_t low=inl(RTC_ADDR)-start_low;
  //printf("low  %d\n",low);
  //uint32_t high=inl(RTC_ADDR+4)-start_high;
  //printf("high  %d\n",high);
  //uptime->us = low+(((uint64_t)high)<<32);

  uptime->us=read_time()-start;
}

void __am_timer_rtc(AM_TIMER_RTC_T *rtc) {
  rtc->second = 0;
  rtc->minute = 0;
  rtc->hour   = 0;
  rtc->day    = 0;
  rtc->month  = 0;
  rtc->year   = 1900;
}
