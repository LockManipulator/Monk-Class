void* ASMBypassWeapon_jmpback;
void* ASMBypassWeapon_retn;
void* ASMBase;
void* ASMWeaponCheck;
void no_optimize ASMBypassWeapon() {
    asm(PUSH_ALL
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
        "jmp [ASMWeaponCheck] \n"

        "bypass_WPN_lbl2: \n"
        POP_ALL
        "jmp [ASMBypassWeapon_retn] \n"

       );
}

void bypass_weapon_restriction_1(void* base){
  WriteFarJMP(base+0x1094F7, (void*)&ASMBypassWeapon);
  ASMBypassWeapon_jmpback = (void*)base+0x109509;
  ASMBypassWeapon_retn = (void*)base+0x109677;
  ASMBase = (void*)base;
  ASMWeaponCheck = (void*)base+0x109555;
}

void hook_item_restriction_bypass(void* base){
  bypass_weapon_restriction_1(base);
}
//start at 555 jump back to 568
//50663 (for easier weapons check bypass)
