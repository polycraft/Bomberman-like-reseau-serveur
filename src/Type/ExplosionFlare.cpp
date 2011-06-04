#include "ExplosionFlare.h"

#include "ManagerExplosion.h"
#include "../Engine/util/Timer.h"
#include "../GameType/GameType.h"
#include "../Server.h"
#include "../Map.h"

using namespace Engine;
class Bomberman;

ExplosionFlare::ExplosionFlare(int x, int y, Bomberman* owner, int speed, int power, EExplose typeExplose, GameType *gametype, ManagerExplosion *manager)
{
	this->x=x;
	this->y=y;
	this->owner = owner;
	this->speed = speed;
	this->power = 2;
	this->powercurrent=0;
	this->typeExplosion = typeExplose;
	this->isEnd = false;
	this->gameType = gametype;
	this->manager = manager;

	Timer::getTimer()->addListener(this,100/this->speed);


	if(this->typeExplosion == T_Emitter)
	{
	    this->powercurrent=0;
		this->listeExplosions.push_back(new Explosion(T_Emitter,x,y));
		this->gameType->getServer()->getMap()->addObject(this->listeExplosions.back(),this->x,this->y, T_Dyn);
	}
	else
	{

	    this->powercurrent=0;
	}


}

ExplosionFlare::~ExplosionFlare()
{
	vector<Explosion*>::iterator it=this->listeExplosions.begin();
	while(it < this->listeExplosions.end())
	{
		(*it)->destroy();
		this->gameType->getServer()->getMap()->set(NULL,(*it)->getX(),(*it)->getY());
		it++;
	}
}

void ExplosionFlare::nextExplose()
{

	if(this->typeExplosion != T_Emitter)
	{

		int x, y;
		x=this->x;
		y=this->y;
		switch(this->typeExplosion)
		{
		case T_Left:
			x-=powercurrent;
			break;
	    case T_Right:
			x+=powercurrent;
			break;
        case T_Up:
            y+=powercurrent;
			break;
        case T_Down:
            y-=powercurrent;
        break;
		}

		if(this->listeExplosions.size()!=0)
		{
		    this->listeExplosions.back()->changeExplose(this->typeExplosion);
		}

        this->listeExplosions.push_back(new Explosion(T_End,x,y));
        this->gameType->getServer()->getMap()->addObject(this->listeExplosions.back(),x,y, T_Dyn);



	}
	else
	{
	    endExplose();
	}
}

void ExplosionFlare::endExplose()
{
	this->manager->addAnEnd();
	Timer::getTimer()->removeListener(this,100/this->speed);


}

EExplose ExplosionFlare::getType()
{
	return this->typeExplosion;
}

void ExplosionFlare::updateTimer(unsigned int delay)
{

		this->powercurrent++;
		this->gameType->updateExplosion(this,this->powercurrent,this->x,this->y);

		if(this->powercurrent >= this->power)
		{
			endExplose();
		}

}

Bomberman* ExplosionFlare::getOwner()
{
	return this->owner;
}
