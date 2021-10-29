#include <am.h>
#include <nemu.h>
#include <stdio.h>
#define KEYDOWN_MASK 0x8000


void __am_input_keybrd(AM_INPUT_KEYBRD_T *kbd) {

  uint32_t keyinfo=inl(KBD_ADDR);
  
  kbd->keycode = keyinfo & (~KEYDOWN_MASK);
  kbd->keydown = (keyinfo & KEYDOWN_MASK) > 0;
  
  /*
  bool s=keyinfo&KEYDOWN_MASK;
  if(s)
  {
    kbd->keydown=1;
  }
  else{kbd->keydown=0;}
  //kbd->keydown=keyinfo&KEYDOWN_MASK;

  if(!s)
  {
    kbd->keycode=keyinfo;
  }
  else{kbd->keycode=keyinfo-KEYDOWN_MASK;}

  //kbd->keycode=keyinfo^((uint32_t)KEYDOWN_MASK);
  */

  
}
