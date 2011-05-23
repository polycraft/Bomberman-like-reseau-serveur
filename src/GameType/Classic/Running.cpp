#include "Running.h"

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
		    this->nextEtat();
		}

		void Running::run()
		{

		}

		void Running::updateTimer(unsigned int delay)
		{

		}

		void Running::updateRecv(Socket *socket,const char*s,int size)
		{

		}
	}
}

