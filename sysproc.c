#include "types.h"
#include "x86.h"
#include "defs.h"
#include "date.h"
#include "param.h"
#include "memlayout.h"
#include "mmu.h"
#include "proc.h"

int sys_fork(void) {
  return fork();
}

int sys_exit(void) {
  int status;

  if(argint(0, &status) < 0)
      return -1;
  else {
      exit(status);
      return 0;  // not reached
  }
}

int sys_wait_stat(void) {
    int status;
    int performance;
    int pid;


    if (argint(0, &status) < 0)
      return -1;
    if (argint(1, &performance) < 0)
      return -1;


    pid = wait_stat((int*)status, (struct perf*) performance); 
    return pid;
  
}

int sys_wait(void) {
  int status;
    if (argint(0, &status) < 0)
      return -1;
    else 
      return wait((int *)status);
}

int sys_priority(void) {
  int p;
    if (argint(0, &p) < 0)
      return -1;
    else {
      priority(p);
      return 0;
    }
}

int sys_policy(void) {
  int p;
    if (argint(0, &p) < 0)
      return -1;
    policy(p);
    return 0;
}



int sys_kill(void) {
  int pid;

  if(argint(0, &pid) < 0)
    return -1;
  return kill(pid);
}

int sys_getpid(void) {
  return proc->pid;
}

int sys_sbrk(void) {
  int addr;
  int n;

  if(argint(0, &n) < 0)
    return -1;
  addr = proc->sz;
  if(growproc(n) < 0)
    return -1;
  return addr;
}

int sys_sleep(void) {
  int n;
  uint ticks0;

  if(argint(0, &n) < 0)
    return -1;
  acquire(&tickslock);
  ticks0 = ticks;
  while(ticks - ticks0 < n){
    if(proc->killed){
      release(&tickslock);
      return -1;
    }
    sleep(&ticks, &tickslock);
  }
  release(&tickslock);
  return 0;
}

// return how many clock tick interrupts have occurred
// since start.
int sys_uptime(void) {
  uint xticks;

  acquire(&tickslock);
  xticks = ticks;
  release(&tickslock);
  return xticks;
}


