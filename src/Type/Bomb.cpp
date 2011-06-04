#include "Bomb.h"
#include "../Engine/util/Timer.h"
#include "../GameType/GameType.h"
#include "../Engine/ManagerRessource.h"

using namespace Engine;
class Bomberman;

Bomb::Bomb(GameType* gameType,Bomberman *owner, int time, int speed, int power):gameType(gameType)
{
	this->owner = owner;
	this->speed = speed;
	this->power = power;
	this->time = time;
	Timer::getTimer()->addListenerOnce(this,time);
	this->attach(ManagerRessource::getRessource("src/ressource/object/bomb.obj"),
		ManagerRessource::getRessource("src/ressource/texture/bomb.jpg"));
}

Bomb::~Bomb()
{

}

void Bomb::explode()
{
    Timer::getTimer()->removeListenerOnce(this,time);
    updateTimer(time);
}

void Bomb::updateTimer(unsigned int delay)
{
	this->setVisible(false);
	this->gameType->explode(this,speed,power);
}


EType Bomb::getType()
{
	return T_Bomb;
}

Bomberman* Bomb::getOwner()
{
    return owner;
}
