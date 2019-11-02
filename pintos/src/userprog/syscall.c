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

     // sys_exit();
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
      /*191102 inseok*/
    case SYS_FIBONACCI:
      break;
    case SYS_SUM4:
      break;
      /**/
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

void sys_exit(int status){
  struct thread *current_t = thread_current();
  current_t -> exit_status = status;//success.  (nonzero == fail to exit)
  printf("%s: exit(%d)\n", thread_name(), status);
  thread_exit();
}
int sys_write(int fd, const void *buffer, unsigned size){

}
int sys_read(int fd, void* buffer, unsigned size){

}
int sys_wait(pid_t pid){

}
pid_t sys_exec(const char *cmd_line){

}

/*20191102 inseok : functions included*/
int sys_fibonacci(int n){//Return N th value of Fibonacci sequence
  int a = 0,b = 1,ans = 0, i;
  
  if(n==0)
    return 0;
  else if(n==1)
    return 1;
  for(i=2;i<n;i++){
    ans=a+b;
    a=b;
    b=ans;
  }
  return ans;
}
int sys_sum4(int a, int b, int c, int d){//Return the sum of a, b, c and d
  return a+b+c+d;
}
/**/