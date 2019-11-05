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

//3501CF - draw text :omegalul:

void no_optimize ASMUltimateInsert() {
  asm("cmp byte ptr [rdi+0x14C], 5 \n"
      "jne  ASMUltimateInsert_jmpback_lbl \n"

      PUSH_ALL

      "movq rax, [max_hp] \n"
      "mov rax, [rax] \n"
      "mov [rdi+0x180], eax \n"

      POP_ALL

      "jmp [ASMUltimateInsert_jmpback] \n"

      "ASMUltimateInsert_jmpback_lbl: \n"
      "call [ASMAdd_Ult] \n"
      "jmp [ASMUltimateInsert_jmpback] \n"

  );
}

void villager_ultimate_insert(void* base) {
  WriteFarJMP(base+0x50301, (void*)&ASMUltimateInsert);
  ASMUltimateInsert_jmpback = (void*)base+0x29D6E9; //if not villager
  ASMAdd_Ult = (void*)base+0x65390; //after all done
}

void hook_villager_new_ultimate(void* base) {
  villager_ultimate_insert(base);
  go_to_cave(base);
}
