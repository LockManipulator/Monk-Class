GETTER_VAR(void*, ASMflamerush_jmpback);
GETTER_VAR(void*, ASMAddBuff);
GETTER_VAR(void*, ASMcheck_for_customclass_jmpback);
GETTER_VAR(void*, ASMcheck_customclass_success);
GETTER_VAR(void*, ASMspecbyteret);
GETTER_VAR(void*, ASMspecbyteret_success);

//cube::Creature::Buff* ASMBuffPtr;

__attribute__((naked)) void ASMflamerushWhileRunning() {
	asm(".intel_syntax \n"
		PUSH_ALL
		"mov rax,[r13+0x08] \n"
		"mov rcx,[rax+0x448] \n"

		"cmp byte ptr [rcx+0x14C], 5 \n"
		"jne ASMflamerush_lbl \n"

		// "mov rdx, [ASMBuffPtr] \n" //Buff
		// "mov r8, 0x01 \n"
		// "call [ASMAddBuff] \n"
		"mov byte ptr [rcx+0x68], 0x92 \n" //Ability


		POP_ALL

		DEREF_JMP(ASMflamerush_jmpback)

		"ASMflamerush_lbl: \n"

		POP_ALL

		"mov rax,[r13+0x08] \n"
		"mov rcx,[rax+0x448] \n"
		"mov byte ptr [rcx+0x68],0x51 \n"
		DEREF_JMP(ASMflamerush_jmpback)
		".att_syntax \n"
	);
}

__attribute__((naked)) void ASMcheck_for_customclass() {
	asm(".intel_syntax \n"
		"mov rcx, [rax+0x448] \n"
		"cmp byte ptr [rcx+0x14C], 5 \n"
		"jne ASMcustomclasslbl \n"

		DEREF_JMP(ASMcheck_customclass_success)

		"ASMcustomclasslbl: \n"
		"cmp byte ptr [rcx+0x14C], 4 \n"
		DEREF_JMP(ASMcheck_for_customclass_jmpback)
		".att_syntax \n"
	);
}

__attribute__((naked)) void ASMspecbyte() {
	asm(".intel_syntax \n"
		"cmp byte ptr [rcx+0x14C], 5 \n"
		"jne nochangebytelbl \n"
		"cmp byte ptr [rcx+0x14D], 0 \n"
		DEREF_JMP(ASMspecbyteret_success)

		"nochangebytelbl: \n"
		"cmp byte ptr [rcx+0x14D], 1 \n"
		DEREF_JMP(ASMspecbyteret)
		".att_syntax \n"
	);
}

void change_spec_byte() {
	char* base = (char*)CWBase();
	int offset = 0x8F2BA;
	WriteByte(base + offset, 0xE9);
	WriteByte(base + offset + 0x01, 0x60);
	WriteByte(base + offset + 0x02, 0xFD);
	WriteByte(base + offset + 0x03, 0xFC);
	WriteByte(base + offset + 0x04, 0xFF);
	WriteByte(base + offset + 0x05, 0x90);
	WriteByte(base + offset + 0x06, 0x90);
}

void hook_spec_byte() {
	char* base = (char*)CWBase();
	WriteFarJMP(Offset(base, 0x5F01F), (void*)&ASMspecbyte);
	ASMspecbyteret = (base + 0x8F2C1);
	ASMspecbyteret_success = (base + 0x8F2DB);
}

void add_flamerush() {
	char* base = (char*)CWBase();
	WriteFarJMP(Offset(base, 0x8F33A), (void*)&ASMflamerushWhileRunning);
	ASMflamerush_jmpback = (base + 0x8F349);
	//ASMAddBuff = (base + 0x65390);

	//ASMBuffPtr = (cube::Creature::Buff*)new char[sizeof(cube::Creature::Buff)];
	//ASMBuffPtr->type = cube::Creature::Buff::BuffType::AuraFlameRush;
	//ASMBuffPtr->unk = 0.5f;
	//ASMBuffPtr->time_remaining = 1000.0f;
}

void check_for_customclass() {
	char* base = (char*)CWBase();
	WriteFarJMP(Offset(base, 0x8F2AA), (void*)&ASMcheck_for_customclass);
	ASMcheck_for_customclass_jmpback = (base + 0x8F2B8);
	ASMcheck_customclass_success = (base + 0x8f2BA);
}

void hook_flamerush() {
	change_spec_byte();
	hook_spec_byte();
	check_for_customclass();
	add_flamerush();
}
/*
this second hook, the check_for_customclass, just changes the check from 4 (rogue) to customclass (5).
hook_spec_byte changes it so that flame rush is for specialization 0
*/

//flame rush = 146
//action state offset = 68

//96EBC i forgot what this is because i forgot to write a comment for it :(
//97875 same as above
//9531A hook to write own functions for unequip?? might be outdated info
//9CD6 unequip bow with boomerang (and other things too I think)
//9CE1 accesses left weapon slot when i have a crossbow equipped and i click a bow. also, when bow is equipped and I click a mace (mov [rcx+04], eax).
//8C16A compares with ranger weapons
