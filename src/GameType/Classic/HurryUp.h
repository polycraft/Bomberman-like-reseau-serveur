#ifndef HURRYUP_H
#define HURRYUP_H

#include "Running.h"
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
		class HurryUp : public Running
		{

		public:
			HurryUp(GameTypeSpace::Classic *gameType,CollisionDetector *collision);
			virtual ~HurryUp();
			void init();
			void run();
			virtual void updateTimer(unsigned int delay);
		private:
			int hurryTime;
		};
	}
}



#endif // HURRYUP_H
