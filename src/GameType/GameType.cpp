#include "GameType.h"
#include "../Type/Bomb.h"
#include "../Type/Bomberman.h"
#include "../Type/Paquet.h"
#include "../Server.h"
#include "../Type/ManagerExplosion.h"
#include "../Type/ExplosionFlare.h"
#include "../Engine/util/Timer.h"

using namespace Engine;

GameType::GameType(Server *server,int partTime,Socket *socket):partTime(partTime),server(server)
{
    this->socket= socket;
    socket->addObserverAccept(this);
    stop=false;
    Threadable::initMutex(mutex);
    thread=socket->run(&stop);

}

GameType::~GameType()
{
    Threadable::stopMutex(mutex);
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

    readBomberman();
    for(std::set<Bomberman*,CompareBomberman>::iterator it=playerNetwork.begin(); it!=playerNetwork.end(); ++it)
    {
        if((*it)->getProperty<int>(PB_id)==id)
            id++;//id déjà utilisé
        else
            break;//id libre
    }
    releaseBomberman();

    s->addObserverRecv(server);
    s->addObserverRecv(this);

    //Création d'un nouveau joueur
    playerNetwork.insert(new Bomberman(s,this,id));
}

set<Bomberman*,CompareBomberman>& GameType::getPlayerNetwork()
{
    return playerNetwork;
}

void GameType::updateNetwork(Bomberman* bomberman,Paquet& paquet)
{
    readBomberman();
    for(std::set<Bomberman*,CompareBomberman>::iterator it=playerNetwork.begin(); it!=playerNetwork.end(); ++it)
    {
        //Envoie du paquet à tout les joueurs sauf le joueur d'origine
        if((*it)->getProperty<int>(PB_id)!=bomberman->getProperty<int>(PB_id) && (*it)->isConnected())
        {
            (*it)->sendData(paquet);
        }
    }
    releaseBomberman();
}

void GameType::updateAllNetwork(Paquet& paquet)
{
    readBomberman();
    for(std::set<Bomberman*,CompareBomberman>::iterator it=playerNetwork.begin(); it!=playerNetwork.end(); ++it)
    {
        if((*it)->isConnected())
        {

            (*it)->sendData(paquet);
        }
    }
    releaseBomberman();
}

void GameType::updateDisconnect(Socket* socket)
{
    readBomberman();
    for(std::set<Bomberman*,CompareBomberman>::iterator it=playerNetwork.begin(); it!=playerNetwork.end(); ++it)
    {
        if((*it)->getSocket()==socket)
        {
            Bomberman* bomberman=*it;
            playerNetwork.erase(it);
            releaseBomberman();

            //On prévient de la deconnexion
            PaquetDeconnect paquetDeconnect={'d', Engine::Timer::getTimer()->getTime(),bomberman->getProperty<int>(PB_id)};
            updateAllNetwork<PaquetDeconnect>(paquetDeconnect);

            //On supprime le bomberman
            delete bomberman;
            return;
        }
    }
    releaseBomberman();
}

void GameType::readBomberman()
{
    Threadable::P(mutex);
}

void GameType::releaseBomberman()
{
    Threadable::V(mutex);
}
