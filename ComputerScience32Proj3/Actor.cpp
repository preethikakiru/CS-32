#include "Actor.h"
#include "StudentWorld.h"

// Students:  Add code to this file, Actor.h, StudentWorld.h, and StudentWorld.cpp
Actor::Actor(int ID, double X, double Y, Direction dir, double size, unsigned int depth):GraphObject(ID, X, Y, dir, size, depth)
{
	m_ID = ID; 
}

int Actor::getimageID()
{
	return m_ID; 
}

Star::Star(int ID, double X, double Y, Direction dir, double size, unsigned int depth) :Actor(IID_STAR, X, Y, 0, randInt(0.05, 0.50), 3)
{

}

Star::Star():Actor(IID_STAR, randInt(0, VIEW_WIDTH),randInt(0, VIEW_HEIGHT), 0, randInt(0.05, 0.50), 3)
{

}

void Star::doSomething()
{
	moveTo(getX() - 1, getY());
}

/*NachenBlaster::NachenBlaster(StudentWorld* gameWorld) :Actor(IID_NACHENBLASTER, 0, 128, 0, 1, 0, gameWorld)
{
	m_hitPoints = 50; 
	m_cabbagePoints = 30; 
	m_GameWorld = gameWorld; 
}

void NachenBlaster::doSomething()
{
	Direction dir = getDirection(); 
	int ch; 
	if (getWorld()->getKey(ch))
	{
		switch (ch)
		{
		case KEY_PRESS_LEFT:
			moveTo(getX() - 1, getY());
			setDirection(180);
			break;
		case KEY_PRESS_RIGHT:
			moveTo(getX() + 1, getY());
			setDirection(0);
			break;
		case KEY_PRESS_SPACE:
			if (m_cabbagePoints < 5)
				break;
			break;
		case KEY_PRESS_UP:
			moveTo(getX(), getY() - 1);
			setDirection(90);
			break;
		case KEY_PRESS_DOWN:
			moveTo(getX(), getY() + 1);
			setDirection(270);
			break;
		}
	}
}*/