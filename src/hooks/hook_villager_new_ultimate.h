void* ASMUltimateInsert_jmpback;
void* ASMAdd_Ult;

//rdx and rbx are data
void go_to_cave(void* base){
  int offset = 0x8C5B3;
  WriteByte(base+offset, 0xE9);
  WriteByte(base+offset+0x01, 0x49);
  WriteByte(base+offset+0x02, 0x3D);
  WriteByte(base+offset+0x03, 0xFC);
  WriteByte(base+offset+0x04, 0xFF);
}

void no_optimize ASMUltimateInsert() {
  asm("cmp byte ptr [rdx+0x14C], 5 \n"
      "jne  ASMUltimateInsert_jmpback_lbl \n"

      PUSH_ALL

      "movq rax, [max_hp] \n"
      "lea rbx, [rdx+0x180] \n"
      "movq rax, [rax] \n"
      "movq [rbx], rax \n"

      POP_ALL

      "jmp [ASMAdd_Ult] \n"

      "ASMUltimateInsert_jmpback_lbl: \n"
      "call [ASMUltimateInsert_jmpback] \n"
      "jmp [ASMAdd_Ult] \n"

  );
}

void villager_ultimate_insert(void* base) {
  WriteFarJMP(base+0x50301, (void*)&ASMUltimateInsert);
  ASMUltimateInsert_jmpback = (void*)base+0x29D3C0; //if not villager
  ASMAdd_Ult = (void*)base+0x8C5B8; //after all done
}

void hook_villager_new_ultimate(void* base) {
  villager_ultimate_insert(base);
  go_to_cave(base);
}
/*
void* ASMUltimateInsert_jmpback;
void* ASMAdd_Ult;

void go_to_cave(void* base){
  int offset = 0x29D6E4;
  WriteByte(base+offset, 0xE9);
  WriteByte(base+offset+0x01, 0x18);
  WriteByte(base+offset+0x02, 0x2C);
  WriteByte(base+offset+0x03, 0xDB);
  WriteByte(base+offset+0x04, 0xFF);
}

void no_optimize ASMUltimateInsert() {
  asm("cmp byte ptr [rcx+0x14C], 5 \n"
      "jne  ASMAdd_Ult_lbl \n"

      PUSH_ALL

      "movq rax, [max_hp] \n"
      "lea rbx, [rcx+0x180] \n"
      "movq rax, [rax] \n"
      "movq [rbx], rax \n"

      POP_ALL

      "jmp [ASMUltimateInsert_jmpback] \n"

      "ASMAdd_Ult_lbl: \n"

      "call [ASMAdd_Ult] \n"
      "jmp [ASMUltimateInsert_jmpback] \n"
  );
}

void villager_ultimate_insert(void* base) {
  WriteFarJMP(base+0x50301, (void*)&ASMUltimateInsert);
  ASMUltimateInsert_jmpback = (void*)base+0x29D6E9;
  ASMAdd_Ult = (void*)base+0x65390;
}

void hook_villager_new_ultimate(void* base) {
  villager_ultimate_insert(base);
  go_to_cave(base);
}
*/
