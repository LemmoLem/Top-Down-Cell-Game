#pragma once
#include "Sprite.h"
#include "NPC.h"


#include <list>
#include <vector>
#include "ChaserNPC.h"
#include "FleerNPC.h"
#include "PathFollowNPC.h"

//
// game class is used to contain all the npcs and walls and background
// with methods to spawn new waves of npcs 
// this class also moves every sprite and makes sure they dont collide with checking collisions before allowing movement
//
class Game
{

private:
	std::vector<Sprite> spriteVector;
	std::vector<NPC> NPCVector;
	std::vector<ChaserNPC> ChaserVector;
	std::vector<FleerNPC> FleerVector;
	std::vector<PathFollowNPC> PathFollowVector;
	glm::mat4 ViewMatrix = glm::translate(glm::mat4(1.0), glm::vec3(0.0, 0.0, 0.0));
	glm::mat4 ModelViewMatrix;
	std::vector<Sprite> walls;
	Sprite player;
	Sprite background;
	int playerHealth, playerScore;
	bool justSpawned;

public:
	Game();
	void RenderSprite(Sprite sprite, glm::mat4 projectionMatrix, float y, float x);
	void MoveAllSprites(float playerX, float playerY, Sprite thePlayer);
	bool MovePlayer(Sprite thePlayer);
	bool CheckCollisions(NPC npc, int num, Sprite thePlayer);
	void AddNPC(NPC npc);
	Sprite GetPlayer();
	void SetPlayer(Sprite player);
	void AddChaser(ChaserNPC chaser);
	void AddFleer(FleerNPC fleer);
	void AddPathFollow(PathFollowNPC Pathfollow);
	void SpawnWalls();
	void SpawnNewWaveOfChasers();
	void SpawnNewWaveOfFleers();
	void SpawnBackground();
	int GetPlayerHealth();
	int GetPlayerScore();
	bool GetJustSpawned();
	void SetJustSpawned(bool spawned);

	FleerNPC SpawnFleer(float x, float y, float speed, float sideLength);
	ChaserNPC SpawnChaser(float x, float y, float speed, float sideLength);
	PathFollowNPC SpawnPathFollower(float x, float y, float speed, float sideLength, bool clockwise, int moveAmountOfTimes);
	
	void RenderAllSprites(glm::mat4 projectionMatrix);
};

