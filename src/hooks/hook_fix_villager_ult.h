void* ASMUltimateInsert_jmpback;
void* ASMIAmVillager;
void* ASMNotVillagerBuff;

void go_to_cave(void* base){
  int offset = 0x29D6C9;
  WriteByte(base+offset, 0xE9);
  WriteByte(base+offset+0x01, 0x38);
  WriteByte(base+offset+0x02, 0x2C);
  WriteByte(base+offset+0x03, 0xDB);
  WriteByte(base+offset+0x04, 0xFF);
  WriteByte(base+offset+0x05, 0x90);
  WriteByte(base+offset+0x06, 0x90);
  WriteByte(base+offset+0x07, 0x90);
}

//3501CF - draw text :omegalul:

void no_optimize ASMUltimateInsert() {
  asm("cmp byte ptr [rdi+0x14C], 5 \n"
      "jne  ASMUltimateInsert_jmpback_lbl \n"

      "movq rax, [max_hp] \n"
      "mov rax, [rax] \n"
      "mov [rdi+0x180], eax \n"
      "mov rcx, 1 \n"

      "jmp [ASMIAmVillager] \n"

      "ASMUltimateInsert_jmpback_lbl: \n"
      "mov rax, [ASMNotVillagerBuff] \n"
      "movss xmm0, [rax] \n"
      "jmp [ASMUltimateInsert_jmpback] \n"

  );
}

void villager_ultimate_insert(void* base) {
  WriteFarJMP(base+0x50306, (void*)&ASMUltimateInsert);
  ASMUltimateInsert_jmpback = (void*)base+0x29D6D1; //if not villager
  ASMIAmVillager = (void*)base+0x29D73C; //if villager
  ASMNotVillagerBuff = (void*)base+0x42E5C;
}

void hook_villager_new_ultimate(void* base) {
  villager_ultimate_insert(base);
  go_to_cave(base);
}
