#ifndef __MAIN_H__
#define __MAIN_H__

#include <windows.h>

/*  To use this exported function of dll, include this header
 *  in your project.
 */

#define no_optimize __attribute__((optimize("O0")))

#define PUSH_ALL "push rax\npush rbx\npush rcx\npush rdx\npush rsi\npush rdi\npush rbp\npush r8\npush r9\npush r10\npush r11\npush r12\npush r13\npush r14\npush r15\n"
#define POP_ALL "pop r15\npop r14\npop r13\npop r12\npop r11\npop r10\npop r9\npop r8\npop rbp\npop rdi\npop rsi\npop rdx\npop rcx\npop rbx\npop rax\n"

#define PREPARE_STACK "mov rax, rsp \n and rsp, 0xFFFFFFFFFFFFFFF0 \n push rax \n sub rsp, 0x28 \n"
#define RESTORE_STACK "add rsp, 0x28 \n pop rsp \n"

#ifdef BUILD_DLL
    #define DLL_EXPORT __declspec(dllexport)
#else
    #define DLL_EXPORT __declspec(dllimport)
#endif


#ifdef __cplusplus
extern "C"
{
#endif

#ifdef __cplusplus
}
#endif

#endif // __MAIN_H__
