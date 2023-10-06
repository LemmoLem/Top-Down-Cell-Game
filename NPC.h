#pragma once
#include "Sprite.h"

//
// base for the other npc classes
// collision triggered means if collides with player will something happen 
// type enum is used in game.cpp as so with using the position in the vector of the objects
// can check whether it is of that type, this is to make sure an npc doesnt check whether it collides with itself
//

class NPC : public Sprite
{

private:
	float playerX, playerY;
	bool collisionTriggered;
public:
	enum class Type{Fleer, Chaser, PathFollower};	
	Type type;

	NPC();

	void SetPlayerCoord(float x, float y);
	float GetPlayerX();
	float GetPlayerY();
	void CalculateMove();
	bool GetCollisionTriggered();
	void SetCollisionTriggered(bool isTrigger);
	void SetType(Type type);
	Type GetType();


};

