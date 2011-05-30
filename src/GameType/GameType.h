#ifndef GAMETYPE_H
#define GAMETYPE_H
class Bomb;
#include "../Type/Bomb.h"
#include "../Type/Bomberman.h"
#include "../Server.h"
#include "../Type/ManagerExplosion.h"
#include "../Type/ExplosionFlare.h"
#include "../Engine/NetworkEngine/Socket.h"
#include "../Engine/NetworkEngine/IObserverSocketAccept.h"
#include "../Engine/NetworkEngine/IObserverSocketRecv.h"
#include <set>


class GameType : public IObserverSocketAccept
{

public:
	GameType(Server *server,int partTime,Socket *socket);
	virtual ~GameType();
	virtual void update()=0;
    virtual void explode(Bomb* bomb,int speed,int power)=0;
    virtual void updateExplosion(ExplosionFlare *flare,int power,int x,int y)=0;
    virtual void destroyManagerExplosion(ManagerExplosion* manager)=0;
    Server* getServer();
    virtual void updateAccept(Socket* s);
    virtual void updateNetwork(Bomberman* bomberman,Paquet& paquet);
	set<Bomberman*,CompareBomberman>& getPlayerNetwork();
protected:
    Server* server;
    Thread* thread;
    Socket *socket;
    std::set<Bomberman*,CompareBomberman> playerNetwork;
    bool stop;
private:
	int partTime;
};



#endif // GAMETYPE_H
