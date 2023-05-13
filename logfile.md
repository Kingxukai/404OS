1：
    **issue:    "relocation truncated to fit:R RISCV_HI20 against ..."**
    time:    2023-04-20 12:40:20 by wxk

    solution:
    add a instruction to common.mk "-mcmodel=medany"

2：
   **issue:    "turn to trap while execute 'MRET' in machine mode and get a tips 'Illegal instruction'"**
    time:    2023-04-27 20:40:38 by wxk

    solution:
    add some instruction to BOOT/boot.s
    "
        li      t0, 0xffffffff
        csrw    pmpaddr0, t0
        li      t0, 0xf
        csrw    pmpcfg0, t0
    "
    here refer "    
        # https://lore.kernel.org/qemu-devel/20201223192553.332508-1-atish.patra@wdc.com/
        # For qemu version >= 6.0, exception would be raised if no PMP enty is
        # configured. So just configure one entny, which allows all the whole
        # 32-bits physical address range is R/W/X.
        # FIXME: I say it is a temporary workaroud due to I think the patch
        # above contains bug, and I have raised new issue to qemu but it has not
        # been rootcaused till now. Details please refer to
        # https://gitlab.com/qemu-project/qemu/-/issues/585 or
        # https://gitee.com/unicornx/riscv-operating-system-mooc/issues/I441IC (in chinese)
        # So it's just a temporary workaround till now to not block people who
        # want to try newer qemu (>= 6.0)."
        thanks all above

3:
    **add "user-mode"**
    time:    2023-04-27 20:40:38 by wxk

4:
   **add "syscall"**
    time:2023-04-28 15:10:38 by wxk

```
comment:althougn maybe it not always get the right answer...
however I actually try to complete the syscall...
In the next step I'll try to correct it
```

5:
   **issue: "the ret_num of syscall not right"**
    time:2023-04-28 16:18:38 by wxk

    solution:
    I ignored the *(fn)() and thought the ret_num = *(fn),which is the address of syscall function, and noticed it through GDB.

6:
   **add "software timer"**
    time:2023-04-28 19:06:28 by wxk

7:
    **add and modify: "add_timer,timer_list,do_timer"**
    time:2023-04-28 20:33:51 by wxk

8:
    **add "syscall:getpid()" and modify the error of Makefile in file manage**
    time:2023-04-29 18:03:12 by wxk

9：
    **add "syscall:getppid()"**
    time:2023-04-29 22:52:30 by wxk

10:
   **issue "encounter unexpected error while use fork() to replace with copy_process() in task0,and the whole system paused"and add "syscall:fork()"**
    time:2023-04-30 00:13:05 by wxk

    solution:
    delete an instruction in copy_process(),which caused thar error
    However, it spent me a lot time tracing the process step by step through GDB, and is always be ignored in writing text.

11:
    **issue "encounter an unexpected error while execute set_Queue() 5th,the value of register a1 was random"and modify "fork()",so it can be invoked as same as Linux.**
    time:2023-05-01 22:30:56 by wxk

    solution:
    I traced the program and noticed that the order will be added to 6,which is greater than 5.Because we only set an arrary with 5 space.
    so stupid..hh

12:
   **modify "define syscall with macro,and change the fork()"**
    time:2023-05-03 02:20:38 by wxk

    comment:Ok,let's talk about the classic syscall——fork,which is invoked to create a new process,and get new pid as return value in father process while get 0 return number in child process. How can I implement it?
    Actually,I let child process's mepc = father's mepc + 1,so that the child process can skip 'ecall',and return 0 directly.
    However,there is still a problem that I haven't tackled it,which surprises me with that it can be correctly execute if I add 'registed' attribute instead of only 'pid_t'.I think is stack's problem. I'll modify it next step.

13:
    **modify "fork()"**
    time:2023-05-03 14:40:29 by wxk

    comment:All right,I finally found the problem, which troubled me. When it comes to fork, we always say it will return two value,one is new pid,and another is 0. But how can I get it? Acutually, the reason why fork can return two value is that the new process almost copy the father process's context,including ra,stack,tp,gp...And we set a0 to 0 and mepc+4,so the new process won't execute 'ecall' and return 0 while father process have to execute ecall to invoke copy_process to get a new pid to return. Don't forget to copy the stack of father process,because the child process will execute the same step of father process.
    
    solution,in last comment, I said that there's a problem that the local variable will be edited but using 'register'. I try to solve the problem through GDB. And I noticed that the s0 of new process unexpected to be 0, so I thought that's the compiler's problem. After a moment,I found that the child process can't execute the same step because of different stack space. oh!!!That's the reason, copying the stack space of father is neccessary.

14:
   **add "syscall:execve and exit"**
    time:2023-05-03 17:06:57 by wxk

15:
    **modify "syscall:execve and modify the macro of syscall to make it be compatible with void function(no return)"**
    time:2023-05-04 23:34:08 by wxk

    comment:I have a trial run almost a day because of some problem in the execve in order to simlify the original syscall——'execute' in Linux.

16:
   **ignored the page_alloc in 'copy_process',which should to be modified to malloc..**
    time:2023-05-05 22:45:44 by wxk

17:
    **add signal of process and modify the wait() and waitpid()**
    time2023-05-13 16:38:25 by wxk

```
comment:however,I'm still not clear how can process excute the code after invoking schedule() in waitpid(), because there's no any step to save the context of current process,and next time current process was executing, the mepc will make PC point to ecall in sys_waitpid() instead of the code after invoking schedule() after waitpid()
```