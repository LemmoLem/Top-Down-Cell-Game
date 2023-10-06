#include "NPC.h"
#include <iostream>
NPC::NPC() {

}


void NPC::SetPlayerCoord(float x, float y) {
	playerX = x;
	playerY = y;
}

float NPC::GetPlayerX() {
	return playerX;
}
float NPC::GetPlayerY() {
	return playerY;
}

void NPC::CalculateMove(){}

void NPC::SetType(Type type)
{
	this->type = type;
}

NPC::Type NPC::GetType()
{
	return type;
}

bool NPC::GetCollisionTriggered() {
	return collisionTriggered;
}

void NPC::SetCollisionTriggered(bool isTrigger) {
	collisionTriggered = isTrigger;
}


