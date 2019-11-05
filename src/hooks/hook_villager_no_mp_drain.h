void* ASMVillgerNoMpDrain_jmpback;

void no_optimize ASMVillgerNoMpDrain() {
  asm("movaps xmm1, xmm10 \n"

      "cmp byte ptr [r13+0x14C], 5 \n"
      "jne ASMVillgerNoMpDrain_no_villager_lbl \n"

      "push rax \n"
      "mov rax, 0x00000000 \n"
      "movq xmm12, rax \n"
      "pop rax \n"

      "ASMVillgerNoMpDrain_no_villager_lbl: \n"
      "mulss xmm1, xmm12 \n"
      "movss xmm0, [r13+0x188] \n"
      "jmp [ASMVillgerNoMpDrain_jmpback] \n"
  );
}

void villager_no_mp_drain(void* base) {
  WriteFarJMP(base+0x2DFDBC, (void*)&ASMVillgerNoMpDrain);
  ASMVillgerNoMpDrain_jmpback = (void*)base+0x2DFDCE;
}

void hook_villager_no_mp_drain(void* base) {
  villager_no_mp_drain(base);
}
