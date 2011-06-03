#ifndef GAMETYPE_H
#define GAMETYPE_H

#include "../Engine/NetworkEngine/IObserverSocketAccept.h"
#include "../Engine/NetworkEngine/Paquet.h"
#include <set>
#include "../Type/CompareBomberman.h"
#include "../Type/Bomberman.h"

class Bomb;
class Server;
class Bomberman;
class ExplosionFlare;
class CompareBomberman;
class ManagerExplosion;

class GameType : public Engine::IObserverSocketAccept
{

public:
	GameType(Server *server,int partTime,Engine::Socket *socket);
	virtual ~GameType();
	virtual void update()=0;
    virtual void explode(Bomb* bomb,int speed,int power)=0;
    virtual void updateExplosion(ExplosionFlare *flare,int power,int x,int y)=0;
    virtual void destroyManagerExplosion(ManagerExplosion* manager)=0;
    Server* getServer();
    virtual void updateAccept(Engine::Socket* s);
    template <class T> void updateNetwork(Bomberman* bomberman,T& paquet)
    {
        for(std::set<Bomberman*,CompareBomberman>::iterator it=playerNetwork.begin(); it!=playerNetwork.end(); ++it)
        {
            //Envoie du paquet à tout les joueurs sauf le joueur d'origine
            if((*it)->getProperty<int>(PB_id)!=bomberman->getProperty<int>(PB_id) && (*it)->isConnected())
            {
                (*it)->sendData<T>(&paquet);
            }
        }
    }

    void updateNetwork(Bomberman* bomberman,Engine::Paquet& paquet);

    template <class T> void updateAllNetwork(T& paquet)
    {
        for(std::set<Bomberman*,CompareBomberman>::iterator it=playerNetwork.begin(); it!=playerNetwork.end(); ++it)
        {
            if((*it)->isConnected())
            {
                (*it)->sendData<T>(&paquet);
            }
        }
    }

    void updateAllNetwork(Engine::Paquet& paquet);

	set<Bomberman*,CompareBomberman>& getPlayerNetwork();
	virtual void updateRecvBomberman(Bomberman* bomberman,Engine::Socket *sock,Engine::Paquet& paquet)=0;
protected:
    Server* server;
    Engine::Thread* thread;
    Engine::Socket *socket;
    std::set<Bomberman*,CompareBomberman> playerNetwork;
    bool stop;
private:
	int partTime;
};



#endif // GAMETYPE_H
