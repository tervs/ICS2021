#include <am.h>
#include <nemu.h>
#include <stdio.h>


uint64_t start;

void __am_timer_init() {

     start=inll(RTC_ADDR);
}

void __am_timer_uptime(AM_TIMER_UPTIME_T *uptime) 
{
  uint64_t low=inll(RTC_ADDR)-start;
  printf("%llu\n",low);
  uint32_t high=inl(RTC_ADDR+4);
  printf("%lu\n",high);
  uptime->us = low;
}

void __am_timer_rtc(AM_TIMER_RTC_T *rtc) {
  rtc->second = 0;
  rtc->minute = 0;
  rtc->hour   = 0;
  rtc->day    = 0;
  rtc->month  = 0;
  rtc->year   = 1900;
}
