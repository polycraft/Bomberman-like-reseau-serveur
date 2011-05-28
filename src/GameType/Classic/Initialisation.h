#ifndef INITIALISATION_H
#define INITIALISATION_H

#include "../../Engine/util/IObserverTimer.h"
#include "../../Engine/util/Timer.h"
#include "PhaseClassic.h"
#include "Classic.h"

namespace GameTypeSpace
{
	namespace ClassicSpace
	{
		class Initialisation : public PhaseClassic, IObserverTimer
		{

		public:
			Initialisation(GameTypeSpace::Classic *gameType,CollisionDetector *collision);
			virtual ~Initialisation();
			void init();
			void run();
			void updateTimer(unsigned int delay);
            virtual void updateRecv(Socket *,Paquet &paquet);
		};
	}
}



#endif // INITIALISATION_H
