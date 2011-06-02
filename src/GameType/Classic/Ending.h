#ifndef ENDING_H
#define ENDING_H

#include "PhaseClassic.h"
#include "../../Engine/util/IObserverTimer.h"
#include "../../Engine/NetworkEngine/IObserverSocketRecv.h"

namespace GameTypeSpace
{
    class Classic;
}
class CollisionDetector;

namespace GameTypeSpace
{
	namespace ClassicSpace
	{
		class Ending : public PhaseClassic, public Engine::IObserverTimer
		{

		public:
			Ending(GameTypeSpace::Classic *gameType,CollisionDetector *collision);
			virtual ~Ending();
			void init();
			void run();
			void updateTimer(unsigned int delay);
			void updateRecv(Engine::Socket *socket,Engine::Paquet &paquet);
		private:
			int waitTime;
		};
	}
}



#endif // ENDING_H
