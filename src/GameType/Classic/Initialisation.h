#ifndef INITIALISATION_H
#define INITIALISATION_H

#include "../../Engine/util/IObserverTimer.h"
#include "../../Engine/NetworkEngine/IObserverSocketRecv.h"
#include "PhaseClassic.h"

namespace GameTypeSpace
{
    class Classic;
}
class CollisionDetector;

namespace GameTypeSpace
{
	namespace ClassicSpace
	{
		class Initialisation : public PhaseClassic, Engine::IObserverTimer
		{

		public:
			Initialisation(GameTypeSpace::Classic *gameType,CollisionDetector *collision);
			virtual ~Initialisation();
			void init();
			void run();
			void updateTimer(unsigned int delay);
            virtual void updateRecvBomberman(Bomberman* bomberman,Engine::Socket *socket,Engine::Paquet &paquet);
		};
	}
}



#endif // INITIALISATION_H
