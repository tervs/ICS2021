#include <NDL.h>
#include <sdl-video.h>
#include <assert.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>

void SDL_BlitSurface(SDL_Surface *src, SDL_Rect *srcrect, SDL_Surface *dst, SDL_Rect *dstrect) {
  assert(dst && src);
  assert(dst->format->BitsPerPixel == src->format->BitsPerPixel);
   int dst_x,dst_y,dst_w = dst->w,dst_h = dst->h;
  int src_x,src_y,src_w = src->w, src_h = src->h;
  //printf("dst x:%d\n",dstrect->x);
  if(srcrect == NULL)
  {
    //printf("1\n");
    src_x = src_y = 0;
    src_w = src->w;
    src_h = src->h;
  }
  else {
    //printf("2\n");
    src_x = srcrect->x;
    src_y = srcrect->y;
    src_w = srcrect->w;
    src_h = srcrect->h;
  }
  if(dstrect == NULL)
  {//printf("3\n");
    dst_x = dst_y = 0;
    dst_w = dst->w;
    dst_h = dst->h;
  }
  else {
    //printf("4\n");
    dst_x = dstrect->x;
    dst_y = dstrect->y;
    dst_w = dstrect->w;
    dst_h = dstrect->h;
  }
  //uint32_t *src_color = src->pixels;
      //uint32_t *x=malloc(dstrect->w*dstrect->h);
    //memset(x,0xffffff,sizeof(x));
  //uint32_t color_width = dst->format->palette?1:4;

  uint32_t *p=(uint32_t *)(src->pixels);
  printf("x:%d  y:%d  w:%d  h:%d   in bilt\n",dst_x,dst_y,src_w,src_h);
  
  NDL_DrawRect(p,dst_x,dst_y,src_w,src_h);
  
  //printf("color width %d\n",color_width);
  ///for(int i = 0;i < src_h;i++)
  //  memcpy(dst_color+color_width*((i+dst_y)*dst->w+dst_x),src_color+color_width*((i+src_y)*src->w+src_x),color_width*src_w);
}

void SDL_FillRect(SDL_Surface *dst, SDL_Rect *dstrect, uint32_t color) {
  
  if(dstrect==NULL)
  {
    printf("here?\n");
    uint32_t *x=malloc(4*400*300);
    memset(x,color,4*400*300);
    NDL_DrawRect(x,0,0,0,0);
  }
  else if((!dstrect->w)&&(dstrect->h==0))
  {
    printf("no null\n");
    uint32_t *x=malloc(400*300);
    memset(x,color,400*300);
    NDL_DrawRect(x,0,0,0,0);
  }
  else
  {
    printf(" nnnn\n");
    uint32_t *x=malloc(dstrect->w*dstrect->h);
    memset(x,color,sizeof(x));
    NDL_DrawRect(x,dstrect->x,dstrect->y,dstrect->w,dstrect->h);
  }

  
  //printf("x is %p\n",&color);
  //printf("x is %p\n",&color);
  //printf("x is %p\n",&color);
  //printf("x is %p\n",&color);
  //printf("x is %p\n",&color);

  //SDL_UpdateRect(dst,)

}

void SDL_UpdateRect(SDL_Surface *s, int x, int y, int w, int h) {

printf("test in update\n");
uint32_t *p=(uint32_t *)(s->pixels);
  printf("x:%d y:%d w:%d h:%d in updaterect\n",x,y,w,h);
  NDL_DrawRect(p, x,  y,  w,  h); 

//while(1);

}

// APIs below are already implemented.

static inline int maskToShift(uint32_t mask) {
  switch (mask) {
    case 0x000000ff: return 0;
    case 0x0000ff00: return 8;
    case 0x00ff0000: return 16;
    case 0xff000000: return 24;
    case 0x00000000: return 24; // hack
    default: assert(0);
  }
}

SDL_Surface* SDL_CreateRGBSurface(uint32_t flags, int width, int height, int depth,
    uint32_t Rmask, uint32_t Gmask, uint32_t Bmask, uint32_t Amask) {
  assert(depth == 8 || depth == 32);
  SDL_Surface *s = malloc(sizeof(SDL_Surface));
  assert(s);
  s->flags = flags;
  s->format = malloc(sizeof(SDL_PixelFormat));
  
  assert(s->format);
  if (depth == 8) {
    s->format->palette = malloc(sizeof(SDL_Palette));
    assert(s->format->palette);
    s->format->palette->colors = malloc(sizeof(SDL_Color) * 256);
    assert(s->format->palette->colors);
    memset(s->format->palette->colors, 0, sizeof(SDL_Color) * 256);
    s->format->palette->ncolors = 256;
  } else {
    s->format->palette = NULL;
    s->format->Rmask = Rmask; s->format->Rshift = maskToShift(Rmask); s->format->Rloss = 0;
    s->format->Gmask = Gmask; s->format->Gshift = maskToShift(Gmask); s->format->Gloss = 0;
    s->format->Bmask = Bmask; s->format->Bshift = maskToShift(Bmask); s->format->Bloss = 0;
    s->format->Amask = Amask; s->format->Ashift = maskToShift(Amask); s->format->Aloss = 0;
  }

  s->format->BitsPerPixel = depth;
  s->format->BytesPerPixel = depth / 8;

  s->w = width;
  s->h = height;
  s->pitch = width * depth / 8;
  assert(s->pitch == width * s->format->BytesPerPixel);

  if (!(flags & SDL_PREALLOC)) {
    s->pixels = malloc(s->pitch * height);
    assert(s->pixels);
  }

  return s;
}

SDL_Surface* SDL_CreateRGBSurfaceFrom(void *pixels, int width, int height, int depth,
    int pitch, uint32_t Rmask, uint32_t Gmask, uint32_t Bmask, uint32_t Amask) {
  SDL_Surface *s = SDL_CreateRGBSurface(SDL_PREALLOC, width, height, depth,
      Rmask, Gmask, Bmask, Amask);
  assert(pitch == s->pitch);
  s->pixels = pixels;
  return s;
}

void SDL_FreeSurface(SDL_Surface *s) {
  if (s != NULL) 
  { //printf("format %p\n",s->format);
    //printf("1\n");
    if (s->format != NULL) 
    {//printf("2\n");
      if (s->format->palette != NULL) 
      {//printf("3\n");
        if (s->format->palette->colors != NULL) 
        free(s->format->palette->colors);
        free(s->format->palette);
        //printf("4\n");
      }
      free(s->format);
    }
    if (s->pixels != NULL && !(s->flags & SDL_PREALLOC)) 
    free(s->pixels);
    free(s);
  }
}

SDL_Surface* SDL_SetVideoMode(int width, int height, int bpp, uint32_t flags) {
  if (flags & SDL_HWSURFACE) {NDL_OpenCanvas(&width, &height) ;
 // printf("test in  w %d  h %d\n",width,height);
  }
  return SDL_CreateRGBSurface(flags, width, height, bpp,
      DEFAULT_RMASK, DEFAULT_GMASK, DEFAULT_BMASK, DEFAULT_AMASK);
}

void SDL_SoftStretch(SDL_Surface *src, SDL_Rect *srcrect, SDL_Surface *dst, SDL_Rect *dstrect) {
  assert(src && dst);
  assert(dst->format->BitsPerPixel == src->format->BitsPerPixel);
  assert(dst->format->BitsPerPixel == 8);

  int x = (srcrect == NULL ? 0 : srcrect->x);
  int y = (srcrect == NULL ? 0 : srcrect->y);
  int w = (srcrect == NULL ? src->w : srcrect->w);
  int h = (srcrect == NULL ? src->h : srcrect->h);

  assert(dstrect);
  if(w == dstrect->w && h == dstrect->h) {
    /* The source rectangle and the destination rectangle
     * are of the same size. If that is the case, there
     * is no need to stretch, just copy. */
    SDL_Rect rect;
    rect.x = x;
    rect.y = y;
    rect.w = w;
    rect.h = h;
    SDL_BlitSurface(src, &rect, dst, dstrect);
  }
  else {
    assert(0);
  }
}

void SDL_SetPalette(SDL_Surface *s, int flags, SDL_Color *colors, int firstcolor, int ncolors) {
  assert(s);
  assert(s->format);
  assert(s->format->palette);
  assert(firstcolor == 0);

  s->format->palette->ncolors = ncolors;
  memcpy(s->format->palette->colors, colors, sizeof(SDL_Color) * ncolors);

  if(s->flags & SDL_HWSURFACE) {
    assert(ncolors == 256);
    for (int i = 0; i < ncolors; i ++) {
      uint8_t r = colors[i].r;
      uint8_t g = colors[i].g;
      uint8_t b = colors[i].b;
    }
    SDL_UpdateRect(s, 0, 0, 0, 0);
  }
}

static void ConvertPixelsARGB_ABGR(void *dst, void *src, int len) {
  int i;
  uint8_t (*pdst)[4] = dst;
  uint8_t (*psrc)[4] = src;
  union {
    uint8_t val8[4];
    uint32_t val32;
  } tmp;
  int first = len & ~0xf;
  for (i = 0; i < first; i += 16) {
#define macro(i) \
    tmp.val32 = *((uint32_t *)psrc[i]); \
    *((uint32_t *)pdst[i]) = tmp.val32; \
    pdst[i][0] = tmp.val8[2]; \
    pdst[i][2] = tmp.val8[0];

    macro(i + 0); macro(i + 1); macro(i + 2); macro(i + 3);
    macro(i + 4); macro(i + 5); macro(i + 6); macro(i + 7);
    macro(i + 8); macro(i + 9); macro(i +10); macro(i +11);
    macro(i +12); macro(i +13); macro(i +14); macro(i +15);
  }

  for (; i < len; i ++) {
    macro(i);
  }
}

SDL_Surface *SDL_ConvertSurface(SDL_Surface *src, SDL_PixelFormat *fmt, uint32_t flags) {
  assert(src->format->BitsPerPixel == 32);
  assert(src->w * src->format->BytesPerPixel == src->pitch);
  assert(src->format->BitsPerPixel == fmt->BitsPerPixel);

  SDL_Surface* ret = SDL_CreateRGBSurface(flags, src->w, src->h, fmt->BitsPerPixel,
    fmt->Rmask, fmt->Gmask, fmt->Bmask, fmt->Amask);

  assert(fmt->Gmask == src->format->Gmask);
  assert(fmt->Amask == 0 || src->format->Amask == 0 || (fmt->Amask == src->format->Amask));
  ConvertPixelsARGB_ABGR(ret->pixels, src->pixels, src->w * src->h);

  return ret;
}

uint32_t SDL_MapRGBA(SDL_PixelFormat *fmt, uint8_t r, uint8_t g, uint8_t b, uint8_t a) {
  assert(fmt->BytesPerPixel == 4);
  uint32_t p = (r << fmt->Rshift) | (g << fmt->Gshift) | (b << fmt->Bshift);
  if (fmt->Amask) p |= (a << fmt->Ashift);
  return p;
}

int SDL_LockSurface(SDL_Surface *s) {
  return 0;
}

void SDL_UnlockSurface(SDL_Surface *s) {
}
