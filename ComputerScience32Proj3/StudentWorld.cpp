#include "StudentWorld.h"
#include "GameConstants.h"
#include <string>
using namespace std;

const int starCount = 30;

GameWorld* createStudentWorld(string assetDir)
{
	return new StudentWorld(assetDir);
}

// Students:  Add code to this file, StudentWorld.h, Actor.h and Actor.cpp

StudentWorld::StudentWorld(string assetDir):GameWorld(assetDir)  
{

}

int StudentWorld::init()
{
	for (int i = 0; i < starCount; i++)
	{
		Star obj;
		m_Stars[i] = &obj; 
	}
    return GWSTATUS_CONTINUE_GAME;
}

int StudentWorld::move()
{
    // This code is here merely to allow the game to build, run, and terminate after you hit enter.
    // Notice that the return value GWSTATUS_PLAYER_DIED will cause our framework to end the current level.
    decLives();
   return GWSTATUS_PLAYER_DIED;
}

void StudentWorld::cleanUp()
{
}

StudentWorld::~StudentWorld()
{
	cleanUp();
}
