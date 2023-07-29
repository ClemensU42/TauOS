
__attribute__((noreturn))
void exception_handler(void);
void exception_handler(void){
    asm("cli");
    asm("hlt");
}