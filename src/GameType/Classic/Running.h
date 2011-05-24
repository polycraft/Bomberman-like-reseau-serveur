#ifndef RUNNING_H
#define RUNNING_H

#include "PhaseClassic.h"

namespace GameTypeSpace
{
	namespace ClassicSpace
	{
		class Running : public PhaseClassic
		{

		public:
			Running(GameTypeSpace::Classic *gameType,CollisionDetector *collision);
			virtual ~Running();
			void init();
			virtual void run();
			virtual void updateTimer(unsigned int delay);
			virtual void updateRecv(Socket *,Paquet &paquet);
		};
	}
}



#endif // RUNNING_H
