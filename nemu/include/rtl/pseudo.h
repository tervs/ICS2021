#ifndef __RTL_PSEUDO_H__
#define __RTL_PSEUDO_H__

#ifndef __RTL_RTL_H__
#error "Should be only included by <rtl/rtl.h>"
#endif

extern int32_t sign_extend(int32_t value, uint32_t bits,uint32_t sign);

/*{
    assert(bits > 0 && bits < 32);
    uint32_t mask = ((~0U) >> (bits - 1)) << (bits - 1);
    if (sign != 0)
        value |= mask;
    else
        value &= ~mask;
    return value;
}
*/
/* RTL pseudo instructions */

static inline def_rtl(li, rtlreg_t* dest, const rtlreg_t imm) {
  rtl_addi(s, dest, rz, imm);
}

static inline def_rtl(mv, rtlreg_t* dest, const rtlreg_t *src1) {
  rtl_addi(s, dest, src1, 0);
}

static inline def_rtl(not, rtlreg_t *dest, const rtlreg_t* src1) {
  // dest <- ~src1
  TODO();
}

static inline def_rtl(neg, rtlreg_t *dest, const rtlreg_t* src1) {
  // dest <- -src1
  TODO();
}

static inline def_rtl(sext, rtlreg_t* dest, const rtlreg_t* src1, int width) {
  *dest=sign_extend(*dest,width,*src1);
  
  // dest <- signext(src1[(width * 8 - 1) .. 0])
  //TODO();
}

static inline def_rtl(zext, rtlreg_t* dest, const rtlreg_t* src1, int width) {
  // dest <- zeroext(src1[(width * 8 - 1) .. 0])
  TODO();
}

static inline def_rtl(msb, rtlreg_t* dest, const rtlreg_t* src1, int width) {
  // dest <- src1[width * 8 - 1]
  TODO();
}


#endif
