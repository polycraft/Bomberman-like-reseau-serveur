#include "Bomberman.h"
#include "../Engine/util/Timer.h"

Bomberman::Bomberman(Socket *sock,map<EPropertyBomberman,Property*>& property):socket(sock)
{
    this->property=property;
}

Bomberman::Bomberman(Socket *sock,int id):socket(sock)
{
	this->property[PB_id]=new Property(id);
}

Bomberman::~Bomberman()
{
    map<EPropertyBomberman,Property*>::iterator it;

    for ( it=property.begin() ; it != property.end(); it++ )
    {
        delete (*it).second;
    }
}

EType Bomberman::getType()
{
	return T_Bomberman;
}

void Bomberman::updateTimer(unsigned int delay)
{
    if(delay==this->getProperty<int>(PB_timeInvinsible))
    {
        this->setProperty<int>(PB_invinsible,false);
        Timer::getTimer()->removeListener(this,100);
    }
    else if(delay==100)
    {
        this->setVisible(!this->getVisible());
    }
    else
    {
        this->setProperty<bool>(PB_canPutBomb,true);
    }
}

void Bomberman::setInvinsible(int time)
{
    if(this->getProperty<bool>(PB_invinsible))
    {
        Timer::getTimer()->removeListenerOnce(this,this->getProperty<int>(PB_timeInvinsible));
    }
    Timer::getTimer()->addListenerOnce(this,time);
    this->setProperty<int>(PB_timeInvinsible,time);
    this->setProperty<int>(PB_invinsible,true);

    Timer::getTimer()->addListener(this,100);
}

void Bomberman::lostLife(int nb)
{
    setProperty<int>(PB_life,getProperty<int>(PB_life)-nb);
}
