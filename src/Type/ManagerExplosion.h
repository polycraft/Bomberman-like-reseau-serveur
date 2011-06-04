#ifndef MANAGEREXPLOSION_H
#define MANAGEREXPLOSION_H

#include "../Engine/util/IObserverTimer.h"
#include <vector>

class GameType;
class ExplosionFlare;
class Bomberman;

class ManagerExplosion : public Engine::IObserverTimer
{
	public:
		ManagerExplosion(int x, int y, Bomberman* owner, int speed, int power, GameType *gametype);
		~ManagerExplosion();
		void addAnEnd();
		void updateTimer(unsigned int delay);
		Bomberman* getOwner();

	private:
		int x;
		int y;
		std::vector<ExplosionFlare*> listeExplosionFlare;
		Bomberman* owner;
		int speed;
		int power;
		int powercurrent;
		GameType *gameType;
		int nbEnd;
		int nbExploSide;
};


#endif //MANAGEREXPLOSION_H
