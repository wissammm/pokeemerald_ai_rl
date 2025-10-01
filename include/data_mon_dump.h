#ifndef DATA_MON_DUMP_H
#define DATA_MON_DUMP_H

#include "pokemon.h"
#include "gba/types.h"

void DumpPartyMonData(struct Pokemon *mon, u32 *dst);
void DumpPartyMonDataActive(struct BattlePokemon *mon, u8 *gStatStageRatios, u32 *dst);

#endif // DATA_MON_DUMP_H