GETTER_VAR(void*, ASMUltimateActionInsert_jmpback);
GETTER_VAR(void*, ASMUltimateActionInsert_oldCode_jmp);
GETTER_VAR(void*, ASMUltimateActionInsert_zero_return_jmp);

__attribute__((naked)) void ASMUltimateActionInsert() {
	asm(".intel_syntax \n"
		"jz ASMUltimateActionInsert_oldCode_lbl \n"
		"sub edx, 1 \n"
		"je ASMUltimateActionInsert_rogue_lbl \n"
		"cmp edx, 1 \n"
		"jnz ASMUltimateActionInsert_zero_return_lbl \n"
		// Class = 5, aka villager
		"mov eax, 0x6D \n"
		"ret \n"

		"ASMUltimateActionInsert_zero_return_lbl: \n"
		DEREF_JMP(ASMUltimateActionInsert_zero_return_jmp)

		"ASMUltimateActionInsert_rogue_lbl: \n"
		"cmp [rcx+0x14D], r8b \n"
		DEREF_JMP(ASMUltimateActionInsert_jmpback)

		"ASMUltimateActionInsert_oldCode_lbl: \n"
		DEREF_JMP(ASMUltimateActionInsert_oldCode_jmp)
		".att_syntax \n"
	);
}

void customclass_action_insert() {
	char* base = (char*)CWBase();
	WriteFarJMP(Offset(base, 0x656F7), (void*)&ASMUltimateActionInsert);
	ASMUltimateActionInsert_jmpback = (base + 0x65705);
	ASMUltimateActionInsert_oldCode_jmp = (base + 0x65717);
	ASMUltimateActionInsert_zero_return_jmp = (base + 0x65713);
}

void hook_customclass_ultimate() {
	customclass_action_insert();
}
