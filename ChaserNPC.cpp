#include "ChaserNPC.h"
#include <iostream>

ChaserNPC::ChaserNPC() {
	SetType(Type::Chaser);
	SetCollisionTriggered(true);
}
void ChaserNPC::CalculateMove() {
	float distanceX = GetPlayerX() - GetXPos();
	float distanceY = GetPlayerY() - GetYPos();
	//get distance between player and chaser in each axis
	if (distanceX == 0 && distanceY == 0) {
		SetXMoveAmount(0.0);
		SetYMoveAmount(0.0);
	}
	//if distance is 0 in an axis that means the chaser is level with the player so sets other move amount to max
	else if (distanceX == 0) {
		SetXMoveAmount(0.0);
		SetYMoveAmount(GetMaxSpeed() * distanceY / (abs(distanceY)));
	}
	else if (distanceY == 0) {
		SetXMoveAmount(GetMaxSpeed() * distanceX / (abs(distanceX)));
		SetYMoveAmount(0.0);
	}
	//above using abs to get the sign
	//works out proportion to move to chase player
	else {
		float fractionX = 1.414 * (distanceX / (abs(distanceX) + abs(distanceY)));
		float fractionY = 1.414 * (distanceY / (abs(distanceX) + abs(distanceY)));
		//finds the fraction
		SetXMoveAmount(fractionX * GetMaxSpeed());
		SetYMoveAmount(fractionY * GetMaxSpeed());

	}

}