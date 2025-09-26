#include "global.h"
#include "data_mon_dump.h"
#include "pokemon.h"


void DumpPartyMonData(struct Pokemon *mon, u32 *dst) {
    int i;
    
    dst[0] = GetMonData(mon, MON_DATA_SPECIES, NULL);

    dst[1] = FALSE;  // isActive
    dst[2] = GetMonData(mon, MON_DATA_ATK, NULL);
    dst[3] = GetMonData(mon, MON_DATA_DEF, NULL);
    dst[4] = GetMonData(mon, MON_DATA_SPEED, NULL);
    dst[5] = GetMonData(mon, MON_DATA_SPATK, NULL);
    dst[6] = GetMonData(mon, MON_DATA_SPDEF, NULL);

    dst[7] = GetMonData(mon, MON_DATA_ABILITY_NUM, NULL);

    dst[8] = gSpeciesInfo[dst[0]].types[0];  // type1 from species
    dst[9] = gSpeciesInfo[dst[0]].types[1];  // type2 from species
    // Moves (sequential indices)

    dst[10] = GetMonData(mon, MON_DATA_HP, NULL);
    dst[11] = GetMonData(mon, MON_DATA_LEVEL, NULL);
    dst[12] = GetMonData(mon, MON_DATA_FRIENDSHIP, NULL);
    dst[13] = GetMonData(mon, MON_DATA_MAX_HP, NULL);
    dst[14] = GetMonData(mon, MON_DATA_HELD_ITEM, NULL);
    dst[15] = GetMonData(mon, MON_DATA_PP_BONUSES, NULL);
    dst[16] = GetMonData(mon, MON_DATA_PERSONALITY, NULL);
    dst[17] = GetMonData(mon, MON_DATA_STATUS, NULL);

    dst[18] = 0;// Status2
    dst[19] = 0;// Status3


    for (i = 0; i < MAX_MON_MOVES; i+=2)
        dst[20 + i] = GetMonData(mon, MON_DATA_MOVE1 + i, NULL);
        dst[20 + i + 1] = GetMonData(mon, MON_DATA_PP1 + i, NULL);
}

// void DumpPartyMonDataActive(){

// }
