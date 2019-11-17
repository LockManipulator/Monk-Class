GETTER_VAR(void*, ASMNoMpDrain_jmpback);

__attribute__((naked)) void ASMNoMpDrain() {
	asm(".intel_syntax \n"
		"movaps xmm1, xmm10 \n"

		"cmp byte ptr [r13+0x14C], 5 \n"
		"jne ASMVillgerNoMpDrain_no_customclass_lbl \n"

		"push rax \n"
		"mov rax, 0x00000000 \n"
		"movq xmm12, rax \n"
		"pop rax \n"

		"ASMVillgerNoMpDrain_no_customclass_lbl: \n"
		"mulss xmm1, xmm12 \n"
		"movss xmm0, [r13+0x188] \n"
		DEREF_JMP(ASMNoMpDrain_jmpback)
		".att_syntax \n"
	);
}

void customclass_no_mp_drain() {
	char* base = (char*)CWBase();
	WriteFarJMP(Offset(base, 0x2DFDBC), (void*)&ASMNoMpDrain);
	ASMNoMpDrain_jmpback = (base + 0x2DFDCE);
}

void hook_customclass_no_mp_drain() {
	customclass_no_mp_drain();
}