#include "global.h"
#include "data_mon_dump.h"
#include "pokemon.h"

#define STRUGGLE_MOVE 165
#define STRUGGLE_PP 20

static void HandleZeroPPMoves(u32 *dst) {
    int i;
    u8 hasAnyPP = FALSE;
    
    // Check if any move has PP
    for (i = 0; i < MAX_MON_MOVES; i++) {
        if (dst[20 + i*2 + 1] > 0) {
            hasAnyPP = TRUE;
            break;
        }
    }
    
    // If no PP for any move, set all moves to 0 and first move to Struggle
    if (!hasAnyPP) {
        for (i = 0; i < MAX_MON_MOVES; i++) {
            dst[20 + i*2] = 0;
            dst[20 + i*2 + 1] = 0;
        }
        dst[20] = STRUGGLE_MOVE;
        dst[21] = STRUGGLE_PP;
    }
}

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
    dst[16] = GetMonData(mon, MON_DATA_PERSONALITY, NULL) % 25;
    dst[17] = GetMonData(mon, MON_DATA_STATUS, NULL);

    dst[18] = 0;// Status2
    dst[19] = 0;// Status3

    for (i = 0; i < MAX_MON_MOVES; i++) {
        dst[20 + i*2] = GetMonData(mon, MON_DATA_MOVE1 + i, NULL);
        dst[20 + i*2 + 1] = GetMonData(mon, MON_DATA_PP1 + i, NULL);
    }
    
    // Handle case where all moves have 0 PP
    HandleZeroPPMoves(dst);
}

void DumpPartyMonDataActive(struct BattlePokemon *mon, u8 *gStatStageRatios, u32 *dst) {
    int i;
    u8 (*ratios)[2] = (u8 (*)[2])gStatStageRatios; // Cast to 2D array for proper access
    
    dst[0] = mon->species;
    dst[1] = TRUE;  
    
    dst[2] = (mon->attack * ratios[mon->statStages[STAT_ATK]][0]) / ratios[mon->statStages[STAT_ATK]][1];
    dst[3] = (mon->defense * ratios[mon->statStages[STAT_DEF]][0]) / ratios[mon->statStages[STAT_DEF]][1];
    dst[4] = (mon->speed * ratios[mon->statStages[STAT_SPEED]][0]) / ratios[mon->statStages[STAT_SPEED]][1];
    dst[5] = (mon->spAttack * ratios[mon->statStages[STAT_SPATK]][0]) / ratios[mon->statStages[STAT_SPATK]][1];
    dst[6] = (mon->spDefense * ratios[mon->statStages[STAT_SPDEF]][0]) / ratios[mon->statStages[STAT_SPDEF]][1];
    
    dst[7] = mon->ability;
    dst[8] = mon->types[0];
    dst[9] = mon->types[1];
    
    dst[10] = mon->hp;
    dst[11] = mon->level;
    dst[12] = mon->friendship;
    dst[13] = mon->maxHP;
    
    dst[14] = mon->item;
    dst[15] = mon->ppBonuses;
    dst[16] = mon->personality;
    dst[17] = mon->status1;
    
    dst[18] = mon->status2;
    dst[19] = 0;  
    
    for (i = 0; i < MAX_MON_MOVES; i++) {
        dst[20 + i*2] = mon->moves[i];
        dst[20 + i*2 + 1] = mon->pp[i];
    }
    
    // Handle case where all moves have 0 PP
    HandleZeroPPMoves(dst);
}
