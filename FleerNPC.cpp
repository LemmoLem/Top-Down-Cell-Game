#include "FleerNPC.h"

FleerNPC::FleerNPC() {
	SetType(Type::Fleer);
	SetCollisionTriggered(true);
}

void FleerNPC::CalculateMove() {
	//pretty much same as chaser but goes in the opposite direction as to run away from player
	float distanceX = GetPlayerX() - GetXPos();
	float distanceY = GetPlayerY() - GetYPos();
	//get distance in each axis
	//below is if the player is on top then just try go up and right, (only here if collision doesnt work)
	if (distanceX == 0 && distanceY == 0) {
		SetXMoveAmount(0.5 * GetMaxSpeed());
		SetYMoveAmount(0.5 * GetMaxSpeed());
	}
	else if (distanceX == 0) {
		SetXMoveAmount(0.0);
		SetYMoveAmount(GetMaxSpeed() * -(distanceY / (abs(distanceY))));
	}
	else if (distanceY == 0) {
		SetXMoveAmount(GetMaxSpeed() * -(distanceX / (abs(distanceX))));
		SetYMoveAmount(0.0);
	}
	//above using abs to get the sign
	else {
		float fractionX = 1.414 * (distanceX / (abs(distanceX) + abs(distanceY)));
		float fractionY = 1.414 * (distanceY / (abs(distanceX) + abs(distanceY)));
		//finds the fraction
		fractionX = -fractionX;
		fractionY = -fractionY;
		//inverts it
		SetXMoveAmount(fractionX * GetMaxSpeed());
		SetYMoveAmount(fractionY * GetMaxSpeed());
	}
}