#ifndef DEAD_H
#define DEAD_H

#include "PhaseClassic.h"
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
		class Dead : public PhaseClassic
		{

		public:
			Dead(GameTypeSpace::Classic *gameType,CollisionDetector *collision);
			virtual ~Dead();
			void init();
			void run();
            virtual void updateRecvBomberman(Bomberman* bomberman,Engine::Socket *socket,Engine::Paquet &paquet);
		};
	}
}


#endif // DEAD_H
