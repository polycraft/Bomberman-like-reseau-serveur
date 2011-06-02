#include "GameType.h"
#include "../Type/Bomb.h"
#include "../Type/Bomberman.h"
#include "../Server.h"
#include "../Type/ManagerExplosion.h"
#include "../Type/ExplosionFlare.h"

using namespace Engine;

GameType::GameType(Server *server,int partTime,Socket *socket):partTime(partTime),server(server)
{
	this->socket= socket;
    socket->addObserverAccept(this);
    stop=false;
    thread=socket->run(&stop);
}

GameType::~GameType()
{

}

Server* GameType::getServer()
{
    return server;
}

void GameType::updateAccept(Socket* s)
{
	cout << "Connection InComming" << endl;
    //Recherche d'un id libre
    int id=0;

    for(std::set<Bomberman*,CompareBomberman>::iterator it=playerNetwork.begin(); it!=playerNetwork.end(); ++it)
    {
        if((*it)->getProperty<int>(PB_id)==id)
            id++;//id déjà utilisé
        else
            break;//id libre
    }

    socket->addObserverRecv(server);

    //Création d'un nouveau joueur
    playerNetwork.insert(new Bomberman(s,this,id));
}

set<Bomberman*,CompareBomberman>& GameType::getPlayerNetwork()
{
    return playerNetwork;
}
