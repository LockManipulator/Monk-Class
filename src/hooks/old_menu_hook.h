const char customclassname_0[] = "Monk";
const char roguename_0[] = "Rogue";

extern "C" std::wstring* LoadCharacterName(int id) {
	cube::Game* game = cube::GetGame();
	return &game->speech.entity_type_id_map.find(id+3)->second;
}

extern "C" char* get_customclass_name() {
	return (char*)&customclassname_0;
}

extern "C" char* get_rogue_name() {
	return (char*)&roguename_0;
}

GETTER_VAR(void*, ASMSetMenuClassName_retn); //Ignore error here 
__attribute__((naked)) void ASMSetMenuClassName() {
	asm(".intel_syntax \n"

		PUSH_ALL
		PREPARE_STACK

		"call LoadCharacterName \n"

		RESTORE_STACK

		"mov rdx, [rax] \n"
		"mov [rsp+0x58], rdx \n" //Address of the string

		POP_ALL

		DEREF_JMP(ASMSetMenuClassName_retn)
		".att_syntaxt \n"
	);
}

GETTER_VAR(void*, ASMSetClassName_1_ret);
__attribute__((naked)) void ASMSetClassName_1() {
	asm(".intel_syntax \n"
		"sub ecx,01 \n"
		"je asm_set_class_name_lbl_1 \n"
		"push rax \n"
		"call get_customclass_name \n"
		"mov rdx, rax \n"
		"pop rax \n"
		DEREF_JMP(ASMSetClassName_1_ret)

		"asm_set_class_name_lbl_1: \n"
		"push rax \n"
		"call get_rogue_name \n"
		"mov rdx, rax \n"
		"pop rax \n"
		DEREF_JMP(ASMSetClassName_1_ret)
		".att_syntax \n"
	);
}

GETTER_VAR(void*, ASMSetClassName_2_ret);
__attribute__((naked)) void ASMSetClassName_2() {
	asm(".intel_syntax \n"
		"sub ecx,01 \n"
		"je asm_set_class_name_lbl_2 \n"
		"push rax \n"
		"call get_customclass_name \n" //puts our string variable into rax
		"mov rdx, rax \n"
		"pop rax \n"
		DEREF_JMP(ASMSetClassName_2_ret)

		"asm_set_class_name_lbl_2: \n"
		"push rax \n"
		"call get_rogue_name \n"
		"mov rdx, rax \n"
		"pop rax \n"
		DEREF_JMP(ASMSetClassName_2_ret)
		".att_syntax \n"
	);
}

void writeClassName() {
	char* base = (char*)CWBase();
	int offset_2 = 0x1694C2;
	char villager[] = "Villager";
	for (int i = 0; i < 9; i++) {
		WriteByte(Offset(base, offset_2 + i), villager[i]);
	}
}

void set_class_name() {
	char* base = (char*)CWBase();
	WriteFarJMP(Offset(base, 0x27405A), (void*)&ASMSetClassName_1);
	ASMSetClassName_1_ret = (base + 0x274081);
	WriteFarJMP(Offset(base, 0x26F5D2), (void*)&ASMSetClassName_2);
	ASMSetClassName_2_ret = (base + 0x26F5F9);
}

void ChangeMenuCharacterCount() {
	char* base = (char*)CWBase();
	WriteByte(Offset(base, 0x272448 + 0x02), 0x04);
	WriteByte(Offset(base, 0x2723F1 + 0x01), 0x04);
}

void menu_hook() {
	char* base = (char*)CWBase();
	WriteFarJMP(Offset(base, 0x2714CF), (void*)&ASMSetMenuClassName);
	ASMSetMenuClassName_retn = Offset(base, 0x2714F6); //Ignore error
	ChangeMenuCharacterCount(); // Ignore errors
	writeClassName();
	set_class_name();
}