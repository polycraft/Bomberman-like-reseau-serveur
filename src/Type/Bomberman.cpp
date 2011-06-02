#include "Bomberman.h"
#include "../Engine/util/Timer.h"
#include "Paquet.h"

Bomberman::Bomberman(Socket *sock, GameType *gameType,map<EPropertyBomberman,Property*>& property):socket(sock),stop(false),gameType(gameType)
{
    this->property=property;

	socket->addObserverRecv(this);
    thread = sock->run(&stop);
}

Bomberman::Bomberman(Socket *sock,GameType *gameType,int id):socket(sock),stop(false),gameType(gameType)
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

void Bomberman::updateRecv(Socket *sock,Paquet& paquet)
{
    char type=(paquet.getData())[0];
    switch(type)
    {
        case 'b'://Bombe
        {
            PaquetBomb *paquetBomb=paquet.getData<PaquetBomb*>();

            //Paquet provient bien du bon joueur
            if(paquetBomb->idBomber==this->getProperty<int>(PB_id))
            {
                gameType->updateNetwork(this,paquet);
            }
        }
        break;
        case 'm'://Move
        {
            PaquetMove *paquetMove=paquet.getData<PaquetMove*>();

            //Paquet provient bien du bon joueur
            if(paquetMove->idBomber==this->getProperty<int>(PB_id))
            {
                gameType->updateNetwork(this,paquet);
            }
        }
        break;
        case 'a'://Demande d'information
        {
            PaquetAsk *paquetAsk=paquet.getData<PaquetAsk*>();
            switch(paquetAsk->paquet)
            {
                case 'i'://id
                {
                    PaquetId paquetId={'i', Engine::Timer::getTimer()->getTime(),this->getProperty<int>(PB_id)};
                    this->sendData<PaquetId>(&paquetId);
                }
                break;
            }
        }
        break;
    }
}

void Bomberman::sendData(Paquet &paquet)
{
    socket->sendData(paquet);
}

bool CompareBomberman::operator()(const Bomberman* a,const Bomberman *b)
{
    return a->getProperty<int>(PB_id)<b->getProperty<int>(PB_id);
}
