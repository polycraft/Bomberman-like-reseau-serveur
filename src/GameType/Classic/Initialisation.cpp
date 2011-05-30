#include "Initialisation.h"

#include "../../Map.h"

namespace GameTypeSpace
{
	namespace ClassicSpace
	{
		Initialisation::Initialisation(GameTypeSpace::Classic *gameType,CollisionDetector *collision)  : PhaseClassic(gameType,collision)
		{
		}

		Initialisation::~Initialisation()
		{
		}

		void Initialisation::init()
		{
			/*if(this->gameType->getPlayerNetwork().size() >= 2)
			{*/
				Timer::getTimer()->addListener(this,this->gameType->getWaitingTime());
				cout << "Waiting " << this->gameType->getWaitingTime()/1000 << " secondes to Begin the Party !" << endl;
				this->nextEtat();
			//}			
		}

		void Initialisation::run()
		{
			
		    Map *map=gameType->getServer()->getMap();
			
		    //Création du bomberman
		    /*Bomberman *bomber=new Bomberman(0);
		    bomber->setProperty<int>(PB_bombPower,2);
		    bomber->setProperty<double>(PB_vitesse,0.05);
		    bomber->setProperty<int>(PB_nbBomb,2);
		    bomber->setProperty<int>(PB_nbBombMax,2);
		    bomber->setProperty<int>(PB_timerBomb,2000);
		    bomber->setProperty<int>(PB_timerPutBomb,200);
		    bomber->setProperty<int>(PB_vitesseExplode,2);
		    bomber->setProperty<int>(PB_life,2);
		    bomber->setProperty<bool>(PB_canPutBomb,true);
		    bomber->setProperty<int>(PB_timeInvinsible,2000);
		    bomber->setProperty<bool>(PB_invinsible,false);
		    bomber->setInvinsible(5000);

		    this->gameType->setPlayer(bomber);
		    map->addBomberman(bomber,map->getSpawn(0));

            bomber=new Bomberman(1);
		    this->gameType->getPlayerNetwork().push_back(bomber);
		    map->addBomberman(bomber,map->getSpawn(1));*/

		    
		}

		void Initialisation::updateRecv(Socket *socket,Paquet &paquet)
		{

		}

		void Initialisation::updateTimer(unsigned int delay)
		{
			Timer::getTimer()->removeListener(this,this->gameType->getWaitingTime());

			end(P_Next);
			
		}
	}
}
