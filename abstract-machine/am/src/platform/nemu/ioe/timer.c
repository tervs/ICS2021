#include <am.h>
#include <nemu.h>
#include <stdio.h>


struct timeval
{ 
   uint32_t low;
   uint32_t high;
   
}now;

void __am_timer_init() {

     now.low=inl(RTC_ADDR);
  now.high=inl(RTC_ADDR+4); 
 
 
 // cfg->present = cfg->has_rtc = true;
}

void __am_timer_uptime(AM_TIMER_UPTIME_T *uptime) {
  uint32_t low=inl(RTC_ADDR)-now.low;
  //printf("%du\n",now.low);
  uint32_t high=inl(RTC_ADDR+4)-now.high;
  uptime->us = low+(high<32);
}

void __am_timer_rtc(AM_TIMER_RTC_T *rtc) {
  rtc->second = 0;
  rtc->minute = 0;
  rtc->hour   = 0;
  rtc->day    = 0;
  rtc->month  = 0;
  rtc->year   = 1900;
}
