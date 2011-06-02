#include "Server.h"

#include "GameType/Classic/Classic.h"
#include <sstream>
#include "Loader/LoaderMap.h"
#include "Engine/ManagerRessource.h"
#include "Map.h"
#include "Type/Paquet.h"
#include "Engine/util/Timer.h"

using namespace Engine;
using namespace std;

Server::Server()
{
    engine =  new MainEngine();

    //loaderMap
    Loader *loaderMap=new LoaderMap();
    ManagerRessource::addLoader("map",loaderMap);

    mapName="src/ressource/map/test.map";

	map = ManagerRessource::getRessource<Map>(mapName);
	cout << "Map loaded"<<endl;

	Socket *socket = new Socket(5001,TP_TCP);
	socket->addObserverRecv(this);
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
    char type=(paquet.getData())[0];
    switch(type)
    {
        case 'a'://Demande d'information
        {
            PaquetAsk *paquetAsk=paquet.getData<PaquetAsk*>();
            switch(paquetAsk->paquet)
            {
                case 'c'://map
                {
                    PaquetMap paquetMap={'c', Engine::Timer::getTimer()->getTime(),""};
                    mapName.copy(paquetMap.name,mapName.size());
                    sock->sendData<PaquetMap>(&paquetMap);
                }
                break;
            }
        }
        break;
        case 'g':
        {
            PaquetPing paquetPing={'g', Engine::Timer::getTimer()->getTime()};
            sock->sendData<PaquetPing>(&paquetPing);
        }
        break;
    }
}
