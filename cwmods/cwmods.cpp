#define MOD_MAJOR_VERSION 4
#define MOD_MINOR_VERSION 2

#include "cwmods.h"
#include <windows.h>

void* moduleBase;

void* CWBase(){
    return moduleBase;
}

EXPORT void ModPreInitialize(){
    moduleBase = GetModuleHandle(NULL);
}

EXPORT int ModMajorVersion(){
    return MOD_MAJOR_VERSION;
}

EXPORT int ModMinorVersion(){
    return MOD_MINOR_VERSION;
}

void WriteByte(void* location, char val){
	DWORD dwOldProtection;
	VirtualProtect(location, 1, PAGE_EXECUTE_READWRITE, &dwOldProtection);
    *(char*)location = val;
	VirtualProtect(location, 1, dwOldProtection, &dwOldProtection);
}

void WriteFarJMP(void* source, void* destination) {
    DWORD dwOldProtection;
    VirtualProtect(source, 14, PAGE_EXECUTE_READWRITE, &dwOldProtection);
    char* location = (char*)source;

    // Far jump
    *((UINT16*)&location[0]) = 0x25FF;

    // mode
    *((UINT32*)&location[2]) = 0x00000000;

    *((UINT64*)&location[6]) = (UINT64)destination;

    VirtualProtect(location, 14, dwOldProtection, &dwOldProtection);
}

__declspec(noinline) void* operator new(size_t size) {
    return ((void*(*)(size_t))CWBase()+0x392BAC)(size);
}
__declspec(noinline) void* operator new[](size_t size) {
    return ((void*(*)(size_t))CWBase()+0x392BAC)(size);
}

__declspec(noinline) void operator delete(void* ptr) noexcept {
    ((void(*)(void*))CWBase()+0x392BE8)(ptr);
}
__declspec(noinline) void operator delete[](void* ptr) noexcept {
    ((void(*)(void*))CWBase()+0x392BE8)(ptr);
}
