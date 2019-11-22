#include <ctime>    // For time()
#include <cstdlib>  // For srand() and rand()

GETTER_VAR(void*, ASMTreasure_ret_1);
GETTER_VAR(void*, ASMTreasure_ret_2);
GETTER_VAR(void*, ASMTreasure_ret_3);
GETTER_VAR(void*, ASMTreasure_ret_4);
GETTER_VAR(void*, ASMTreasure_jmpback);

extern "C" int get_rand_treasure() {
	srand(time(0));  // Initialize random number generator.
	return (rand() % 4) + 1;
}

__attribute__((naked)) void ASMRandomTreasure() {
	asm(".intel_syntax \n"
		"cmp ecx, 5 \n"
		"jne monk_treasure_lbl \n"

		PUSH_ALL
		PREPARE_STACK

		"call get_rand_treasure \n"

		RESTORE_STACK

		"mov [rsp+0x60], rax \n"

		POP_ALL

		"monk_treasure_lbl: \n"
		"sub ecx, 1 \n"
		"jz treasure_ret_1_lbl \n"
		"sub ecx, 1 \n"
		"jz treasure_ret_2_lbl \n"
		DEREF_JMP(ASMTreasure_jmpback)

		"treasure_ret_1_lbl: \n"
		DEREF_JMP(ASMTreasure_ret_1)

		"treasure_ret_2_lbl: \n"
		DEREF_JMP(ASMTreasure_ret_2)

		".att_syntax \n"
	);
}


void treasure_fix() {
	char* base = (char*)CWBase();
	WriteFarJMP(Offset(base, 0x10A7FE), (void*)&ASMRandomTreasure);
	ASMTreasure_jmpback = (base + 0x10A810);
	ASMTreasure_ret_1 = (base + 0x10AB70);
	ASMTreasure_ret_2 = (base + 0x10AA60);
	ASMTreasure_ret_3 = (base + 0x10A933);
	ASMTreasure_ret_4 = (base + 0x10AD17);
}