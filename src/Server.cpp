#include "Server.h"

#include "GameType/Classic/Classic.h"
#include <sstream>
#include "Loader/LoaderMap.h"

Server::Server()
{
    engine =  new MainEngine();

    //loaderMap
    Loader *loaderMap=new LoaderMap();
    ManagerRessource::addLoader("map",loaderMap);

	map = ManagerRessource::getRessource<Map>("src/ressource/map/test.map");
	cout << "Map loaded"<<endl;

	Socket *socket = new Socket(5001,TP_TCP);
	GameType *gameType=new GameTypeSpace::Classic(this,socket);


    bool continuer=true;
	while(continuer)
	{
        gameType->update();
        continuer=engine->run();
	}
}

Server::~Server()
{
    //dtor
}

void Server::updateTimer(unsigned int delay)
{

}

Map *Server::getMap()
{
    return map;
}

MainEngine* Server::getEngine()
{
    return engine;
}


void Server::updateRecv(Socket *sock,Paquet& paquet)
{

}
