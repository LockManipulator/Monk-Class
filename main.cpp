#include "main.h"
#include "cwmods/cwsdk.h"
#include <wchar.h>
#include <stdio.h>
#include <string.h>
#include <fstream>
#include <sstream>
#include <vector>
#include <map>
#include <windows.h>

#include "src/hooks/menu_hook.h"
#include "src/hooks/hook_add_ult.h"
#include "src/hooks/hook_new_ult.h"
#include "src/hooks/hook_customclass_nompdrain.h"
#include "src/hooks/hook_add_flamerush.h"
#include "src/hooks/hook_item_restriction_bypass.h"
#include "src/hooks/fix_treasure.h"

void* Offset(void* x1, uint64_t x2) {
	return (void*)((char*)x1 + x2);
}

void Popup(const char* title, const char* msg) {
	MessageBoxA(0, msg, title, MB_OK | MB_ICONINFORMATION);
}

class Mod : GenericMod {
	char* base = (char*)CWBase();
	bool init = false;
	bool used_monk = false;
	//new damagae calculations here
	virtual void OnCreatureAttackPowerCalculated(cube::Creature* creature, float* power) {
		if (cube::GetGame()->world->local_creature == creature) {
			float max_hp = creature->GetMaxHP();
			*power = 5.0f + (max_hp * 0.06f);
		}
	}

	virtual void Initialize() override {
		menu_hook();
		hook_customclass_ultimate();
		hook_customclass_new_ultimate();
		hook_customclass_no_mp_drain();
		hook_flamerush();
		hook_item_restriction_bypass();
		treasure_fix();
	}

	virtual void OnGameTick(cube::Game* game) override {
		if (!init) {
			init = true;
						
			std::pair<uint32_t, uint32_t> def;
			def.first = 5;
			def.second = 0;
			std::wstring specName(L"SpecializationFire");
			game->speech.specialization_type_id_map.insert_or_assign(def, specName);		
		}
		if (game->GetPlayer()->entity_data.classType == 5) {
			if (!used_monk) {
				used_monk = true;
				game->GetPlayer()->entity_data.specialization = 0;

				std::wstring ultName(L"SkillBulwark");
				game->speech.skill_type_id_map.insert_or_assign(109, ultName);
			}
		}
		else if (used_monk){
			used_monk = false;
			std::wstring ultName(L"SkillCamouflage");
			game->speech.skill_type_id_map.insert_or_assign(109, ultName);
		}
	}

};

EXPORT Mod* MakeMod() {
	return new Mod();
}

/*
To do:
(test getting hit by every enemy ability)

1. Fix crafting tab being shifted over.
2. Fix crafting (allow cobwebs and cotton to be made into plain silk)
3. Fix shift ability UI label
*/