#include "GameType.h"

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

    //Création d'un nouveau joueur
    playerNetwork.insert(new Bomberman(s,this,id));
}
void GameType::updateNetwork(Bomberman* bomberman,Paquet& paquet)
{
    for(std::set<Bomberman*,CompareBomberman>::iterator it=playerNetwork.begin(); it!=playerNetwork.end(); ++it)
    {
        //Envoie du paquet à tout les joueurs sauf le joueur d'origine
        if((*it)->getProperty<int>(PB_id)!=bomberman->getProperty<int>(PB_id))
        {
            (*it)->sendData(paquet);
        }
    }
}

set<Bomberman*,CompareBomberman>& GameType::getPlayerNetwork()
{
    return playerNetwork;
}