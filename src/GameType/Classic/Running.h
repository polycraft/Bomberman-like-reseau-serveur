#ifndef RUNNING_H
#define RUNNING_H

#include "PhaseClassic.h"
#include "../../Engine/util/IObserverTimer.h"

namespace GameTypeSpace
{
    class Classic;
}
class CollisionDetector;

namespace GameTypeSpace
{
	namespace ClassicSpace
	{
		class Running : public PhaseClassic, public Engine::IObserverTimer
		{

		public:
			Running(GameTypeSpace::Classic *gameType,CollisionDetector *collision);
			virtual ~Running();
			virtual void init();
			virtual void run();
			virtual void updateTimer(unsigned int delay);
			virtual void updateRecvBomberman(Bomberman* bomberman,Engine::Socket *socket,Engine::Paquet &paquet);
		};
	}
}



#endif // RUNNING_H
