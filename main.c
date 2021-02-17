#define _XOPEN_SOURCE 700
#include <signal.h>
#include <unistd.h>
#include <string.h>
#include <errno.h>
#include <execinfo.h>

unsigned char stBuff[10240];
void handler(int sig)
{

        void *bt[1024];
        int bt_size;
        char **bt_syms;
        int i;

        bt_size = backtrace(bt, 1024);
        bt_syms = backtrace_symbols(bt, bt_size);

        for (i = 1; i < bt_size; i++) {
                size_t len = strlen(bt_syms[i]);
                write(2, bt_syms[i], len);
                write(2, "\n", 1);
        }

    write(2, "stack overflow\n", 15);
    _exit(1);
}
int lvl=0;
unsigned infinite_recursion(unsigned x) {
    lvl=lvl+1;
    while(lvl==5) {
        int i=2;
        }
    return infinite_recursion(x)+1;
}
int main()
{
    static char stack[SIGSTKSZ];
    stack_t ss = {
        .ss_size = SIGSTKSZ,
        .ss_sp = stack,
    };
    struct sigaction sa = {
        .sa_handler = handler,
        .sa_flags = SA_ONSTACK
    };
    sigaltstack(&ss, 0);
    sigfillset(&sa.sa_mask);
    sigaction(SIGALRM, &sa, 0);
    //sigaction(SIGSEGV, &sa, 0);
    alarm(2);
    while(0) {
        int i=2;
        }
    infinite_recursion(0);
}