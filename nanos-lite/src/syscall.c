#include <common.h>
#include "syscall.h"
#include<sys/time.h>
#include <proc.h>

int sys_execve(const char *fname, char * const argv[], char *const envp[]);
int sys_write(int fd, void *buf, size_t count);
int fs_close(int fd);
int fs_open(const char* pathname,int flags);
size_t fs_read(int fd,void* buf,size_t len);
size_t fs_lseek(int fd,size_t offset,int whence);
size_t fs_write(int fd,const void *buf,size_t len);
void naive_uload(PCB *pcb, const char *filename);
int sys_gettimeofday(struct timeval *tv,struct timezone *tz);
void sys_yield(Context *c){
  yield();
  c->GPRx=0;
}
void sys_exit(Context *c){
  //halt(c->GPR2);//wait to modify
  sys_execve("/bin/menu",NULL,NULL);
}

void do_syscall(Context *c) {

  uintptr_t a[4];
  a[0] = c->GPR1;
  a[1]=c->GPR2;
  a[2]=c->GPR3;
  a[3]=c->GPR4;
  //Log("you caused a write_syscall!!");
    switch (a[0]) {
      case SYS_yield:/*Log("you caused a yield_syscall!!");*/sys_yield(c);break;
      case SYS_exit:/*Log("you caused a exit_syscall!!");*/sys_exit(c);break;
      case SYS_write:c->GPRx=fs_write(a[1],(void*)a[2],a[3]); break;
      //case SYS_write:c->GPRx=sys_write(a[1],(void*)a[2],a[3]); break;
      case SYS_brk: /*Log("you caused a brk_syscall!!");*/c->GPRx=0;break;
      case SYS_open:/*Log("you casued a open_syscall!!");*/c->GPRx=fs_open((char*)a[1],a[2]);break;
      case SYS_close:/*Log("you casued a close_syscall!!");*/c->GPRx=fs_close(a[1]);break;
      case SYS_read:c->GPRx=fs_read(a[1],(void*)a[2],a[3]);break;
      case SYS_lseek:c->GPRx=fs_lseek(a[1],a[2],a[3]);break;
      case SYS_gettimeofday:c->GPRx=sys_gettimeofday((struct timeval*)a[1],(struct timezone*)a[2]);break;
      case SYS_execve:c->GPRx=sys_execve((char*)a[1],(char**)a[2],(char**)a[3]);break;
    default: panic("Unhandled syscall ID = %d", a[0]);
  }
}//Log("you casued a timer_syscall!!");
//Log("you casued a lseek_syscall!!");
//Log("you casued a read_syscall!!");

int sys_execve(const char *fname, char * const argv[], char *const envp[]){
  int flag=fs_open(fname,0);
  printf("filename:%s\n",fname);
  if(flag==-1)return -1;
  else{
    naive_uload(NULL,fname);//wait to be modify
    return 0;
  }
}
int sys_write(int fd, void *buf, size_t count){
  if(fd==1||fd==2){
    char* buff=(char*)buf;
    for(int i=0;i<count;i++) putch(buff[i]); 
  }
  return count;
}
