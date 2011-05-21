#include "Server.h"

#include "GameType/Classic/Classic.h"
#include <sstream>
#include "Loader/LoaderMap.h"

Server::Server()
{
    engine =  new MainEngine(Engine_Event|Engine_Graphic);

    //loaderMap
    Loader *loaderMap=new LoaderMap();
    ManagerRessource::addLoader("map",loaderMap);

	map = ManagerRessource::getRessource<Map>("src/ressource/map/test.map");

	Engine::Camera *camera = new Engine::Camera(map->getWidth()*10/2, 0, 150, map->getWidth()*10/2, map->getHeight()*10, 0, 0, 0, 1);
	engine->getGengine()->addCamera(camera);

	ManagerFont* font=new ManagerFont("src/ressource/font/font.ttf",24);
	string s("Blablbla");
	Text text(s,20,500);
	text.setColor(255,255,255,255);
	font->addText(&text);
	engine->getGengine()->getManagerText().addFont(font);

	map->setEngine(engine);

	GameType *gameType=new GameTypeSpace::Classic(this);


    bool continuer=true;

    std::stringstream out;

	while(continuer)
	{
        //cout << "fps:" << Timer::getTimePerFrame() << endl;

        gameType->update();
        continuer=engine->run(camera);

        std::stringstream out;
        out << static_cast<int>(1000/Timer::getTimePerFrame());
        s=out.str();
    text.setText(s);
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