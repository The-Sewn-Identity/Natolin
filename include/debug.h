#ifndef DEBUG_H
#define DEBUG_H

#include "levels.h"
#include "player.h"

#ifdef _NTSK_DEBUG_
    void DisplayPlayerInfo(Player *_player);
    void DisplayLevelInfo(Level *_level);
#endif

#endif