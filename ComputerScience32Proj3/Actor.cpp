#include "Actor.h"
#include <iostream>
#include "StudentWorld.h"
#include <math.h>
using namespace std;

const int HIT_BY_SHIP = 0; 
const int  HIT_BY_PROJECTILE= 1; 

int euclidian_dist(int X1, int X2, int Y1, int Y2)
{
	//return sqrt(((X2 - X1)  * (X2 - X1)) + ((Y2 - Y1) * (Y2 - Y1)));
	return (pow((X2 - X1), 2)+ pow((Y2 - Y1), 2));
}
// Students:  Add code to this file, Actor.h, StudentWorld.h, and StudentWorld.cpp
Actor::Actor( int ID, double X, double Y, Direction dir, double size, unsigned int depth) :GraphObject(ID, X, Y, dir, size, depth)
{
	m_ID = ID;
	isDead = false; 
}

int Actor::getimageID()
{
	return m_ID;
}
bool Actor::isAlive()
{
	if (isDead == true)
		return false;
	return true;
}

void Actor::setDead()
{
	isDead = true;
}

Explosion::Explosion(StudentWorld* w, double startX, double startY):Actor(IID_EXPLOSION, startX, startY, 0, 1, 0)
{
	m_ticks = 0;
	m_world = w; 
	m_size = 1; 
}


void Explosion::doSomething()
{
	setSize(getSize() * 1.5); 
	m_ticks++; 
	if (m_ticks == 4)
	{
		setDead();
		//return;
	}
}

StudentWorld* Explosion::getWorld()
{
	return m_world; 
}

Star::Star(const int ID, double X, double Y, Direction dir, double size, unsigned int depth) :Actor(IID_STAR, X, Y, 0, double((randInt(5.0, 50.0))/100.0) , 3)
{
	//not sure what to add
}

Star::Star() : Actor(IID_STAR, randInt(0, VIEW_WIDTH), randInt(0, VIEW_HEIGHT), 0, double ((randInt(5.0, 50.0))/100.0), 3)
{
	//not sure what to add
}

void Star::doSomething()
{
	moveTo(getX() - 1, getY());
}

bool Star::isAlive()
{
	if (getX() <= 0)
		return false;
	else
		return true; 
}

DamageableObject::DamageableObject(StudentWorld* w, double startX, double startY, int imageID,
	int startDir, double size, int depth, double hitPoints):Actor(imageID, startX, startY, startDir, size, depth)
{
	m_StudentWorld = w; 
	m_hitPoints = hitPoints; 
}

double DamageableObject::hitPoints() const
{
	return m_hitPoints; 
}

void DamageableObject::increaseHitPoints(double amt)
{
	m_hitPoints += amt; 
}

void DamageableObject::sufferDamage(double amt, int cause)
{
	m_hitPoints -= amt; 
}

StudentWorld* DamageableObject::getWorld()
{
	return m_StudentWorld; 
}


NachenBlaster::NachenBlaster(StudentWorld* StudentWorld):DamageableObject(StudentWorld, 0, 128, IID_NACHENBLASTER, 0, 1, 0, 50)
{
	m_cabbagePoints = 30;
	m_torpedoPoints = 0;
}


void NachenBlaster::increaseTorpedoes(int amt)
{
	m_torpedoPoints += amt; 
}

int NachenBlaster::cabbagePct() const
{
	return m_cabbagePoints;
}

void NachenBlaster::doSomething()
{
	Direction dir = getDirection();
	int ch;
	if (!isAlive())
	{
		return;
	}
	if (hitPoints() <= 0)
	{
		setDead();
		return; 
	}
	if (getWorld()->getKey(ch))
	{
		switch (ch)
		{
		case KEY_PRESS_LEFT:
			if (getX() - 6 >= 0)
			{
				moveTo(getX() - 6, getY());
				break;
			}
			break;
		case KEY_PRESS_RIGHT:
			if (getX() + 6 <= VIEW_WIDTH)
			{
				moveTo(getX() + 6, getY());
				break;
			}
			break;
		case KEY_PRESS_SPACE:
			if (m_cabbagePoints < 5)
				break;
			else
			{
				m_cabbagePoints = cabbagePct() - 5; 
				getWorld()->addObj(new Cabbage(this)); 
				getWorld()->playSound(SOUND_PLAYER_SHOOT); 
				return; 
			}
			break;
		case KEY_PRESS_UP:
			if (getY() + 6 <= VIEW_HEIGHT)
			{
				moveTo(getX(), getY() + 6);
				break;
			}
			break;
		case KEY_PRESS_DOWN:
			if (getY() - 6 >= 0)
			{
				moveTo(getX(), getY() - 6);
				break;
			}
			break;
		case KEY_PRESS_TAB:
		if (m_torpedoPoints <= 0)
				break; 
			else
			{
				getWorld()->addObj(new FlatTorp(this, getWorld(), getX() + 12, getY(), 0));
				getWorld()->playSound(SOUND_TORPEDO);
				return; 
			}
		}
	}
	if (m_cabbagePoints < 30)
		m_cabbagePoints++; 
}


int NachenBlaster::numTorpedoes() const
{
	return m_torpedoPoints; 
}


Cabbage::Cabbage(NachenBlaster* blaster):Actor(IID_CABBAGE, blaster->getX() + 12, blaster->getY(), 0, 0.5, 1)
{
	m_blaster = blaster; 
	m_isDead = false; 
}


void Cabbage::doSomething()
{
	if (getX() < 0 || getX() >= VIEW_WIDTH)
	{
		setDead(); 
		return;
	}
	DamageableObject* p = (DamageableObject*)(m_blaster->getWorld()->getCollidingAlien(this));
	if (p != nullptr)
	{
		p->sufferDamage(2, HIT_BY_PROJECTILE); 
		setDead();
		return;
	}
	if (isAlive())
	{
		moveTo(getX() + 8, getY());
		setDirection(getDirection() + 20);
	}
}

FlatTorp::FlatTorp(Actor* a, StudentWorld* h, int X, int Y, Direction dir):Actor(IID_TORPEDO, a->getX() + 8, a->getY(), dir, 0.5, 1)
{
	m_dir = dir; 
	m_h = h; 
}
void FlatTorp::doSomething()
{
	if (!isAlive())
	{
		return; 
	}
	else
	{
		if (getDirection() == 0)
		{
			DamageableObject *a = (DamageableObject*)(getWorld()->getCollidingProjectile(this)); 
			if (a != nullptr)
			{
				a->sufferDamage(8, HIT_BY_PROJECTILE); 
				setDead(); 
				return; 
			}
			moveTo(getX() + 8, getY()); 
		}
		else if (getDirection() == 180)
		{
			NachenBlaster *p = getWorld()->getCollidingPlayer(this);
			if (p != nullptr)
			{
				p->sufferDamage(8, HIT_BY_PROJECTILE); 
				setDead();
				return;
			}
			moveTo(getX() - 8, getY()); 
		}
	}
}

Turnip::Turnip(Alien* alien, int X, int Y, Direction dir) :Actor(IID_TURNIP, alien->getX() - 14, alien->getY(), dir, 0.5, 1)
{
	m_alien = alien; 
	m_dir = dir; 
}
Alien* Turnip::getAlien()
{
	return m_alien; 
}
void Turnip::doSomething()
{
	if (!isAlive())
	{
		//setDead();
		return; 
	}

	NachenBlaster *p = getAlien()->getWorld()->getCollidingPlayer(this);
	
	if (p != nullptr)
	{
		p->sufferDamage(2, HIT_BY_PROJECTILE); 
		setDead();
		return;
	}
	moveTo(getX() - 6, getY());
	setDirection(getDirection() + 20); 
	p = getAlien()->getWorld()->getCollidingPlayer(this);
	if (p != nullptr)
	{
		p->sufferDamage(2, HIT_BY_PROJECTILE); 
		setDead();
		return;
	}
}

//Alien member functions

Alien::Alien(StudentWorld* gameWorld, int ID, int X, int Y, int hitPoints):DamageableObject(gameWorld, X, Y, ID, 0, 1.5, 1, hitPoints)
{
	m_hitPoints = hitPoints; 
	m_length = 0; 
	m_travelSpeed = 2.0; 
	m_GameWorld = gameWorld; 
	m_tempdir = 0;  
}


int Alien::getHitpoints()
{
	return m_hitPoints; 
}

int Alien::getLength()
{
	return m_length; 
}

double Alien::getTravelSpeed()
{
	return m_travelSpeed;
}

void Alien::setLength(int x)
{
	m_length = x;
}

int Alien::getTempDir()
{
	return m_tempdir; 
}

void Alien::setTempdir(int x)
{
	m_tempdir = x; 
}

void Alien::dropGoodie()
{
	return;
}

void Smoregon::dropGoodie()
{
	int x = randInt(1, 3);
	if (x == 1)
	{
		int chance = randInt(1, 2);
		if (chance == 1)
		{
			getWorld()->addObj(new RepairGoodie(getX(), getY(), IID_REPAIR_GOODIE, this));
		}
		else if (chance == 2)
		{
			getWorld()->addObj(new FlatulenceTorpedoGoodie(getX(), getY(), IID_TORPEDO_GOODIE, this));
		}
	}
}

void Snagglegon::dropGoodie()
{
	int x = randInt(1, 6);
	if (x == 1)
	{
		getWorld()->addObj(new ExtraLifeGoodie(getX(), getY(), IID_LIFE_GOODIE, this));
	}
}

void Alien::setSpeed(int x)
{
	setTravelSpeed(-getTravelSpeed()); 
	setTravelSpeed(x); 
}

void Alien::doSomething()
{
	if (!isAlive())
		return;
	if (getX() < 0)
	{
		setDead(); 
		return; 
	}
	int n = getTravelSpeed();
	if (getWorld()->getCollidingProjectile(this) != nullptr)
	{
		if (hitPoints() <= 0)
		{
			getWorld()->increaseScore(250); 
			setDead();
			getWorld()->playSound(SOUND_DEATH);
			getWorld()->addObj(new Explosion(getWorld(), getX(), getY()));
			getWorld()->alienKilled();
			return; 
		}
		else
		{
			getWorld()->playSound(SOUND_BLAST); 
			return; 
		}
	}

	if (getWorld()->getCollidingPlayer(this) != nullptr)
	{
		getWorld()->ship()->sufferDamage(5, HIT_BY_SHIP);
		setDead(); 
		getWorld()->alienKilled(); 
		getWorld()->increaseScore(250);
		getWorld()->playSound(SOUND_DEATH);
		dropGoodie(); 
		getWorld()->addObj(new Explosion(getWorld(), getX(), getY()));
		return; 
	}
	//check for collsiion
	if (getLength() == 0 || getY() <= 0 || getY() >= VIEW_HEIGHT)
	{
		if (getY() >= VIEW_HEIGHT - 1)
		{
			setTempdir(1);
		}
		else if (getY() <= 0)
		{
			setTempdir(2);
		}
		else if (getLength() == 0)
		{
			int x = randInt(1, 3);
			setTempdir(x);
		}
		int x = randInt(1, 32);
		setLength(x);
	}
	//check to see if nachenblaster to leftand above/below
	if (((getWorld()->ship()->getX() < getX()) && (abs(getWorld()->ship()->getY() - getY()) <= 4)))
	{
		int chance = (20 / getWorld()->getLevel()) + 5;
		int x = randInt(1, chance);
		if (x == 1)
		{
			getWorld()->addObj(new Turnip(this, getX() - 14, getY(), 0));
			getWorld()->playSound(SOUND_ALIEN_SHOOT);
			return;
		}
	}
	else
	{
		if (this->getimageID() == IID_SMOREGON)
		{
			Smoregon(RammingSpeed()); 
		}
	}
	switch (getTempDir())
	{
	case 1:
		moveTo(getX() - n, getY() - n);
		setLength(getLength() - 1);
		break;
	case 2:
		moveTo(getX() - n, getY() + n);
		setLength(getLength() - 1);
		break;
	case 3:
		moveTo(getX() - n, getY());
		setLength(getLength() - 1);
		break;
	}
	if (getWorld()->getCollidingProjectile(this) != nullptr)
	{
		if (hitPoints() <= 0)
		{
			setDead();
			getWorld()->playSound(SOUND_DEATH);
			getWorld()->addObj(new Explosion(getWorld(), getX(), getY()));
			getWorld()->alienKilled();
			return; 
		}
		else
		{
			getWorld()->playSound(SOUND_BLAST);
			return; 
		}
	}
	if (isAlive())
	{
		if (getWorld()->getCollidingPlayer(this) != nullptr)
		{
			getWorld()->increaseScore(250);
			setDead();
			getWorld()->ship()->sufferDamage(5, HIT_BY_SHIP);
			getWorld()->alienKilled();
			dropGoodie();
			getWorld()->playSound(SOUND_DEATH);
			getWorld()->addObj(new Explosion(getWorld(), getX(), getY()));
			return;
		}
	}
}

StudentWorld* Alien::getWorld()
{
	return m_GameWorld; 
} 

Smallgon::Smallgon(StudentWorld* gameWorld, double startX, double startY, double hitPoints):Alien(gameWorld, IID_SMALLGON, VIEW_WIDTH, randInt(0, VIEW_HEIGHT - 1), hitPoints)
{
	m_GameWorld = gameWorld;
}


Smoregon::Smoregon(StudentWorld* gameWorld, double startX, double startY, double hitPoints) :Alien(gameWorld, IID_SMOREGON, VIEW_WIDTH, randInt(0, VIEW_HEIGHT - 1), hitPoints)
{
	m_GameWorld = gameWorld; 
}


void Smoregon::RammingSpeed()
{
	int chance = ((20 / getWorld()->getLevel()) + 5); 
	int x = randInt(1, chance); 
	if (x == 1)
	{
		setDirection(0); 
		setLength(VIEW_WIDTH); 
		setSpeed(5); 
	}
}
Snagglegon::Snagglegon(StudentWorld* gameWorld, double startX, double startY, double hitPoints) : Alien(gameWorld, IID_SNAGGLEGON, VIEW_WIDTH, randInt(0, VIEW_HEIGHT - 1), hitPoints)
{
	m_GameWorld = gameWorld; 
	setTempdir(1);
}


void Snagglegon::doSomething()
{
	if (!isAlive())
		return;
	if (getX() < 0)
	{
		setDead(); 
		return; 
	}
	int n = getTravelSpeed();
	if (getWorld()->getCollidingPlayer(this) != nullptr)
	{
		getWorld()->increaseScore(1000);
		setDead();
		getWorld()->ship()->sufferDamage(5, HIT_BY_SHIP);
		getWorld()->alienKilled();
		dropGoodie();
		getWorld()->playSound(SOUND_DEATH);
		getWorld()->addObj(new Explosion(getWorld(), getX(), getY()));
		return; 
	}

	if (getWorld()->getCollidingProjectile(this) != nullptr)
	{
		if (hitPoints() <= 0)
		{
			getWorld()->increaseScore(1000); 
			setDead();
			dropGoodie();
			getWorld()->alienKilled();
			getWorld()->playSound(SOUND_DEATH);
			getWorld()->addObj(new Explosion(getWorld(), getX(), getY()));
			return; 
		}
		else
		{
			getWorld()->playSound(SOUND_BLAST);
			return; 
		}
	}
	//check for collsiion
	if (getY() <= 0 || getY() >= VIEW_HEIGHT)
	{
		if (getY() >= VIEW_HEIGHT - 1)
		{
			setTempdir(1);
		}
		else if (getY() <= 0)
		{
			setTempdir(2);
		}
	}
	if (((getWorld()->ship()->getX() < getX()) && (abs(getWorld()->ship()->getY() - getY()) <= 4)))
	{
		int chance = (15 / getWorld()->getLevel()) + 10;
		int x = randInt(1, chance);
		if (x == 1)
		{
			getWorld()->addObj(new FlatTorp(this, getWorld(), getX() - 14, getY(), 180));
			getWorld()->playSound(SOUND_TORPEDO);
			return;
		}
	}
	switch (getTempDir())
	{
	case 1:
		moveTo(getX() - n, getY() - n);
		setLength(getLength() - 1);
		break;
	case 2:
		moveTo(getX() - n, getY() + n);
		setLength(getLength() - 1);
		break;
	}
	if (isAlive())
	{
		if (getWorld()->getCollidingPlayer(this) != nullptr)
		{
			getWorld()->increaseScore(1000);
			setDead();
			getWorld()->ship()->sufferDamage(5, HIT_BY_SHIP);
			getWorld()->alienKilled();
			dropGoodie();
			getWorld()->playSound(SOUND_DEATH);
			getWorld()->addObj(new Explosion(getWorld(), getX(), getY()));
			return;
		}
		if (getWorld()->getCollidingProjectile(this) != nullptr)
		{
			if (hitPoints() <= 0)
			{
				getWorld()->increaseScore(1000);
				setDead();
				dropGoodie();
				getWorld()->alienKilled();
				getWorld()->playSound(SOUND_DEATH);
				getWorld()->addObj(new Explosion(getWorld(), getX(), getY()));
				return;
			}
			else
			{
				getWorld()->playSound(SOUND_BLAST);
				return;
			}
		}
	}
}



Goodie::Goodie(int startX, int startY, int imageID, Alien* alien):Actor(imageID, alien->getX(), alien->getY(), 0, 0.5, 1)
{
	m_alien = alien; 
}

Alien* Goodie::getAlien()
{
	return m_alien; 
}

ExtraLifeGoodie::ExtraLifeGoodie(int startX, int startY, int imageID, Alien* alien):Goodie(startX, startY,IID_LIFE_GOODIE, alien)
{
}

void ExtraLifeGoodie::doSomething()
{
	if (!isAlive())
		return; 
	if (getX() < 0 || getX() > VIEW_WIDTH || getY() < 0 || getY() > VIEW_HEIGHT)
	{
		setDead();
		return;
	}
	NachenBlaster *p = getAlien()->getWorld()->getCollidingPlayer(this);
	if (p != nullptr)
	{
		p->getWorld()->increaseScore(100); 
		setDead();
		getAlien()->getWorld()->playSound(SOUND_GOODIE);
		p->getWorld()->incLives(); 
		return;
	}
	//check to see if it collides with a nachenblaster, add plus 100 points to the nachenblaster, add a life, return
		moveTo(getX() - 0.75, getY() - 0.75); 
		p = getAlien()->getWorld()->getCollidingPlayer(this);
		if (p != nullptr)
		{
			p->getWorld()->increaseScore(100);
			setDead();
			getAlien()->getWorld()->playSound(SOUND_GOODIE);
			p->getWorld()->incLives();
			return;
		}
}

RepairGoodie::RepairGoodie(int startX, int startY, int imageID, Alien* alien) :Goodie(startX, startY, IID_REPAIR_GOODIE, alien)
{

}

void RepairGoodie::doSomething()
{
	if (!isAlive())
		return;
	if (getX() < 0 || getX() > VIEW_WIDTH || getY() < 0 || getY() > VIEW_HEIGHT)
	{
		setDead();
		//return;
	}
	NachenBlaster *p = getAlien()->getWorld()->getCollidingPlayer(this);
	if (p != nullptr)
	{
		p->getWorld()->increaseScore(100); 
		setDead(); 
		getAlien()->getWorld()->playSound(SOUND_GOODIE);
		int count = 0; 
		while (p->hitPoints() != 50 && count < 10)
		{
			p->increaseHitPoints(1);
		} 
		return; 
	}
	else
	{
		moveTo(getX() - 0.75, getY() - 0.75);
		NachenBlaster *p = getAlien()->getWorld()->getCollidingPlayer(this);
		if (p != nullptr)
		{
			setDead();
			getAlien()->getWorld()->playSound(SOUND_GOODIE);
			return;
		} 
		p = getAlien()->getWorld()->getCollidingPlayer(this);
		if (p != nullptr)
		{
			p->getWorld()->increaseScore(100);
			setDead();
			getAlien()->getWorld()->playSound(SOUND_GOODIE);
			int count = 0;
			while (p->hitPoints() != 50 && count < 10)
			{
				p->increaseHitPoints(1);
			}
			return;
		}
	}
}

FlatulenceTorpedoGoodie::FlatulenceTorpedoGoodie(int startX, int startY, int minageID, Alien* alien):Goodie(alien->getX(), alien->getY(), IID_TORPEDO_GOODIE, alien)
{

}


void FlatulenceTorpedoGoodie::doSomething()
{
	if (!isAlive())
		return;
	if (getX() < 0 || getX() > VIEW_WIDTH || getY() < 0 || getY() > VIEW_HEIGHT)
	{
		setDead();
		return;
	}
	NachenBlaster *p = getAlien()->getWorld()->getCollidingPlayer(this);
	if (p != nullptr)
	{
		p->getWorld()->increaseScore(100); 
		p->increaseTorpedoes(5); 
		setDead();
		getAlien()->getWorld()->playSound(SOUND_GOODIE);
		return;
	}
	else
	{
		moveTo(getX() - 0.75, getY() - 0.75);
		NachenBlaster *p = getAlien()->getWorld()->getCollidingPlayer(this);
		if (p != nullptr)
		{
			setDead();
			getAlien()->getWorld()->playSound(SOUND_GOODIE); 
			return;
		}
		p = getAlien()->getWorld()->getCollidingPlayer(this);
		if (p != nullptr)
		{
			p->getWorld()->increaseScore(100);
			p->increaseTorpedoes(5);
			setDead();
			getAlien()->getWorld()->playSound(SOUND_GOODIE);
			return;
		}
	}
}

bool Actor::areColliding(Actor* p) 
{
	if (euclidian_dist(getX(), p->getX(), getY(), p->getY()) < pow((0.75 * (getRadius() + p->getRadius())), 2))
	{
		return true;
	}
	else
		return false; 
}




