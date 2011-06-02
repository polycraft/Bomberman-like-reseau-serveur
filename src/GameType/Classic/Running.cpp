#include "Running.h"

#include "Classic.h"
#include "../../CollisionDetector.h"
#include "../../Engine/util/Timer.h"

using namespace Engine;

namespace GameTypeSpace
{
	namespace ClassicSpace
	{
		Running::Running(GameTypeSpace::Classic *gameType,CollisionDetector *collision)  : PhaseClassic(gameType,collision)
		{
		}

		Running::~Running()
		{
		}

		void Running::init()
		{
			Timer::getTimer()->addListener(this,this->gameType->getPartTime());
			cout << "GameType is Running" << endl;
		    this->nextEtat();
		}


		void Running::run()
		{

		}

		void Running::updateTimer(unsigned int delay)
		{
			cout << "End Running" << endl;
			Timer::getTimer()->removeListener(this,this->gameType->getPartTime());
			end(P_Next);
		}

		void Running::updateRecv(Socket *socket,Paquet &paquet)
		{

		}
	}
}

