#ifndef HURRYUP_H
#define HURRYUP_H

#include "Running.h"
#include "../../Engine/util/IObserverTimer.h"
class StaticBloc;

namespace GameTypeSpace
{
    class Classic;
}
class CollisionDetector;

namespace GameTypeSpace
{
	namespace ClassicSpace
	{
			enum EDirection
			{
				D_Haut,
				D_Bas,
				D_Gauche,
				D_Droite
			};

		class HurryUp : public Running
		{

		public:
			HurryUp(GameTypeSpace::Classic *gameType,CollisionDetector *collision);
			virtual ~HurryUp();
			void init();
			void run();
			virtual void updateTimer(unsigned int delay);
		private:
			int timeHurry;
			int actuTime;
			int blocx;
			int blocy;
			double blocz;
			int nbIteration;
			int countIteration;
			int nbFailure;//detection de la fin du hurryUp/recouvrement total
			EDirection direction;
		};
	}
}



#endif // HURRYUP_H
