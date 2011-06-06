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
			this->hurryTime = 60000;
			this->timeBetweenBloc = 100;
			this->blocx = 0;
			this->blocy = 0;
			this->direction = D_Haut;
		}

		HurryUp::~HurryUp()
		{
		}

		void HurryUp::init()
		{

			Timer::getTimer()->addListener(this,this->timeBetweenBloc);
			Timer::getTimer()->addListener(this,this->hurryTime);
			cout << "HurryUp Running" << endl;
			this->nextEtat();
		}

		void HurryUp::run()
		{
		}

		void HurryUp::updateTimer(unsigned int delay)
		{
			/*if(delay == this->actuTime)
			{

			}
			else if(delay == this->hurryTime)
			{
				cout << "HurryUp end" << endl;
				Timer::getTimer()->removeListener(this,this->hurryTime);
				end(P_Next);
			}
			else if(delay == this->timeBetweenBloc)
			{
				double x1,y1,z1;
				x1=15;
				y1=15;
				z1=5;
				switch(this->direction)
				{
					case D_Haut:
						if()
						{
							this->blocx++;
						}
					break;
					case D_Bas:

					break;
					case D_Droite:

					break;
					case D_Gauche:

					break;


				}
			}*/

		}
	}
}
