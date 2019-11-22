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
//#include "src/hooks/hook_custom_damage.h"
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
	//new damagae calculations here
	virtual void OnCreatureAttackPowerCalculated(cube::Creature* creature, float* power) {
		if (cube::GetGame()->world->local_creature == creature) {
			float max_hp = creature->GetMaxHP();
			*power = 5.0f + (max_hp * 0.06f);
		}
	}

	virtual void Initialize() override {
		menu_hook();
		//hook_customclass_damage();
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

			game->GetPlayer()->entity_data.specialization = 0;

			std::pair<uint32_t, uint32_t> def;
			def.first = 5;
			def.second = 0;
			std::wstring specName(L"SpecializationFire");
			game->speech.specialization_type_id_map.insert_or_assign(def, specName);		
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
3. Fix ultimate name (use chris's method with dict_en.xml?). Name of "Second chance"?
4. Fix not looking invis when using ult or don't go invis
5. Fix shift ability UI label
*/