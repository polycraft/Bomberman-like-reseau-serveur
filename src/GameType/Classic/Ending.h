#ifndef ENDING_H
#define ENDING_H

#include "Running.h"

namespace GameTypeSpace
{
	namespace ClassicSpace
	{
		class Ending : public Running, IObserverTimer
		{

		public:
			Ending(GameTypeSpace::Classic *gameType,CollisionDetector *collision);
			virtual ~Ending();
			void init();
			void run();
			void updateTimer(unsigned int delay);
		private:
			int waitTime;
		};
	}
}



#endif // ENDING_H