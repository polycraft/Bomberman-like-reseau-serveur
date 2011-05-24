#include "Bomberman.h"
#include "../Engine/util/Timer.h"

Bomberman::Bomberman(Socket *sock,map<EPropertyBomberman,Property*>& property):socket(sock),stop(false)
{
    this->property=property;
    thread = sock->run(&stop);
}

Bomberman::Bomberman(Socket *sock,int id):socket(sock),stop(false)
{
	this->property[PB_id]=new Property(id);
	thread = sock->run(&stop);
}

Bomberman::~Bomberman()
{
    map<EPropertyBomberman,Property*>::iterator it;

    for ( it=property.begin() ; it != property.end(); it++ )
    {
        delete (*it).second;
    }
    stop=true;
    Threadable::join(thread);
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

void Bomberman::updateRecv(Socket *sock,const char *str,int size)
{

}
