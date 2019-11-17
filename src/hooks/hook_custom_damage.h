void hook_customclass_damage() {

}
/*
GETTER_VAR(void*, update_damage_retn);
GETTER_VAR(float*, max_hp);

extern "C" float* get_max_hp() {
	return max_hp;
}

__attribute__((naked)) void ASMGetHP() {
	asm(".intel_syntax \n"
		"movaps xmm0, xmm6 \n"
		"movaps xmm6, [rsp+0x20] \n"
		"add rsp, 0x30 \n"

		"cmp byte ptr [rbx+0x60], 0 \n"
		"jne ASMFixDamage_skip \n"

		"push rax \n"
		"call get_max_hp \n"
		"movaps [rax], xmm0 \n"
		"pop rax \n"

		"ASMFixDamage_skip: \n"

		"pop rbx \n" // Pop rbx after, because we need it for the player check.

		"ret \n"
		".att_syntax \n"
	);
}

__attribute__((naked)) void ASMUpdateDamage() {
	asm(".intel_syntax \n"
		"movaps xmm6, [rsp+0x70] \n"
		"movaps xmm7, [rsp+0x60] \n"
		"mov rsp, r11 \n"
		"pop r14 \n"

		"cmp byte ptr [rsi+0x60], 0 \n"
		"jne ASMUpdateDamageSkip \n"

		PUSH_ALL
		"call get_max_hp \n" //Load max_hp float pointer
		"movq rdi, xmm1 \n" //save xmm1
		"movq rbx, xmm2 \n" //save xmm2
		"movq xmm1, [rax] \n" //put max_hp into xmm1
		"mov rax, 0x3d75c28f \n"//Set rax to 0.06 (6%)
		"movq xmm2, rax \n" //Set xmm2 to rax
		"mulss xmm1, xmm2 \n" //multiply max_hp by 0.06
		"addss xmm0, xmm1 \n" //add (max_hp * 0.06) to our base damage
		"movq xmm1, rdi \n" //restore xmm1
		"movq xmm2, rbx \n" //restore xmm2
		POP_ALL

		// PUSH_ALL
		// "call get_max_hp \n"
		// "addss xmm0, [rax] \n" //Add float from pointer to base damage
		// "movq rdi, xmm1 \n" //Store xmm1
		// "mov rax, 0x3d75c28f \n"//Set rax to 0.06 (6%)
		// "movq xmm1, rax \n" //Set xmm1 to rax
		// "mulss xmm0, xmm1 \n" //Multiply the damage by xmm1 (0.06)
		// "movq xmm1, rdi \n" //Reset xmm1
		// POP_ALL

		"ASMUpdateDamageSkip: \n"
		DEREF_JMP(update_damage_retn)
		".att_syntax \n"
	);
}

void get_hp() {
	char* base = (char*)CWBase();
	WriteFarJMP(Offset(base, 0x5FC11), (void*)&ASMGetHP);
	max_hp = (float*) new char[4];
}

void update_damage() {
	char* base = (char*)CWBase();
	WriteFarJMP(Offset(base, 0x4FD2B), (void*)&ASMUpdateDamage);
	update_damage_retn = (base + 0x4FD3A);
}

void hook_customclass_damage() {
	get_hp();
	update_damage();
}
*/