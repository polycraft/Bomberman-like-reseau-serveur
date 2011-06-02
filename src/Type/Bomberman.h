#ifndef BOMBERMAN_H
#define BOMBERMAN_H

#include "Type.h"
#include "../Engine/NetworkEngine/IObserverSocketRecv.h"
#include "../Engine/NetworkEngine/Socket.h"
#include "../Engine/util/IObserverTimer.h"
#include "Property.h"
#include <map>


class GameType;


typedef enum EPropertyBomberman
{
    PB_id=0,
    PB_bombPower=1,
    PB_vitesse=2,
    PB_nbBomb=3,
    PB_nbBombMax=4,
    PB_timerBomb=5,
    PB_timerPutBomb=6,
    PB_vitesseExplode=7,
    PB_life=8,
    PB_canPutBomb=9,
    PB_invinsible=10,
    PB_timeInvinsible=11
} EPropertyBomberman;

class Bomberman : public Type, public Engine::IObserverTimer,public Engine::IObserverSocketRecv
{

public:
    Bomberman(Engine::Socket *sock, GameType *gameType,std::map<EPropertyBomberman,Property*>& property);
    Bomberman(Engine::Socket *sock, GameType *gameType,int id);
    ~Bomberman();
    EType getType();

    template <typename T>const T& getProperty(EPropertyBomberman prop) const
    {
        return this->property.find(prop)->second->getValue<T>();
    }

    template <typename T> void setProperty(EPropertyBomberman prop,T val)
    {
        map<EPropertyBomberman,Property*>::iterator it=this->property.find(prop);

        //Nouveau élément
        if(it==this->property.end())
        {
            this->property[prop]=new Property(val);
        }
        else
        {
            (*it).second->setValue<T>(val);
        }
    }

    void updateTimer(unsigned int delay);

    void setInvinsible(int time);
    void lostLife(int nb=1);

    void updateRecv(Engine::Socket *sock,Engine::Paquet &paquet);
    void sendData(Engine::Paquet &paquet);
	template<class T> void sendData(T *data)
		{
				socket->sendData<T>(data);
		}

    bool isConnected();
    void setConnected(bool c);

protected:
    std::map<EPropertyBomberman,Property*> property;
    Engine::Thread* thread;
    Engine::Socket* socket;
    bool stop;
    GameType *gameType;
    bool connected;
};



#endif // BOMBERMAN_H
