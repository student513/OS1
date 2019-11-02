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
syscall_handler (struct intr_frame *f) 
{
  //1101 형준
  void * temp_esp = f->esp;
  //printf("syscall num : %d\n", *(uint32_t *)(temp_esp));//check
  //printf("f->esp : %x\n",f->esp);//check
  //hex_dump(f->esp, f->esp, 100, 1);//check

  switch(*(uint32_t *)(temp_esp)){
    case SYS_HALT://
      sys_halt();
      break;
    case SYS_EXIT://
      //(is_user_vaddr(f->esp + 4)) ? NULL:exit(-1); 
      sys_exit((int)*(uint32_t *)(f->esp + 4));
      break;
    case SYS_EXEC://
      //(is_user_vaddr(f->esp + 4)) ? NULL:exit(-1);
      sys_exec((const char)*(uint32_t *)(f->esp + 4));
      break;
    case SYS_WAIT://
      sys_wait((pid_t)*(uint32_t *)(f->esp + 4));
      break;
    case SYS_CREATE://prj2
      break;
    case SYS_REMOVE://prj2
      break;
    case SYS_OPEN://prj2
      break;
    case SYS_FILESIZE://prj2
      break;
    case SYS_READ://
      //(is_user_vaddr(f->esp + 4)) ? NULL:exit(-1);
      //(is_user_vaddr(f->esp + 8)) ? NULL:exit(-1);
      //(is_user_vaddr(f->esp + 12)) ? NULL:exit(-1);
      sys_write((int)*(uint32_t *)(temp_esp+4),(void*)*(uint32_t *)(temp_esp+8),(unsigned)*(uint32_t *)(temp_esp+12));
      
      break;
    case SYS_WRITE://
      
      sys_write((int)*(uint32_t *)(temp_esp+4),(void*)*(uint32_t *)(temp_esp+8),(unsigned)*(uint32_t *)(temp_esp+12));
      break;
    case SYS_SEEK://prj2
      break;
    case SYS_TELL://prj2
      break;
    case SYS_CLOSE://prj2
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

  //printf ("system call!\n");
  //thread_exit ();
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
  if(fd == 1){
    putbuf(buffer,size);
  }
  return (int)size;
}
int sys_read(int fd, void* buffer, unsigned size){
  int i=0;
  uint8_t check;
  if(fd ==0){
    for(i=0;i<(int)size;i++){
      check = input_getc();
      if(!check) break;
    }
  }
}
int sys_wait(pid_t pid){
  return process_wait(pid);
}
pid_t sys_exec(const char *cmd_line){
  return process_execute(cmd_line); 
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