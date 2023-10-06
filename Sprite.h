#pragma once

class Shader;

#include "glm\glm.hpp"
#include "glm\gtc\matrix_transform.hpp"
#include "gl\glew.h"


#include "OBB.h"
//
// sprite class contains everything needed to render and move a sprite and for collisions
// used as base for the npc types as well
//

class Sprite
{
private:
	unsigned int m_vaoID;		// id for Vertex Array Object
	unsigned int m_vboID[3];	// ids for Vertex Buffer Objects
	unsigned int m_NumberOfVerts;//number of vertices in the object

	Shader* m_Shader;  ///shader object 

	//Dimensions of the sprite.
	float m_Width;
	float m_Height;

	//position of the sprite
	float m_xpos;
	float m_ypos;
	float yMoveAmount, xMoveAmount;
	float maxSpeed;

	GLuint m_TexName; //identifier for the texture

	OBB obb; //obb object for oriented bounding box collision

public:
	Sprite();					//default constructor
	void Init(float colour[3], const char* filename);
	void Init(float colour[3], const char* filename, float repeatInS, float repeatInT);
	void SetWidth(float size);
	void SetHeight(float size);
	void SetXpos(float x);
	void SetYpos(float y);
	float GetXPos();
	float GetYPos();
	void IncPos(float x, float y);
	void Render(glm::mat4& ModelViewMatrix, glm::mat4& ProjectionMatrix);
	OBB& GetOBB();
	bool IsInCollision(OBB &anotherOBB);
	Sprite* GetSprite();
	void SetYMoveAmount(float amount);
	void SetXMoveAmount(float amount);
	float GetYMoveAmount();
	float GetXMoveAmount();
	void MoveByMoveAmounts();
	float GetMaxSpeed();
	void SetMaxSpeed(float amount);

};