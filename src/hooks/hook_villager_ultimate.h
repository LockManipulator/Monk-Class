void* ASMUltimateActionInsert_jmpback;
void* ASMUltimateActionInsert_oldCode_jmp;
void* ASMUltimateActionInsert_zero_return_jmp;

void no_optimize ASMUltimateActionInsert() {
  asm("jz ASMUltimateActionInsert_oldCode_lbl \n"
      "sub edx, 1 \n"
      "je ASMUltimateActionInsert_rogue_lbl \n"
      "cmp edx, 1 \n"
      "jnz ASMUltimateActionInsert_zero_return_lbl \n"
      // Class = 5, aka villager
      "mov eax, 0x6D \n"
      "ret \n"

      "ASMUltimateActionInsert_zero_return_lbl: \n"
      "jmp [ASMUltimateActionInsert_zero_return_jmp] \n"

      "ASMUltimateActionInsert_rogue_lbl: \n"
      "cmp [rcx+0x14D], r8b \n"
      "jmp [ASMUltimateActionInsert_jmpback] \n"

      "ASMUltimateActionInsert_oldCode_lbl: \n"
      "jmp [ASMUltimateActionInsert_oldCode_jmp] \n"
  );
}

void villager_ultimate_action_insert(void* base) {
  WriteFarJMP(base+0x656F7, (void*)&ASMUltimateActionInsert);
  ASMUltimateActionInsert_jmpback = (void*)base+0x65705;
  ASMUltimateActionInsert_oldCode_jmp = (void*)base+0x65717;
  ASMUltimateActionInsert_zero_return_jmp = (void*)base+0x65713;
}

void hook_villager_ultimate(void* base) {
  villager_ultimate_action_insert(base);
}

//109, 112, 113, 114, 141, 146, 115