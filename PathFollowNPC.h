#pragma once
#include "NPC.h"
class PathFollowNPC : public NPC
{

private:
	int moveAmountOfTimes;
	int currentMoveNum;
	bool yPositive, yNegative, xPositive, xNegative, clockwise;
public:
	PathFollowNPC(bool clockwise, float x, float y);
	void CalculateMove();
	void SetMoveAmountOfTimes(int amount);
	void MoveByMoveAmounts();
};

