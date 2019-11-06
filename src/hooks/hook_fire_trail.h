void* ASMFire_Trail_jmpback;
void* ASMAddBuff;
void* ASMcheck_for_villager_jmpback;
void* ASMspecbyteret;

cube::Buff* ASMBuffPtr;

void no_optimize ASMFireTrailWhileRunning() {
    asm(PUSH_ALL
        "mov rax,[r13+0x08] \n"
        "mov rcx,[rax+0x448] \n"

        "cmp byte ptr [rcx+0x14C], 5 \n"
        "jne ASMFire_trail_lbl \n"

        // "mov rdx, [ASMBuffPtr] \n" //Buff
        // "mov r8, 0x01 \n"
        // "call [ASMAddBuff] \n"
        "movb [rcx+0x68], 0x92 \n" //Ability


        POP_ALL

        "jmp [ASMFire_Trail_jmpback] \n"

        "ASMFire_trail_lbl: \n"

        POP_ALL

        "mov rax,[r13+0x08] \n"
        "mov rcx,[rax+0x448] \n"
        "mov byte ptr [rcx+0x68],0x51 \n"
        "jmp [ASMFire_Trail_jmpback] \n"
       );
}

void no_optimize ASMcheck_for_villager() {
    asm("mov rcx, [rax+0x448] \n"
        "cmp byte ptr [rcx+0x14C], 5 \n"
        "jne ASMVillagerlbl \n"

        "jmp [ASMcheck_for_villager_jmpback] \n"

        "ASMVillagerlbl: \n"
        "cmp byte ptr [rcx+0x14C], 4 \n"
        "jmp [ASMcheck_for_villager_jmpback] \n"
       );
}

void no_optimize ASMspecbyte() {
    asm("cmp byte ptr [rcx+0x14C], 5 \n"
        "jne nochangebytelbl \n"
        "cmp byte ptr [rcx+0x14D], 0 \n"
        "jmp [ASMspecbyteret] \n"

        "nochangebytelbl: \n"
        "cmp byte ptr [rcx+0x14D], 1 \n"
        "jmp [ASMspecbyteret] \n"
       );
}

void change_spec_byte(void* base) {
  int offset = 0x8F2BA;
  WriteByte(base+offset, 0xE9);
  WriteByte(base+offset+0x01, 0x60);
  WriteByte(base+offset+0x02, 0xFD);
  WriteByte(base+offset+0x03, 0xFC);
  WriteByte(base+offset+0x04, 0xFF);
  WriteByte(base+offset+0x05, 0x90);
  WriteByte(base+offset+0x06, 0x90);
}

void hook_spec_byte(void* base){
  WriteFarJMP(base+0x5F01F, (void*)&ASMspecbyte);
  ASMspecbyteret = (void*)base+0x8F2C1;
}

void add_fire_trail(void* base){
  WriteFarJMP(base+0x8F33A, (void*)&ASMFireTrailWhileRunning);
  ASMFire_Trail_jmpback = (void*)base+0x8F349;
  ASMAddBuff = (void*)base+0x65390;

  ASMBuffPtr = (cube::Buff*)new char[sizeof(cube::Buff)];
  ASMBuffPtr->buff_id = cube::Buff::BuffType::AuraFlameRush;
  ASMBuffPtr->modifier = 0.5f;
  ASMBuffPtr->duration = 1000.0f;
}
  
void check_for_villager(void* base){
  WriteFarJMP(base+0x8F2AA, (void*)&ASMcheck_for_villager);
  ASMcheck_for_villager_jmpback = (void*)base+0x8F2B8;
}

void hook_fire_trail(void* base){
  change_spec_byte(base);
  hook_spec_byte(base);
  check_for_villager(base);
  add_fire_trail(base);
}
/*
this second hook, the check_for_villager, just changes the check from 4 (rogue) to villager (5).
You still need to be specialization 1 so change your specialization after making your villager character.
*/

//flame rush = 146
//action state offset = 68

//96EBC i forgot what this is because i forgot to write a comment for it :(
//97875 same as above
//9531A hook to write own functions for unequip?? might be outdated info
//9CD6 unequip bow with boomerang (and other things too I think)
//9CE1 accesses left weapon slot when i have a crossbow equipped and i click a bow. also, when bow is equipped and I click a mace (mov [rcx+04], eax).
//8C16A compares with ranger weapons
