#ifndef GAME_H
#define GAME_H
class Server;
#include "Engine/util/IObserverTimer.h"
#include "Engine/NetworkEngine/IObserverSocketRecv.h"
#include "Map.h"
#include "Engine/MainEngine.h"


class Server : public Engine::IObserverTimer, public Engine::IObserverSocketRecv
{
    public:
        Server();
        virtual ~Server();

        void run();
        void updateTimer(unsigned int delay);
        void updateRecv(Engine::Socket *,Engine::Paquet& paquet);
        Map *getMap();
        MainEngine* getEngine();
    protected:
    private:
    Map *map;
    MainEngine* engine;
};

#endif // GAME_H
