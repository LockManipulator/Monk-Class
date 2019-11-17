GETTER_VAR(void*, ASMBypassWeapon_retn);
GETTER_VAR(void*, ASMWeaponCheck);

__attribute__((naked)) void ASMBypassWeapon() {
	asm(".intel_syntax \n"
		PUSH_ALL
		"cmp al, 3 \n"
		"jz bypass_WPN_lbl \n"
		"jbe bypass_WPN_lbl2 \n"
		"cmp al, 7 \n"
		"ja bypass_WPN_lbl2 \n"

		"bypass_WPN_lbl: \n"
		"cmp rdx, 5 \n"
		"jne bypass_WPN_lbl3 \n"
		"cmp byte ptr [rcx], 0x03 \n" //no weapons allowed
		"je bypass_WPN_lbl3 \n"
		"jmp bypass_WPN_lbl2 \n"

		"bypass_WPN_lbl3: \n"
		POP_ALL
		DEREF_JMP(ASMWeaponCheck)

		"bypass_WPN_lbl2: \n"
		POP_ALL
		DEREF_JMP(ASMBypassWeapon_retn)
		".att_syntax \n"
	);
}

void bypass_weapon_restriction_1() {
	char* base = (char*)CWBase();
	WriteFarJMP(Offset(base, 0x1094F7), (void*)&ASMBypassWeapon);
	ASMBypassWeapon_retn = (base + 0x109677);
	ASMWeaponCheck = (base + 0x109555);
}

void hook_item_restriction_bypass() {
	bypass_weapon_restriction_1();
}