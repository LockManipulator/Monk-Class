GETTER_VAR(void*, ASMUltimateInsert_jmpback);
GETTER_VAR(void*, ASMAdd_Ult);

void go_to_cave() {
	char* base = (char*)CWBase();
	int offset = 0x29D6E4;
	WriteByte(base + offset, 0xE9);
	WriteByte(base + offset + 0x01, 0x18);
	WriteByte(base + offset + 0x02, 0x2C);
	WriteByte(base + offset + 0x03, 0xDB);
	WriteByte(base + offset + 0x04, 0xFF);
}

//3501CF - draw text :omegalul:

extern "C" float get_max_hp() {
	return cube::GetGame()->GetPlayer()->GetMaxHP();
}

__attribute__((naked)) void ASMUltimateInsert() {
	asm(".intel_syntax \n"
		"cmp byte ptr [rdi+0x14C], 5 \n"
		"jne  ASMUltimateInsert_jmpback_lbl \n"

		PUSH_ALL
		/*
		"call get_max_hp \n"
		"mov rax, [rax] \n"
		"mov [rdi+0x180], eax \n"
		*/

		"movq rbx, xmm0 \n"
		"call get_max_hp \n"
		"movq rax, xmm0 \n"
		"mov [rdi+0x180], eax \n"
		"movq xmm0, rbx \n"

		POP_ALL

		DEREF_JMP(ASMUltimateInsert_jmpback)

		"ASMUltimateInsert_jmpback_lbl: \n"
		DEREF_JMP(ASMAdd_Ult) //supposed to be call, does that matter?
		DEREF_JMP(ASMUltimateInsert_jmpback)
		".att_syntax \n"

	);
}

void customclass_ultimate_insert() {
	char* base = (char*)CWBase();
	WriteFarJMP(Offset(base, 0x50301), (void*)&ASMUltimateInsert);
	ASMUltimateInsert_jmpback = (base + 0x29D6E9); //if not villager
	ASMAdd_Ult = (base + 0x65390); //after all done
}

void hook_customclass_new_ultimate() {
	customclass_ultimate_insert();
	go_to_cave();
}