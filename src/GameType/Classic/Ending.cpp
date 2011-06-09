#include "Ending.h"

#include "Classic.h"
#include "../../CollisionDetector.h"
#include "../../Engine/util/Timer.h"
#include "../../Type/Paquet.h"

namespace GameTypeSpace
{
    using namespace ClassicSpace;
    using namespace Engine;
	Ending::Ending(GameTypeSpace::Classic *gameType,CollisionDetector *collision)  : PhaseClassic(gameType,collision)
	{
		this->waitTime = 8000;
	}

	Ending::~Ending()
	{

	}

	void Ending::init()
	{
		Timer::getTimer()->addListener(this,this->waitTime);
		cout << "End Of Round ... Wait" << endl;
		this->nextEtat();
	}

	void Ending::run()
	{

	}

	void Ending::updateTimer(unsigned int delay)
	{
			cout << "End of Ending.. Prepare to next Round" << endl;
			Timer::getTimer()->removeListener(this,this->waitTime);
			PaquetRound paquetRound = {'o', Timer::getTimer()->getTime()};
			gameType->updateAllNetwork<PaquetRound>(paquetRound);
			end(P_Next);
	}

	void Ending::updateRecvBomberman(Bomberman* bomberman,Socket *socket,Paquet &paquet)
    {

    }
}
