#ifndef GAME_H
#define GAME_H

#include "Engine/util/IObserverTimer.h"
#include "Engine/NetworkEngine/IObserverSocketRecv.h"
#include "Engine/MainEngine.h"

class Map;

class Server : public Engine::IObserverTimer, public Engine::IObserverSocketRecv
{
    public:
        Server();
        virtual ~Server();

        void run();
        void updateTimer(unsigned int delay);
        void updateRecv(Engine::Socket *,Engine::Paquet& paquet);
        Map *getMap();
        Engine::MainEngine* getEngine();
    protected:
    private:
    Map *map;
    Engine::MainEngine* engine;
};

#endif // GAME_H
