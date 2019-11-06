void* ASMSetMenuClassName_retn;
void* ASMSetClassName_1_ret;
void* ASMSetClassName_2_ret;

void* rogueName_1;
void* villname_1;
void* rogueName_0;
void* villname_0;

//void* ASMSetSpecializationName_0_ret;
//void* vill_spec_ret;

//void* villspecname0;

void no_optimize ASMSetMenuClassName() {
    asm("sub ecx,01 \n"
        "je asm_set_class_name_lbl \n"
        "mov rdx, [villname_0] \n"
        "jmp [ASMSetMenuClassName_retn] \n"

        "asm_set_class_name_lbl: \n"
        "mov rdx, [rogueName_1] \n"
        "jmp [ASMSetMenuClassName_retn] \n"
       );
}

void no_optimize ASMSetClassName_1() {
    asm("sub ecx,01 \n"
        "je asm_set_class_name_lbl_1 \n"
        "mov rdx, [villname_0] \n"
        "jmp [ASMSetClassName_1_ret] \n"

        "asm_set_class_name_lbl_1: \n"
        "mov rdx, [rogueName_0] \n"
        "jmp [ASMSetClassName_1_ret] \n"
       );
}

void no_optimize ASMSetClassName_2() {
    asm("sub ecx,01 \n"
        "je asm_set_class_name_lbl_2 \n"
        "mov rdx, [villname_0] \n"
        "jmp [ASMSetClassName_2_ret] \n"

        "asm_set_class_name_lbl_2: \n"
        "mov rdx, [rogueName_0] \n"
        "jmp [ASMSetClassName_2_ret] \n"
       );
}
/*
void no_optimize ASMSetSpecializationName_0(){
  asm("sub ecx, 1 \n"
      "jz roguespec_lbl \n" //if rogue
      "mov rdx, [villspecname0] \n"
      "jmp [vill_spec_ret] \n"

      "roguespec_lbl: \n"
      "cmp byte ptr [rdx+0x14D], 0 \n"
      "jmp [ASMSetSpecializationName_0_ret] \n"
    );
}

void set_spec_name(void* base){
  WriteFarJMP(base+0x26F736, (void*)&ASMSetSpecializationName_0);
  ASMSetSpecializationName_0_ret = (void*)base+0x26F746;
  vill_spec_ret = (void*)base+0x26F74F;
}
*/
void set_class_name(void* base) {
  WriteFarJMP(base+0x2714CF, (void*)&ASMSetMenuClassName);
  ASMSetMenuClassName_retn = (void*)base+0x2714F6;
  WriteFarJMP(base+0x27405A, (void*)&ASMSetClassName_1);
  ASMSetClassName_1_ret = (void*)base+0x274081;
  WriteFarJMP(base+0x26F5D2, (void*)&ASMSetClassName_2);
  ASMSetClassName_2_ret = (void*)base+0x26F5F9;
}

void increase_character_count(void* base) {
  WriteByte( base + 0x272448 + 0x02, 0x04);
  WriteByte( base + 0x2723F1 + 0x01, 0x04);
}
/*
void writeSpecName(void* base) {
  int offset_1 = 0x5F08D;
  int offset_2 = 0x5F01F;
  char spec[] = "Fire";
  for (int i = 0; i < 9; i++) {
    WriteByte(base+offset_1+2*i, spec[i]);
    WriteByte(base+offset_1+2*i+1, 0x0);
  }
  for (int i = 0; i < 9; i++) {
    WriteByte(base+offset_2+i, spec[i]);
  }
}
*/
void writeClassName(void* base) {
  int offset_1 = 0x1694B0;
  int offset_2 = 0x1694C2;
  char villager[] = "Monk";
  for (int i = 0; i < 9; i++) {
    WriteByte(base+offset_1+2*i, villager[i]);
    WriteByte(base+offset_1+2*i+1, 0x0);
  }
  for (int i = 0; i < 9; i++) {
    WriteByte(base+offset_2+i, villager[i]);
  }
}

void hook_creation_menu(void* base) {
  rogueName_1 = (void*)base+0x46DE28;
  villname_1 = (void*)base+0x1694B0;
  rogueName_0 = (void*)base+0x46D8B8;
  villname_0 = (void*)base+0x1694C2;
  //villspecname0 = (void*)base+0x5F01F;

  increase_character_count(base);
  writeClassName(base);
  set_class_name(base);
  //writeSpecName(base);
  //set_spec_name(base);
}

/*
26F748 aAssassin_0
154ECC aAssassin
28DEDB SpecializationFire

  cube::Game* game = cube::GetGame();
  game->GetPlayer()->entity_data.specialization = 0;

  std::pair<uint32_t, uint32_t> def;
  def.first = 5;
  def.second = 1;
  std::wstring specName(L"SpecializationFire");
  game->speech.specialization_type_id_map.insert_or_assign(def, specName);
*/