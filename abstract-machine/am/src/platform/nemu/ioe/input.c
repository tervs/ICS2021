#include <am.h>
#include <nemu.h>
#include <stdio.h>
#define KEYDOWN_MASK 0x8000
//#define KEYDOWN_MASK 0x8000

void __am_input_keybrd(AM_INPUT_KEYBRD_T *kbd) {
  //printf("test\n");
  uint32_t keyinfo=inl(KBD_ADDR);

  if(keyinfo&KEYDOWN_MASK)
  {
    kbd->keydown=1;
  }
  else{kbd->keydown=0;}
  //kbd->keydown=keyinfo&KEYDOWN_MASK;
  kbd->keycode=keyinfo^((uint32_t)KEYDOWN_MASK);
  
  
  
  //kbd->keydown = 0;
  //kbd->keycode = AM_KEY_NONE;
}
