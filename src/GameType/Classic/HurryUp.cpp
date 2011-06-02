#include "HurryUp.h"

#include "Classic.h"
#include "../../CollisionDetector.h"
#include "../../Engine/util/Timer.h"

using namespace Engine;

namespace GameTypeSpace
{
	namespace ClassicSpace
	{
		HurryUp::HurryUp(GameTypeSpace::Classic *gameType,CollisionDetector *collision)  : Running(gameType,collision)
		{
			this->hurryTime = 4000;
		}

		HurryUp::~HurryUp()
		{
		}

		void HurryUp::init()
		{
			Timer::getTimer()->addListener(this,this->hurryTime);
			cout << "HurryUp Running" << endl;
			this->nextEtat();
		}

		void HurryUp::run()
		{
		}

		void HurryUp::updateTimer(unsigned int delay)
		{
			cout << "HurryUp end" << endl;
			Timer::getTimer()->removeListener(this,this->hurryTime);
			end(P_Next);
		}
	}
}
