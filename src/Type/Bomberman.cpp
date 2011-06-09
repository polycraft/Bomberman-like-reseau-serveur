#include "Bomberman.h"

#include "../Engine/util/Timer.h"
#include "Paquet.h"
#include "../GameType/GameType.h"

using namespace Engine;

Bomberman::Bomberman(Socket *sock, GameType *gameType,map<EPropertyBomberman,Property*>& property):socket(sock),stop(false),gameType(gameType),connected(false)
{
    this->property=property;

	socket->addObserverRecv(this);
    thread = sock->run(&stop);
}

Bomberman::Bomberman(Socket *sock,GameType *gameType,int id):socket(sock),stop(false),gameType(gameType)
{
	this->property[PB_id]=new Property(id);
	thread = sock->run(&stop);
	socket->addObserverRecv(this);
}

Bomberman::~Bomberman()
{
    //destruction des bonus
	set<Bonus*>::iterator it2;
	for(it2 = this->bonusList.begin() ; it2 != this->bonusList.end() ; it2++)
	{
		//delete (*it);
	}

    map<EPropertyBomberman,Property*>::iterator it;

    for ( it=property.begin() ; it != property.end(); it++ )
    {
        delete (*it).second;
    }
    stop=true;
    //Threadable::join(thread);
    delete socket;

}

EType Bomberman::getType()
{
	return T_Bomberman;
}

void Bomberman::updateTimer(unsigned int delay)
{
    if(delay==this->getProperty<int>(PB_timeInvincible))
    {
        this->setProperty<bool>(PB_invincible,false);
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
    if(this->getProperty<bool>(PB_invincible))
    {
        Timer::getTimer()->removeListenerOnce(this,this->getProperty<int>(PB_timeInvincible));
    }
    Timer::getTimer()->addListenerOnce(this,time);
    this->setProperty<int>(PB_timeInvincible,time);
    this->setProperty<int>(PB_invincible,true);

    Timer::getTimer()->addListener(this,100);
}

void Bomberman::lostLife(int nb)
{
    setProperty<int>(PB_life,getProperty<int>(PB_life)-nb);
}

void Bomberman::updateRecv(Socket *sock,Paquet& paquet)
{
    gameType->updateRecvBomberman(this,sock,paquet);
    char type=(paquet.getData())[0];
    switch(type)
    {
        case 'n':
        {
            PaquetName *paquetName=paquet.getData<PaquetName*>();

            this->setName(string(paquetName->name));
        }
        break;
        default:

        break;
    }
}

void Bomberman::sendData(Paquet &paquet)
{
    socket->sendData(paquet);
}

bool Bomberman::isConnected()
{
    return connected;
}

void Bomberman::setConnected(bool c)
{
    connected=c;
}

string& Bomberman::getName()
{
    return name;
}

void Bomberman::setName(string name)
{
    this->name=name;
}

Socket* Bomberman::getSocket()
{
    return socket;
}

void Bomberman::addBonus(Bonus *bonus)
{
	this->bonusList.insert(bonus);
}

void Bomberman::remove(Bonus *bonus)
{
	set<Bonus*>::iterator it;
	for(it = this->bonusList.begin() ; it != this->bonusList.end() ; it++)
	{
		if((*it) == bonus)
		{
			//suppression a voir si besoin
		}
	}
}
