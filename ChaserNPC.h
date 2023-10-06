#pragma once
#include "NPC.h"
//
// chaserNPC tracks the player and adjust its movement based on player position
//
class ChaserNPC : public NPC
{
public:
	ChaserNPC();
	void CalculateMove();
};

