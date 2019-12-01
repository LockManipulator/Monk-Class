GETTER_VAR(void*, ASMFixInvis_jmpback);

//3501CF - draw text :omegalul:

extern "C" float load_invis_time() {
	cube::Creature* player = cube::GetGame()->GetPlayer();
	if (player->entity_data.classType == 5) {
		player->entity_data.HP = player->GetMaxHP();
		return 0.0f;
	}
	return 20000.0f;
}

__attribute__((naked)) void ASMFixInvis() {
	asm(".intel_syntax \n"
		PUSH_ALL
		PREPARE_STACK
		"call load_invis_time \n"
		RESTORE_STACK
		POP_ALL

		"lea rdx, [rbp-0x19] \n"
		"mov r8b, 1 \n"
		DEREF_JMP(ASMFixInvis_jmpback)
		".att_syntax \n"

	);
}

void fix_invis() {
	char* base = (char*)CWBase();
	WriteFarJMP(Offset(base, 0x29D6C9), (void*)&ASMFixInvis);
	ASMFixInvis_jmpback = (base + 0x29D6D8);
}

void hook_customclass_new_ultimate() {
	fix_invis();
}