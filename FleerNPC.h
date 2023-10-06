#pragma once
#include "NPC.h"
//
// fleernpc runs away from the player and so uses similar method to chaser
// and uses negative values as to move away from the player
//
class FleerNPC : public NPC
{
public:
	FleerNPC();
	void CalculateMove();
};

