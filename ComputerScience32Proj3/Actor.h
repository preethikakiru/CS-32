#ifndef ACTOR_H_
#define ACTOR_H_

#include "GraphObject.h"

class StudentWorld; 

class Actor:public GraphObject
{
public:
	Actor(int ID, double X, double Y, Direction dir, double size, unsigned int depth);
	StudentWorld* getWorld();
	virtual void doSomething() = 0;
	int getimageID();
private:
	StudentWorld* m_gameWorld; 
	int m_ID; 
};

class Star :public Actor
{
public:
	Star();
	Star(int ID, double X, double Y, Direction dir, double size, unsigned int depth);
	virtual void doSomething();
private:
};

/*class NachenBlaster :public Actor
{
public:
	NachenBlaster(StudentWorld* GameWorld);
	virtual void doSomething();
private:
	int m_hitPoints; 
	int m_cabbagePoints; 
	StudentWorld* m_GameWorld; 
}*/

// Students:  Add code to this file, Actor.cpp, StudentWorld.h, and StudentWorld.cpp

#endif // ACTOR_H_
