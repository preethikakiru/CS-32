#ifndef ACTOR_H_
#define ACTOR_H_
#include "GraphObject.h"

class StudentWorld; 

// Students:  Add code to this file, Actor.cpp, StudentWorld.h, and StudentWorld.cpp

using Direction = int; 


 //Base Class for Actor for Actor
class Actor :public GraphObject
{
public:
	Actor(int ID, double X, double Y, Direction dir, double size, unsigned int depth);
	virtual void doSomething() = 0;
	int getimageID();
	virtual bool isAlive(); 
	bool areColliding(Actor* other); 
	void setDead(); 
	virtual bool isAlien() { return false; }
	virtual bool isProjectile() { return false;  }
private:
	int m_ID;
	bool isDead; 
};

class DamageableObject : public Actor
{
public:
	DamageableObject(StudentWorld* w, double startX, double startY, int imageID,
		int startDir, double size, int depth, double hitPoints);

	// How many hit points does this actor have left?
	double hitPoints() const;

	// Increase this actor's hit points by amt.
	virtual void increaseHitPoints(double amt);

	// This actor suffers an amount of damage caused by being hit by either
	// a ship or a projectile (see constants above).
	virtual void sufferDamage(double amt, int cause);

	StudentWorld* getWorld(); 
private:
	StudentWorld* m_StudentWorld; 
	double m_hitPoints; 
};

//Star Class
class Star :public Actor
{
public:
	Star();
	Star(const int ID, double X, double Y, Direction dir, double size, unsigned int depth);
	virtual void doSomething();
	virtual bool isAlive(); 
private:
};

//Nachenblaster class
class NachenBlaster :public DamageableObject
{
public:
	NachenBlaster(StudentWorld* StudentWorld);
	virtual void doSomething();
	void increaseTorpedoes(int amt);
	int cabbagePct() const;
	int numTorpedoes() const;
private:
	int m_health; 
	int m_cabbagePoints;
	int m_torpedoPoints; 
};

//Projectile Classes
class Cabbage:public Actor
{
public:
	Cabbage(NachenBlaster* blaster);
	virtual void doSomething();
	virtual bool isProjectile() { return true; }
private:
	NachenBlaster* m_blaster; 
	bool m_isDead; 
};

class FlatTorp:public Actor
{
public:
	FlatTorp(Actor* a, StudentWorld* h, int X, int Y, Direction dir); 
	virtual void doSomething();
	Actor* getActor() { return m_a; }
	virtual bool isProjectile() { return true; }
	StudentWorld* getWorld() { return m_h; }; 
private:
	Actor* m_a; 
	Direction m_dir; 
	StudentWorld* m_h; 
};
//Alien Class

class Alien :public DamageableObject
{
public:
	Alien(StudentWorld* gameWorld, int ID, int X, int Y, int hitPoints); 
	virtual void doSomething(); 
	int getHitpoints(); 
	int getLength(); 
	double getTravelSpeed(); 
	virtual void  setTravelSpeed(int x) { m_travelSpeed += x; }
	StudentWorld* getWorld();
	void setLength(int x); 
	int getTempDir(); 
	virtual void setTempdir(int x); 
	virtual void dropGoodie(); 
	virtual bool isAlien() { return true; }
	virtual void RammingSpeed() { ; }
	virtual void setSpeed(int x); 
private:
	StudentWorld* m_GameWorld; 
	int m_hitPoints; 
	int m_length; 
	double m_travelSpeed; 
	//1 means down and left, 2, up and left, 3 is left
	int m_tempdir; 
};

class Smallgon :public Alien
{
public:
	Smallgon(StudentWorld* gameWorld, double startX, double startY, double hitPoints);   
private:
	int m_ID;
	StudentWorld* m_GameWorld; 
};

class Smoregon :public Alien
{
public:
	Smoregon(StudentWorld* gameWorld, double startX, double startY, double hitPoints);
	virtual void dropGoodie();
	virtual void RammingSpeed(); 
private:
	int m_ID;
	StudentWorld* m_GameWorld;
};

class Snagglegon :public Alien
{
public:
	Snagglegon(StudentWorld* gameWorld, double startX, double startY, double hitPoints); 
	virtual void doSomething(); 
	virtual void dropGoodie();
private:
	StudentWorld* m_GameWorld; 
};

class Turnip :public Actor
{
public:
	Turnip(Alien* alien, int X, int Y, Direction Dir);
	virtual void doSomething();
	Alien* getAlien(); 
	virtual bool isProjectile() { return true; }
private:
	StudentWorld* t; 
	Alien* m_alien;
	Direction m_dir;
};


class Goodie: public Actor
{
public:
	Goodie(int startX, int startY, int imageID, Alien* alien);
	Alien* getAlien(); 
private:
	Alien* m_alien; 
};

class ExtraLifeGoodie : public Goodie
{
public:
	ExtraLifeGoodie(int startX, int startY, int imageID, Alien* alien); 
	virtual void doSomething(); 
};

class RepairGoodie :public Goodie
{
public:
	RepairGoodie(int startX, int startY, int imageID, Alien* alien); 
	virtual void doSomething(); 
};

class FlatulenceTorpedoGoodie :public Goodie
{
public:
	FlatulenceTorpedoGoodie(int startX, int startY, int minageID, Alien* alien);
	virtual void doSomething(); 
};

class Explosion:public Actor
{
public:
	Explosion(StudentWorld* w, double startX, double startY);
	StudentWorld* getWorld(); 
	virtual void doSomething();
private:
	StudentWorld* m_world;
	int m_ticks; 
	double m_size; 
};

#endif