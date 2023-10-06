#include <iostream>
using namespace std;

//--- OpenGL ---
#include "GL\glew.h"
#include "GL\wglew.h"
#pragma comment(lib, "glew32.lib")
//--------------

#include "glm\glm.hpp"
#include "glm\gtc\matrix_transform.hpp"


#include "GL\freeglut.h"
#include "FreeImage.h"

#include "Sprite.h"
#include "NPC.h"
#include "Game.h"
#include <iostream>
#include "ChaserNPC.h"
#include "FleerNPC.h"
#include "PathFollowNPC.h"


using namespace std;

glm::mat4 ViewMatrix;  // matrix for the modelling and viewing
glm::mat4 ProjectionMatrix; // matrix for the orthographic projection
int screenWidth = 480, screenHeight = 480;

//booleans to handle when the arrow keys are pressed or released.
bool Left = false;
bool Right = false;
bool Up = false;
bool Down = false;

Sprite player;


Game game1;


//OPENGL FUNCTION PROTOTYPES
void display();				//used as callback in glut for display.
void reshape(int width, int height); //used as callback for reshape function in glut
void init();				//called in main when the program starts.

/*************    START OF OPENGL FUNCTIONS   ****************/

void reshape(int width, int height)		// Resize the OpenGL window
{
	screenWidth = width;
	screenHeight = height;

	glViewport(0, 0, width, height);						// set Viewport dimensions

}

void display()									
{
	//clear the colour and depth buffers
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);


	ProjectionMatrix = glm::ortho(player.GetXPos()-25.0, player.GetXPos()+25.0, player.GetYPos()-25.0, player.GetYPos()+25.0);
	//above is way that the player stays in center of the screen

	ViewMatrix = glm::translate(glm::mat4(1.0), glm::vec3(0.0, 0.0, 0.0));
	game1.RenderAllSprites(ProjectionMatrix);

	glEnable(GL_BLEND);
	glm::mat4 ModelViewMatrix = glm::translate(ViewMatrix, glm::vec3(player.GetXPos(), player.GetYPos(), 0.0));
	player.Render(ModelViewMatrix, ProjectionMatrix);
	
	glDisable(GL_BLEND);
	


	glutSwapBuffers();

}

void init()
{
	FreeImage_Initialise();
	
	glClearColor(0.0,0.0,1.0,0.0);						//sets the clear colour to black
	float red[3] = { 1,0,0 };
	float red2[3] = { 0,0,0 };
	game1.SpawnBackground();
	player.SetWidth(4.0f);
	player.SetHeight(4.0f);
	
	player.Init(red, "textures/chromosome.png");
	

	player.SetMaxSpeed(0.03f);

	game1.AddPathFollow(game1.SpawnPathFollower(-40, -40, 0.008, 4, true, 1000));
	game1.AddPathFollow(game1.SpawnPathFollower(40, 40, 0.012, 4, false, 1000));
	game1.AddPathFollow(game1.SpawnPathFollower(-40, 40, 0.006, 4, true, 1500));
	game1.AddPathFollow(game1.SpawnPathFollower(40, -40, 0.016, 4, false, 800));

	game1.SpawnWalls();

	game1.SetPlayer(player);

	
	

	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
}

void special(int key, int x, int y)
{
	switch (key)
	{
	case GLUT_KEY_LEFT:
		Left = true;
		break;
	case GLUT_KEY_RIGHT:
		Right = true;
		break;
	case GLUT_KEY_UP:
		Up = true;
		break;
	case GLUT_KEY_DOWN:
		Down = true;
		break;
	}
}

void specialUp(int key, int x, int y)
{
	switch (key)
	{
	case GLUT_KEY_LEFT:
		Left = false;
		break;
	case GLUT_KEY_RIGHT:
		Right = false;
		break;
	case GLUT_KEY_UP:
		Up = false;
		break;
	case GLUT_KEY_DOWN:
		Down = false;
		break;
	}
}


//use booleans to set how much the player wants to move by rather than just incrementing position, so that collisions can occur
void processKeys() 
{

	//as pressing both left and right cancels movement in either direction i use ^ 
	if (Left ^ Right)
	{
		

		//used this if and else so that if user is going diagonal the speed scales
		if (!(Up ^ Down)) {
			if (Left) {
				
				player.SetXMoveAmount(-1 * player.GetMaxSpeed());
				
			}
			if (Right) {
				player.SetXMoveAmount(1 * player.GetMaxSpeed());
			}
			player.SetYMoveAmount(0.0f);
		}
		else {
			if (Left) {
				player.SetXMoveAmount(-0.7071 * player.GetMaxSpeed());
			}
			if (Right) {
				player.SetXMoveAmount(0.7071 * player.GetMaxSpeed());
			}
			if (Up) {
				player.SetYMoveAmount(0.7071 * player.GetMaxSpeed());
			}
			if (Down) {
				player.SetYMoveAmount(-0.7071 * player.GetMaxSpeed());
			}
		}
	}
	else if (Up ^ Down) {
		if (Up) {
			player.SetYMoveAmount(1 * player.GetMaxSpeed());
		}
		if (Down) {
			player.SetYMoveAmount(-1 * player.GetMaxSpeed());
		}
		player.SetXMoveAmount(0.0f);
	}

	if (!(Left || Right || Down || Up)) {
		player.SetXMoveAmount(0.0f);
		player.SetYMoveAmount(0.0f);
	}

}

void idle()
{
	processKeys();

	game1.MoveAllSprites(player.GetXPos(),player.GetYPos(), player);
	if (!game1.MovePlayer(player)) {
		player.MoveByMoveAmounts();
	}
	//code below is way that the game will spawn new chasers and fleers when the player gets to 5 points
	if (game1.GetPlayerScore() % 5 == 0 && !game1.GetJustSpawned()) {
		game1.SpawnNewWaveOfChasers();
		game1.SpawnNewWaveOfFleers();
		game1.SetJustSpawned(true);
	}
	if (game1.GetPlayerScore() % 5 == 1) {
		game1.SetJustSpawned(false);
	}

	//game ends if player gets hit 3 times by an enemy
	if (game1.GetPlayerHealth() == 0) {
		glutLeaveMainLoop();
	}
	glutPostRedisplay();
}
/**************** END OPENGL FUNCTIONS *************************/

// FREEGLUT WINDOW SET UP
int main(int argc, char **argv)
{
	glutInit(&argc, argv);

	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
	glutInitWindowSize(screenWidth, screenHeight);
	glutInitWindowPosition(100, 100);
	glutCreateWindow("OpenGL FreeGLUT Example: Image loading");

	glutReshapeFunc(reshape);

	//This initialises glew - it must be called after the window is created.
	GLenum err = glewInit();
	if (GLEW_OK != err)
	{
		cout << " GLEW ERROR" << endl;
	}

	//Check the OpenGL version being used
	int OpenGLVersion[2];
	glGetIntegerv(GL_MAJOR_VERSION, &OpenGLVersion[0]);
	glGetIntegerv(GL_MINOR_VERSION, &OpenGLVersion[1]);
	cout << OpenGLVersion[0] << " " << OpenGLVersion[1] << endl;

	//initialise the objects for rendering
	init();

	//specify which function will be called to refresh the screen.
	glutDisplayFunc(display);

	glutSpecialFunc(special);
	glutSpecialUpFunc(specialUp);

	glutIdleFunc(idle);

	//starts the main loop. Program loops and calls callback functions as appropriate.
	glutMainLoop();

	return 0;
}

