
extern char *__bss, *__bss_end, *__stack_top;

void memset(char *begin, char c, unsigned int n)
{
    for (unsigned int i=0;i<n;i++) {
        *(begin + i) = c;
    }
}

void main(void) 
{
    memset((char *)__bss, 0, (__bss_end - __bss));

    while(1);
}

__attribute__((section(".text.boot")))
__attribute__((naked))
void boot(void) {
    __asm__ __volatile__(
        "mv sp, %0\n"
        "j main\n"
        :
        : "r"(__stack_top)
    );
}
