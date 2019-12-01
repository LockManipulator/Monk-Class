GETTER_VAR(void*, ASMSetMenuClassName_retn);
GETTER_VAR(void*, ASMSetClassName_1_ret);
GETTER_VAR(void*, ASMSetClassName_2_ret);
GETTER_VAR(void*, ASMSetSpecializationName_0_ret);
GETTER_VAR(void*, vill_spec_ret);
GETTER_VAR(void*, is_rogue_0);

const char customclassname_0[] = "Monk";
const char roguename_0[] = "Rogue";
wchar_t customclassname_L[] = L"Monk";
wchar_t roguename_L[] = L"Rogue";
const char customclassspec_0[] = "Fire Magic";

extern "C" char* get_customclass_name() {
	return (char*)&customclassname_0;
}
extern "C" char* get_rogue_name() {
	return (char*)&roguename_0;
}
extern "C" wchar_t* get_customclass_name_L() {
	return (wchar_t*)&customclassname_L;
}
extern "C" wchar_t* get_rogue_name_L() {
	return (wchar_t*)&roguename_L;
}
extern "C" char* get_customclassspec_name() {
	return (char*)&customclassspec_0;
}

__attribute__((naked)) void ASMSetMenuClassName() {
	asm(".intel_syntax \n"
		"sub ecx,01 \n"
		"je asm_set_class_name_lbl \n"
		"push rax \n"
		"call get_customclass_name_L \n"
		"mov rdx, rax \n"
		"pop rax \n"
		DEREF_JMP(ASMSetMenuClassName_retn)

		"asm_set_class_name_lbl: \n"
		"push rax \n"
		"call get_rogue_name_L \n"
		"mov rdx, rax \n"
		"pop rax \n"
		DEREF_JMP(ASMSetMenuClassName_retn)
		".att_syntax \n"
	);
}

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

__attribute__((naked)) void ASMSetClassName_2() {
	asm(".intel_syntax \n"
		"sub ecx,01 \n"
		"je asm_set_class_name_lbl_2 \n"
		"push rax \n"
		"call get_customclass_name \n"
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

__attribute__((naked)) void ASMSetSpecializationName_0() {
	asm(".intel_syntax \n"
		"sub ecx, 1 \n"
		"jz roguespec_lbl \n" //if rogue
		"push rax \n"
		"call get_customclassspec_name \n"
		"mov rdx, rax \n"
		"pop rax \n"
		DEREF_JMP(vill_spec_ret)

		"roguespec_lbl: \n"
		"cmp byte ptr [rdx+0x14D], 0 \n"
		"jnz FuckChrisBecauseHeManglesFlagsBecauseHeIsScaredOfAssembly_lbl \n"
		DEREF_JMP(ASMSetSpecializationName_0_ret)

		"FuckChrisBecauseHeManglesFlagsBecauseHeIsScaredOfAssembly_lbl: \n"
		DEREF_JMP(is_rogue_0)
		".att_syntax \n"
	);
}

void set_spec_name() {
	char* base = (char*)CWBase();
	WriteFarJMP(Offset(base, 0x26F736), (void*)&ASMSetSpecializationName_0);
	ASMSetSpecializationName_0_ret = (base + 0x26F748);
	vill_spec_ret = (base + 0x26F74F);
	is_rogue_0 = (base + 0x26F759);
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

void ChangeMenuClassNames() {
	char* base = (char*)CWBase();
	WriteFarJMP(Offset(base, 0x2714CF), (void*)&ASMSetMenuClassName);
	ASMSetMenuClassName_retn = (base + 0x2714F6); //Ignore error
}

void menu_hook() {
	ChangeMenuCharacterCount(); // Ignore errors
	ChangeMenuClassNames();
	set_class_name();
	set_spec_name();
}