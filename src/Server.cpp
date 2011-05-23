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

	GameType *gameType=new GameTypeSpace::Classic(this);


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
