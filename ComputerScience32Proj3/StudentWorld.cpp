#include "StudentWorld.h"
#include "GameConstants.h"
#include <iostream>
#include <string>
#include <vector>
#include "Actor.h"
#include <sstream>
#include <iomanip> 
#include "math.h"
using namespace std;

GameWorld* createStudentWorld(string assetDir)
{
	return new StudentWorld(assetDir);
}

// Students:  Add code to this file, StudentWorld.h, Actor.h and Actor.cpp

StudentWorld::StudentWorld(string assetDir)
	: GameWorld(assetDir)
{
	actor.reserve(100);
	m_assetDir = assetDir;
	isCollision = false;
}

int StudentWorld::init()
{
	m_record = 0; 
	for (int i = 0; i < 30; i++)
	{
		actor.push_back(new Star);
	}
	m_ship = new NachenBlaster(this);
	m_aliens = 0;
	return GWSTATUS_CONTINUE_GAME;
}

bool StudentWorld::addAlien()
{
	int D = numofAliensDestroyed(); 
	int T = 6 + (4 * getLevel()); 
	int R = T - D;
	int M = 4 + (0.5 * getLevel()); 
	if (numOnScreen() < min(M, R))
	{
		return true; 
	}
	return false; 
}

int StudentWorld::move()
{ 
	setText();
	if (addAlien())
	{
		int S1 = 60;
		int S2 = 20 + (getLevel() * 5);
		int S3 = 5 + (getLevel() * 10);
		int S = S1 + S2 + S3;
		int rand = randInt(1, S);
		if (rand <= S1)
		{
			actor.push_back(new Smallgon(this, VIEW_WIDTH, randInt(0, VIEW_HEIGHT - 1), double (5 * (1 + (getLevel() - 1) * 0.1))));
		}
		else if (rand <= S1 + S2)
		{
			actor.push_back(new Smoregon(this, VIEW_WIDTH, randInt(0, VIEW_HEIGHT - 1), 5 * (1 + (getLevel() - 1) * 0.1)));
		}
		else
		{
			actor.push_back(new Snagglegon(this, VIEW_WIDTH, randInt(0, VIEW_HEIGHT - 1), 10 * (1 + (getLevel() - 1) * 0.1)));
		}
		m_aliens++;
	}
	
	// This code is here merely to allow the game to build, run, and terminate after you hit enter.
	// Notice that the return value GWSTATUS_PLAYER_DIED will cause our framework to end the current level.
	vector<Actor*>::iterator it;
	for (it = actor.begin(); it != actor.end();it++)
	{
		(*it)->doSomething();
	}
	
	vector<Actor*>::iterator it2; 
	it2 = actor.begin(); 
	while (it2 != actor.end())
	{
		if (!((*it2)->isAlive()))
		{
			if ((*it2)->isAlien())
				m_aliens--;
		
			delete (*it2); 
			it2 = actor.erase(it2);
		}
		else
			it2++; 
	}
	if ((randInt(0, 16)) == 1)
	{
		actor.push_back(new Star(IID_STAR, VIEW_WIDTH - 1, randInt(0, VIEW_HEIGHT), 0,  double(randInt(5.0, 50.0)/100.0), 3)); 
	}

	m_ship->doSomething();
	if (!(m_ship->isAlive()))
	{
		decLives();
		return GWSTATUS_PLAYER_DIED;
	}
	if (numofAliensDestroyed() >= (6 + (4 * getLevel())))
	{
		playSound(SOUND_FINISHED_LEVEL); 
		return GWSTATUS_FINISHED_LEVEL;
	}
	return GWSTATUS_CONTINUE_GAME;
}

void StudentWorld::addObj(Actor* obj)
{
	actor.push_back(obj);
}

double StudentWorld::getCabbage()
{
	double x = m_ship->cabbagePct();
	return ((x / 30.0) * 100.0);
}

int StudentWorld::getHealth()
{
	int x = m_ship->hitPoints(); 
	return ((x / 50.0) * 100); 
}

int StudentWorld::getTorpedo()
{
	return ship()->numTorpedoes();
}

void StudentWorld::setText()
{
	int lives = getLives();
	int score = getScore();
	int level = getLevel();
	int cabbageamt = getCabbage();
	int torpedoes = getTorpedo();
	int health = getHealth(); 
	stringstream s;
	s << "Lives: " << lives <<  " Health: " << health << "%" << "  Score: " << score << " Level: " << level<< " Cabbages: "<< cabbageamt << "%" <<  " Torpedoes: " << torpedoes;

	string text = s.str();
	setGameStatText(text);
}
NachenBlaster* StudentWorld::getCollidingPlayer(Actor* a)
{
	if (a != nullptr && ship() != nullptr)
	{
		if (a->areColliding(ship()))
			return ship();
	}
	return nullptr;
}

Actor* StudentWorld::getCollidingAlien(Actor* a)
{
	for (int i = 0; i < actor.size(); i++)
	{
		if (actor[i]->isAlien())
		{
			if (a->areColliding(actor[i]))
			{
				return actor[i];
			}
		}
	}
	return nullptr;
}

Actor* StudentWorld::getCollidingProjectile(Actor* a)
{
	for (int i = 0; i < actor.size(); i++)
	{
		if (actor[i]->isProjectile())
		{
			if (a->areColliding(actor[i]))
			{
				return actor[i];
			}
		}
	}
	return nullptr;
}

bool StudentWorld::isAlien(Actor *a)
{
	if (a->getimageID() == IID_SMALLGON || a->getimageID() == IID_SMOREGON || a->getimageID() == IID_SNAGGLEGON)
	{
		m_aliens++;
		return true;
	}
	return false;
}
void StudentWorld::cleanUp()
{
	vector<Actor*>::iterator it3;
	it3 = actor.begin();
	while (it3 != actor.end())
	{
		delete (*it3);
		it3 = actor.erase(it3);
	}
	if (m_ship != nullptr)
	{
		delete m_ship;
		m_ship = nullptr;
	}
}

StudentWorld::~StudentWorld()
{
	cleanUp();
	delete m_ship; 
}
