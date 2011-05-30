#include "Ending.h"

namespace GameTypeSpace
{
    using namespace ClassicSpace;
	Ending::Ending(GameTypeSpace::Classic *gameType,CollisionDetector *collision)  : Running(gameType,collision)
	{
		this->waitTime = 4000;
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
			end(P_Next);
	}
}