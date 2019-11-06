#include "main.h"
#include "../cwmods/cwmods.h"
#include "hooks/hook_fire_trail.h"
#include "hooks/hook_creation_menu.h"
#include "hooks/hook_item_restriction_bypass.h"
#include "hooks/hook_villager_damage.h"
#include "hooks/hook_villager_no_mp_drain.h"
#include "hooks/hook_villager_ultimate.h"
//#include "hooks/hook_villager_new_ultimate.h"
#include "hooks/hook_add_villager_ult_in_camouflage.h"
//#include "hooks/hook_fix_villager_ult.h"

EXPORT void ModInitialize() {
	auto base = CWBase();
	hook_creation_menu(base);
	hook_item_restriction_bypass(base);
	hook_fire_trail(base);
	hook_villager_damage(base);
	hook_villager_no_mp_drain(base);
	hook_villager_ultimate(base);
	hook_villager_new_ultimate(base);
}

/*
Code caves used:
50301
1694B0
1694C2
//5F01F


To do:
(test getting hit by every enemy ability)

1. Get working with new sdk and mod launcher
2. Weapon chests/treasure/POI's only drop armor.
3. Fix crafting tab being shifted over.
4. Fix ultimate name (use chris's method with dict_en.xml?). Name of "Second chance"?
5. Fix specialization (needs to be default 0) and name (use chris's method with dict_en.xml?)
6. Fix shift ability UI label
7. Fix crafting (allow cobwebs and cotton to be make into plain silk)
8. Fix not looking invis when using ult

*/
