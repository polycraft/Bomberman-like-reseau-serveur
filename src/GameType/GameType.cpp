#include "GameType.h"

GameType::GameType(Server *server,int partTime):partTime(partTime),server(server)
{

}

GameType::~GameType()
{

}

Server* GameType::getServer()
{
    return server;
}


