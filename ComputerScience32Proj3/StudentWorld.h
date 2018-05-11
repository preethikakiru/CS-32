#ifndef STUDENTWORLD_H_
#define STUDENTWORLD_H_

#include "Actor.h"
#include "GameWorld.h"
#include <string>
#include <vector>

// Students:  Add code to this file, StudentWorld.cpp, Actor.h, and Actor.cpp

//class Actor;  

class StudentWorld : public GameWorld
{
public:
    StudentWorld(std::string assetDir);
	virtual ~StudentWorld();

    int init();
    int move();
    void cleanUp();
	bool isAlien(Actor *a); 
	

	void addObj(Actor* x); 
	bool addAlien();
	int numofAliensDestroyed() {return m_record;}
	void alienKilled() { m_record++;  }
	int numOnScreen() { return m_aliens;}
	NachenBlaster* ship() { return m_ship; }
	NachenBlaster* getCollidingPlayer(Actor* a);
	Actor* getCollidingAlien(Actor* a);
	Actor* getCollidingProjectile(Actor* a); 
	int maxAlien() { return maxAliens;  }

	void setText(); 

	double getCabbage(); 
	int getTorpedo();
	int getHealth();
	

private:
	std::string m_assetDir; 
	std::vector<Actor*> actor; 
	NachenBlaster* m_ship; 
	bool isCollision; 
	int m_aliens; 
	int maxAliens; 
	int m_record; 
};

#endif // STUDENTWORLD_H_
