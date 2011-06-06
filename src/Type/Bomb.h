#ifndef BOMB_H
#define BOMB_H

#include "Type.h"
#include "../Engine/util/IObserverTimer.h"


class GameType;
class Bomberman;

class Bomb : public Type, public Engine::IObserverTimer
{

public:
	Bomb(GameType* gameType,Bomberman* owned, int time, int speed, int power);
	~Bomb();
	EType getType();
	void updateTimer(unsigned int);
	Bomberman* getOwner();
	void explode();
	void destroy();
private:
	Bomberman* owner;

	GameType* gameType;
	int speed;
	int power;
	int time;

};



#endif // BOMB_H
