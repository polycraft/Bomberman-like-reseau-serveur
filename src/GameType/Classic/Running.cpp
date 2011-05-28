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
			cout << "GameType is Running" << endl;
		    this->nextEtat();
		}

		void Running::run()
		{
			
		}

		void Running::updateTimer(unsigned int delay)
		{

		}

		void Running::updateRecv(Socket *socket,Paquet &paquet)
		{

		}
	}
}

