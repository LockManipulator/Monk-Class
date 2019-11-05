#ifndef BUFF_H
#define BUFF_H

#include "../IDA/types.h"

namespace cube {
  struct Buff {
      enum BuffType : char32_t {
          AuraBulwark = 1,
          AuraWarFrenzy = 2,
          AuraCamouflage = 3,
          AuraPoisoned = 4,
          //unk5 = 5,
          AuraManaShield = 6,
          //unk7 = 7,
          //unk8 = 8,
          AuraInstantFire = 9,
          AuraInstantShoot = 10,
          AuraDodge = 11,
          AuraSwiftness = 12,
          AuraNinjutsu = 13,
          //unk14 = 14,
          AuraShadowClone = 15,
          AuraFlameRush = 16,
          AuraRegeneration = 17,
          //unk18 = 18,
          AuraSpiritWorld = 19,
          //unk20 = 20,
          //unk21 = 21,
          //unk22 = 22,
          AuraLifeFlask = 23,
          AuraArmorFlask = 24,
          AuraResistanceFlask = 25,
          AuraHeatResistance = 26,
          AuraColdFlask = 27,
          AuraPlagueResistance = 28,
          AuraFrozen = 29,
          //unk30 = 30,
          //unk31 = 31,
          //unk32 = 32,
          AuraAncientPower = 33,
          AuraManaAbsorption = 34,
      };

      BuffType buff_id;
      float modifier;
      float duration;
      char32_t field_10;
      char32_t field_14;
      char32_t field_18;
  };
}

#endif // CREATURE_H
