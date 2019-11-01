#include "userprog/syscall.h"
#include <stdio.h>
#include <syscall-nr.h>
#include "threads/interrupt.h"
#include "threads/thread.h"
#include "devices/shutdown.h"
#include "lib/user/syscall.h"
static void syscall_handler (struct intr_frame *);

void
syscall_init (void) 
{
  intr_register_int (0x30, 3, INTR_ON, syscall_handler, "syscall");
}

static void
syscall_handler (struct intr_frame *f UNUSED) 
{
  //1101 형준
  //printf("syscall num : %d\n", *(uint32_t *)(f->esp));
  switch(*(uint32_t *)(f->esp)){
    case SYS_HALT://
      sys_halt();
      break;
    case SYS_EXIT://

      break;
    case SYS_EXEC://
      break;
    case SYS_WAIT://
      break;
    case SYS_CREATE:
      break;
    case SYS_REMOVE:
      break;
    case SYS_OPEN:
      break;
    case SYS_FILESIZE:
      break;
    case SYS_READ://
      break;
    case SYS_WRITE://
      break;
    case SYS_SEEK:
      break;
    case SYS_TELL:
      break;
    case SYS_CLOSE:
      break;
      /*
    case SYS_PIBONACCI:
      break;
    case SYS_SUM:
      break;
      */
     default:
      printf("\nsyscall error\n");
  }
  //

  printf ("system call!\n");
  thread_exit ();
}

void sys_halt(void){
  shutdown_power_off();
}
void sys_halt(void){

}
void sys_exit(int status){

}
int sys_write(int fd, const void *buffer, unsigned size){

}
int sys_read(int fd, void* buffer, unsigned size){

}
int sys_wait(pid_t pid){

}
pid_t sys_exec(const char *cmd_line){

}