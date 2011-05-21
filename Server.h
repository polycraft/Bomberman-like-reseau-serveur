#ifndef GAME_H
#define GAME_H
#include "Engine/util/IObserverTimer.h"
#include "Map.h"
#include "Engine/MainEngine.h"


class Server : public Engine::IObserverTimer
{
    public:
        Server();
        virtual ~Server();

        void run();
        void updateTimer(unsigned int delay);

        Map *getMap();
        MainEngine* getEngine();
    protected:
    private:
    Map *map;
    MainEngine* engine;
};

#endif // GAME_H
