#include "Game.h"
#include <iostream>
#include <stdlib.h>   
#include <time.h> 



Game::Game() {
	playerHealth = 3;
	playerScore = 0;
	justSpawned = false;
}
//this game method will initialise player

//below is for handling spawning new waves of npcs
bool Game::GetJustSpawned() {
	return justSpawned;
}
void Game::SetJustSpawned(bool spawned) {
	justSpawned = spawned;
}


int Game::GetPlayerHealth() {
	return playerHealth;
}
int Game::GetPlayerScore() {
	return playerScore;
}



//using randomness to have variety of chasers
//always spawn in corners as to give the player a chance 
void Game::SpawnNewWaveOfChasers() {
	srand(time(NULL));
	int speedMultiplier = rand() % 19 + 1;
	this->AddChaser(this->SpawnChaser(-85, -85, 0.0005 * speedMultiplier, 4));
	speedMultiplier = rand() % 19 + 1;
	this->AddChaser(this->SpawnChaser(85, -85, 0.0005 * speedMultiplier, 4));
	speedMultiplier = rand() % 19 + 1;

	this->AddChaser(this->SpawnChaser(-85, 85, 0.0005 * speedMultiplier, 4));
	speedMultiplier = rand() % 19 + 1;

	this->AddChaser(this->SpawnChaser(85, 85, 0.0005 * speedMultiplier, 4));
}

//spawn fleers anywhere on map with random position for spawning
void Game::SpawnNewWaveOfFleers() {
	srand(time(NULL));
	for (int i = 0; i < 10; i++) {
		int speedMultiplier = rand() % 19 + 1;
		int x = rand() % 121 - 60;
		int y = rand() % 121 - 60;
		this->AddFleer(this->SpawnFleer(x, y, 0.0005 * speedMultiplier, 4));
	}
}




void Game::SpawnBackground() {
	float red[3] = { 1,0,0 };
	background.SetWidth(200.0f);
	background.SetHeight(200.0f);
	background.Init(red, "textures/background.png", 200/64, 200/64);
	background.SetXpos(0);
	background.SetYpos(0);
}


void Game::SpawnWalls() {
	float red[3] = { 1,0,0 };
	Sprite wallBottom;
	wallBottom.SetWidth(225.0f);
	wallBottom.SetHeight(25.0f);
	wallBottom.Init(red, "textures/wall2.png", 225 / 64, 1);
	wallBottom.SetXpos(0);
	wallBottom.SetYpos(-100);
	walls.push_back(wallBottom);

	Sprite wallTop;
	wallTop.SetWidth(225.0f);
	wallTop.SetHeight(25.0f);
	wallTop.Init(red, "textures/wall2.png", 225 / 64, 1);
	wallTop.SetXpos(0);
	wallTop.SetYpos(100);
	walls.push_back(wallTop);

	Sprite wallLeft;
	wallLeft.SetWidth(25.0f);
	wallLeft.SetHeight(225.0f);
	wallLeft.Init(red, "textures/wall2.png", 1, 225 / 64);
	wallLeft.SetXpos(-100);
	wallLeft.SetYpos(0);
	walls.push_back(wallLeft);

	Sprite wallRight;
	wallRight.SetWidth(25.0f);
	wallRight.SetHeight(225.0f);
	wallRight.Init(red, "textures/wall2.png", 1, 225 / 64);
	wallRight.SetXpos(100);
	wallRight.SetYpos(0);
	walls.push_back(wallRight);
}

//code for spawning new npcs below
FleerNPC Game::SpawnFleer(float x, float y, float speed, float sideLength) {
	FleerNPC newNPC;
	newNPC.SetXpos(x);
	newNPC.SetYpos(y);
	newNPC.SetMaxSpeed(speed);
	newNPC.SetWidth(sideLength);
	newNPC.SetHeight(sideLength);
	float red[3] = { 1,0,0 };
	newNPC.Init(red, "textures/food.png");

	return newNPC;
}

ChaserNPC Game::SpawnChaser(float x, float y, float speed, float sideLength) {
	ChaserNPC newNPC;
	newNPC.SetXpos(x);
	newNPC.SetYpos(y);
	newNPC.SetMaxSpeed(speed);
	newNPC.SetWidth(sideLength);
	newNPC.SetHeight(sideLength);
	float red[3] = { 1,0,0 };
	newNPC.Init(red, "textures/enemy.png");

	return newNPC;
}



PathFollowNPC Game::SpawnPathFollower(float x, float y, float speed, float sideLength, bool clockwise, int moveAmountOfTimes) {
	PathFollowNPC newNPC(clockwise, x, y);
	newNPC.SetMaxSpeed(speed);
	newNPC.SetWidth(sideLength);
	newNPC.SetHeight(sideLength);
	float red[3] = { 1,0,0 };
	newNPC.Init(red, "textures/neutral.png");
	newNPC.SetMoveAmountOfTimes(moveAmountOfTimes);
	
	return newNPC;
}

Sprite Game::GetPlayer() {
	return player;
}

void Game::SetPlayer(Sprite player) {
	this->player = player;
}

void Game::AddChaser(ChaserNPC chaser) {
	spriteVector.push_back(chaser);
	ChaserVector.push_back(chaser);
}
void Game::AddFleer(FleerNPC fleer) {
	spriteVector.push_back(fleer);
	FleerVector.push_back(fleer);
}
void Game::AddPathFollow(PathFollowNPC Pathfollow) {
	spriteVector.push_back(Pathfollow);
	PathFollowVector.push_back(Pathfollow);
}



void Game::RenderSprite(Sprite sprite, glm::mat4 projectionMatrix, float y, float x) {
	ModelViewMatrix = glm::translate(ViewMatrix, glm::vec3(x, y, 0.0));
	sprite.Render(ModelViewMatrix, projectionMatrix);
}



void Game::RenderAllSprites(glm::mat4 projectionMatrix) {
	ModelViewMatrix = glm::translate(ViewMatrix, glm::vec3(background.GetXPos(), background.GetYPos(), 0.0));
	background.Render(ModelViewMatrix, projectionMatrix);
	for (int i = 0; i < ChaserVector.size(); i++) {
		ModelViewMatrix = glm::translate(ViewMatrix, glm::vec3(ChaserVector.at(i).GetXPos(), ChaserVector.at(i).GetYPos(), 0.0));
		ChaserVector.at(i).Render(ModelViewMatrix, projectionMatrix);
	}
	for (int i = 0; i < FleerVector.size(); i++) {
		ModelViewMatrix = glm::translate(ViewMatrix, glm::vec3(FleerVector.at(i).GetXPos(), FleerVector.at(i).GetYPos(), 0.0));
		FleerVector.at(i).Render(ModelViewMatrix, projectionMatrix);
	}
	for (int i = 0; i < PathFollowVector.size(); i++) {
		ModelViewMatrix = glm::translate(ViewMatrix, glm::vec3(PathFollowVector.at(i).GetXPos(), PathFollowVector.at(i).GetYPos(), 0.0));
		PathFollowVector.at(i).Render(ModelViewMatrix, projectionMatrix);
	}
	for (int i = 0; i < walls.size(); i++) {
		ModelViewMatrix = glm::translate(ViewMatrix, glm::vec3(walls.at(i).GetXPos(), walls.at(i).GetYPos(), 0.0));
		walls.at(i).Render(ModelViewMatrix, projectionMatrix);
	}
	
}

bool Game::MovePlayer(Sprite thePlayer) {
	//the player only checks collisions with walls and pathfollower as colliding with chaser or fleer results in score or health being changed


	for (int i = 0; i < 4; i++) {
		//check all walls for collision
		if (thePlayer.GetOBB().CheckIfWillBeSAT2D(walls[i].GetOBB(), thePlayer.GetXMoveAmount(), thePlayer.GetYMoveAmount())) {
			//checks whether there will be a collision
			return true;
		}
	}
	
	
	for (int i = 0; i < PathFollowVector.size(); i++) {
		if (!(thePlayer.GetXPos() > (PathFollowVector.at(i).GetXPos() + 10) || thePlayer.GetXPos() < (PathFollowVector.at(i).GetXPos() - 10) || thePlayer.GetYPos() > (PathFollowVector.at(i).GetYPos() + 10) || thePlayer.GetYPos() < (PathFollowVector.at(i).GetYPos() - 10))) {
			if (thePlayer.GetOBB().CheckIfWillBeSAT2D(PathFollowVector.at(i).GetOBB(), thePlayer.GetXMoveAmount(), thePlayer.GetYMoveAmount())) {

				return true;					
			}
		}
	}

	return false;

}

void Game::MoveAllSprites(float playerX, float playerY, Sprite thePlayer) {
	//this will call check collisions when trying to move a sprite
	//will use calculatemove to update x and y move amount variables
	//if returned false from check collisions move the sprite yeyye

	
	for (int i = 0; i < ChaserVector.size(); i++) {
		ChaserVector.at(i).SetPlayerCoord(playerX, playerY);
		ChaserVector.at(i).CalculateMove();
		if (!CheckCollisions(ChaserVector.at(i), i, thePlayer)) {
			ChaserVector.at(i).MoveByMoveAmounts();
		}
		//below is if movement results in a collision, try just the x axis movement, a way to stop chaser being stuck behind something
		else {
			//gets the sign of move amount, and applies it to max speed
			ChaserVector.at(i).SetXMoveAmount(ChaserVector.at(i).GetXMoveAmount() / (abs(ChaserVector.at(i).GetXMoveAmount())) * ChaserVector.at(i).GetMaxSpeed());
			ChaserVector.at(i).SetYMoveAmount(0);
			if (!CheckCollisions(ChaserVector.at(i), i, thePlayer)) {
				ChaserVector.at(i).MoveByMoveAmounts();
			}
			else {
				ChaserVector.at(i).CalculateMove();
				ChaserVector.at(i).SetXMoveAmount(0);
				ChaserVector.at(i).SetYMoveAmount(ChaserVector.at(i).GetYMoveAmount() / (abs(ChaserVector.at(i).GetYMoveAmount())) * ChaserVector.at(i).GetMaxSpeed());
				if (!CheckCollisions(ChaserVector.at(i), i, thePlayer)) {
					ChaserVector.at(i).MoveByMoveAmounts();
				}
			}
			
		}
		if (ChaserVector.at(i).GetOBB().SAT2D(thePlayer.GetOBB())) {
			ChaserVector.erase(ChaserVector.begin()+i);
			playerHealth--;
		}
	}

	

	for (int i = 0; i < FleerVector.size(); i++) {
		FleerVector.at(i).SetPlayerCoord(playerX, playerY);
		//check whether player is within 28 of fleer
		//so the fleer doesnt just run to edge of map
		if ((!(FleerVector.at(i).GetXPos() > (playerX + 28) || FleerVector.at(i).GetXPos() < (playerX - 28) || FleerVector.at(i).GetYPos() > (playerY + 28) || FleerVector.at(i).GetYPos() < (playerY - 28)))) {
			FleerVector.at(i).CalculateMove();
			if (!CheckCollisions(FleerVector.at(i), i, thePlayer)) {
				FleerVector.at(i).MoveByMoveAmounts();

			}
			else {
				//gets the sign of move amount, and applies it to max speed
				FleerVector.at(i).SetXMoveAmount(FleerVector.at(i).GetXMoveAmount() / (abs(FleerVector.at(i).GetXMoveAmount())) * FleerVector.at(i).GetMaxSpeed());
				FleerVector.at(i).SetYMoveAmount(0);

				if (!CheckCollisions(FleerVector.at(i), i, thePlayer)) {
					FleerVector.at(i).MoveByMoveAmounts();
				}
				else {
					FleerVector.at(i).CalculateMove();
					FleerVector.at(i).SetXMoveAmount(0);
					FleerVector.at(i).SetYMoveAmount(FleerVector.at(i).GetYMoveAmount() / (abs(FleerVector.at(i).GetYMoveAmount())) * FleerVector.at(i).GetMaxSpeed());
					if (!CheckCollisions(FleerVector.at(i), i, thePlayer)) {
						FleerVector.at(i).MoveByMoveAmounts();

					}
				}

			}
			if (FleerVector.at(i).GetOBB().SAT2D(thePlayer.GetOBB())) {
				FleerVector.erase(FleerVector.begin() + i);
				playerScore++;
			}
		}
	}

	for (int i = 0; i < PathFollowVector.size(); i++) {
		PathFollowVector.at(i).CalculateMove();

		if (!CheckCollisions(PathFollowVector.at(i), i, thePlayer)) {
			PathFollowVector.at(i).MoveByMoveAmounts();
		}
	}


		
	
}



bool Game::CheckCollisions(NPC npc, int num, Sprite thePlayer) {
	
	for (int i = 0; i < 4; i++) {
		//check all walls for collision
		if (npc.GetOBB().CheckIfWillBeSAT2D(walls[i].GetOBB(), npc.GetXMoveAmount(), npc.GetYMoveAmount())) {
			//checks whether there will be a collision
			return true;
		}
	}
	
	
	//checks all chasernpcs for collision
	for (int i =0; i < ChaserVector.size(); i++) {
		if (!(ChaserVector.at(i).GetXPos() > (npc.GetXPos() + 10) || ChaserVector.at(i).GetXPos() < (npc.GetXPos() - 10) || ChaserVector.at(i).GetYPos() > (npc.GetYPos() + 10) || ChaserVector.at(i).GetYPos() < (npc.GetYPos() - 10))) {
			//checks whether the sprite is in range of 10 * 10 of other sprite
			//so doesnt need to check all sprites for collisions
			
			if ((i != num) || (npc.GetType() != NPC::Type::Chaser)) {
				//checks whether sprite is the same 
				if (npc.GetOBB().CheckIfWillBeSAT2D(ChaserVector.at(i).GetOBB(), npc.GetXMoveAmount(), npc.GetYMoveAmount())) {
					//checks whether there will be a collision
					return true;
				}
			}
			else {
			}

		}
	}

	for (int i = 0; i < FleerVector.size(); i++) {

		if (!(FleerVector.at(i).GetXPos() > (npc.GetXPos() + 10) || FleerVector.at(i).GetXPos() < (npc.GetXPos() - 10) || FleerVector.at(i).GetYPos() > (npc.GetYPos() + 10) || FleerVector.at(i).GetYPos() < (npc.GetYPos() - 10))) {
			//checks whether the sprite is in range of 10 * 10 of other sprite


			if ((i != num) || (npc.GetType() != NPC::Type::Fleer)) {
				//checks whether sprite is the same 

				if (npc.GetOBB().CheckIfWillBeSAT2D(FleerVector.at(i).GetOBB(), npc.GetXMoveAmount(), npc.GetYMoveAmount())) {
					//checks whether there will be a collision
					return true;
				}
			}
			
		}
	}
	
	for (int i = 0; i < PathFollowVector.size(); i++) {
		if (!(PathFollowVector.at(i).GetXPos() > (npc.GetXPos() + 10) || PathFollowVector.at(i).GetXPos() < (npc.GetXPos() - 10) || PathFollowVector.at(i).GetYPos() > (npc.GetYPos() + 10) || PathFollowVector.at(i).GetYPos() < (npc.GetYPos() - 10))) {
			//checks whether the sprite is in range of 10 * 10 of other sprite


			if ((i != num) || (npc.GetType() != NPC::Type::PathFollower)) {
				//checks whether sprite is the same 
				if (npc.GetOBB().CheckIfWillBeSAT2D(PathFollowVector.at(i).GetOBB(), npc.GetXMoveAmount(), npc.GetYMoveAmount())) {
					//checks whether there will be a collision
					return true;
				}
			}
			else {
			}

		}
	}

	//check against player for collision if its not collision triggered, as npcs will need to be able to move into players obb for game to work
	if(!npc.GetCollisionTriggered()){
		if (npc.GetOBB().CheckIfWillBeSAT2D(thePlayer.GetOBB(), npc.GetXMoveAmount(), npc.GetYMoveAmount())) {
			//checks whether there will be a collision
			return true;
		}
	}
	return false;
}

