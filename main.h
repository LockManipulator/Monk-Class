#ifndef MAIN_H
#define MAIN_H

#include <vector>

#define no_optimize __attribute__((optimize("O0")))

void Popup(const char* title, const char* msg);

#define PUSH_ALL "push rax\npush rbx\npush rcx\npush rdx\npush rsi\npush rdi\npush rbp\npush r8\npush r9\npush r10\npush r11\npush r12\npush r13\npush r14\npush r15\n"
#define POP_ALL "pop r15\npop r14\npop r13\npop r12\npop r11\npop r10\npop r9\npop r8\npop rbp\npop rdi\npop rsi\npop rdx\npop rcx\npop rbx\npop rax\n"

#define PREPARE_STACK "mov rax, rsp \n and rsp, 0xFFFFFFFFFFFFFFF0 \n push rax \n sub rsp, 0x28 \n"
#define RESTORE_STACK "add rsp, 0x28 \n pop rsp \n"


// These macros exist because "jmp [var]" or "jmp ds:[var]" and any other variants I have tried do not properly compile
#define GETTER_VAR(vartype, varname)\
	static __attribute__((used)) vartype varname;\
	extern "C" vartype Get_##varname(){return varname;}
#define DEREF_JMP(varname)\
	"sub rsp, 8 \n"\
	"push rax \n"\
	"call Get_"#varname" \n"\
	"mov [rsp+8], rax \n"\
	"pop rax \n"\
	"ret \n"

void* Offset(void* x1, uint64_t x2);

#endif // MAIN_H