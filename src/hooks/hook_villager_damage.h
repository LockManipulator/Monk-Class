void* update_damage_retn;
float* max_hp;

void no_optimize ASMGetHP() {
    asm("movaps xmm0, xmm6 \n"
        "movaps xmm6, [rsp+0x20] \n"
        "add rsp, 0x30 \n"

        "cmp byte ptr [rbx+0x60], 0 \n"
        "jne ASMFixDamage_skip \n"

        "push rax \n"
        "mov rax, [max_hp] \n"
        "movaps [rax], xmm0 \n"
        "pop rax \n"

        "ASMFixDamage_skip: \n"

        "pop rbx \n" // Pop rbx after, because we need it for the player check.

        "ret \n"
       );
}

void no_optimize ASMUpdateDamage(){
    asm("movaps xmm6, [rsp+0x70] \n"
      "movaps xmm7, [rsp+0x60] \n"
      "mov rsp, r11 \n"
      "pop r14 \n"

      "cmp byte ptr [rsi+0x60], 0 \n"
      "jne ASMUpdateDamageSkip \n"

      PUSH_ALL
      "mov rax, [max_hp] \n" //Load max_hp float pointer
      "addss xmm0, [rax] \n" //Add float from pointer to base damage
      "movq rdi, xmm1 \n" //Store xmm1
      "mov rax, 0x3d75c28f \n"//Set rax to 0.06 (6%)
      "movq xmm1, rax \n" //Set xmm1 to rax
      "mulss xmm0, xmm1 \n" //Multiply the damage by xmm1 (0.06)
      "movq xmm1, rdi \n" //Reset xmm1
      POP_ALL

      "ASMUpdateDamageSkip: \n"
      "jmp [update_damage_retn] \n"
      );
}

void get_hp(void* base){
  WriteFarJMP(base+0x5FC11, (void*)&ASMGetHP);
  max_hp = (float*) new char[4];
}

void update_damage(void* base){
  WriteFarJMP(base+0x4FD2B, (void*)&ASMUpdateDamage);
  update_damage_retn = (void*)base+0x4FD3A;
}

void hook_villager_damage(void* base){
  get_hp(base);
  update_damage(base);
}
/*
void no_optimize ASMGetHP() {
    asm("movaps xmm0, xmm6 \n"
        "movaps xmm6, [rsp+0x20] \n"
        "add rsp, 0x30 \n"

        "cmp byte ptr [rbx+0x08], 1 \n"
        "jne ASMFixDamage_skip \n"

        "push rax \n"
        "mov rax, [max_hp] \n"
        "movaps [rax], xmm0 \n"
        "pop rax \n"

        "ASMFixDamage_skip: \n"

        "pop rbx \n" // Pop rbx after, because we need it for the player check.

        "ret \n"
       );
}

RAX = 000002052AB2FC50
*/
