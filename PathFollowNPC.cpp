#include "PathFollowNPC.h"
PathFollowNPC::PathFollowNPC(bool clockwise, float x, float y) {
	currentMoveNum = 0;
	yPositive = true;
	yNegative = false;
	xPositive = false;
	xNegative = false;
	this->clockwise = clockwise;
	SetXpos(x);
	SetYpos(y);
	SetType(Type::PathFollower);
	SetCollisionTriggered(false);
}

//path follow npc just moves on a loop
void PathFollowNPC::CalculateMove() {
	if (currentMoveNum == moveAmountOfTimes) {
		currentMoveNum = 0;
		if (yPositive) {
			yPositive = false;
			if (clockwise) {
				xPositive = true;
			}
			else
			{
				xNegative = true;
			}
		}
		else if (yNegative) {
			yNegative = false;
			if (clockwise) {
				xNegative = true;
			}
			else
			{
				xPositive = true;
			}
		}
		else if (xPositive) {
			xPositive = false;
			if (clockwise) {
				yNegative = true;
			}
			else
			{
				yPositive = true;
			}
		}
		else {
			xNegative = false;
			if (clockwise) {
				yPositive = true;
			}
			else
			{
				yNegative = true;
			}
		}
		
	}

	else {
		if (yPositive) {
			SetXMoveAmount(0);
			SetYMoveAmount(1 * GetMaxSpeed());
		}
		else if (yNegative) {
			SetXMoveAmount(0);
			SetYMoveAmount(-1 * GetMaxSpeed());
		}
		else if (xPositive) {
			SetXMoveAmount(1 * GetMaxSpeed());
			SetYMoveAmount(0);
		}
		else {
			SetXMoveAmount(-1 * GetMaxSpeed());
			SetYMoveAmount(0);
		}
	}
}

void PathFollowNPC::SetMoveAmountOfTimes(int amount) {
	moveAmountOfTimes = amount;
}



void PathFollowNPC::MoveByMoveAmounts() {
	SetXpos(GetXMoveAmount() + GetXPos());
	SetYpos(GetYMoveAmount() + GetYPos());
	currentMoveNum++;
}

 