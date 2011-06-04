#ifndef EXPLOSIONFLARE_H
#define EXPLOSIONFLARE_H

#include "../Engine/util/IObserverTimer.h"
#include <vector>
#include "Explosion.h"


class GameType;
class ManagerExplosion;
class Explosion;
class Bomberman;

class ExplosionFlare : public Engine::IObserverTimer
{
	public:
		ExplosionFlare(int x, int y, Bomberman* owner, int speed, int power, EExplose typeExplose, GameType *gametype, ManagerExplosion *manager);
		~ExplosionFlare();
		void nextExplose();
		void endExplose();
		EExplose getType();
		void updateTimer(unsigned int delay);
		Bomberman* getOwner();

	private:
		int x;
		int y;
		std::vector<Explosion*> listeExplosions;
		Bomberman* owner;
		int speed;
		int power;
		int powercurrent;
		EExplose typeExplosion;
		bool isEnd;
		GameType *gameType;
		ManagerExplosion *manager;

};



#endif // EXPLOSIONFLARE_H
