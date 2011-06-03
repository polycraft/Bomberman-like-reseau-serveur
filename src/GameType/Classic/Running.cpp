#include "Running.h"

#include "Classic.h"
#include "../../CollisionDetector.h"
#include "../../Engine/util/Timer.h"
#include "../../Type/Paquet.h"

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

		void Running::updateRecvBomberman(Bomberman* bomberman,Socket *socket,Paquet &paquet)
		{
            char type=(paquet.getData())[0];
                switch(type)
                {
                    case 'b'://Bombe
                    {
                        PaquetBomb *paquetBomb=paquet.getData<PaquetBomb*>();

                        //Paquet provient bien du bon joueur
                        if(paquetBomb->idBomber==bomberman->getProperty<int>(PB_id))
                        {
                            gameType->updateAllNetwork(paquet);
                        }
                    }
                    break;
                    case 'm'://Move
                    {
                        PaquetMove *paquetMove=paquet.getData<PaquetMove*>();

                        //Paquet provient bien du bon joueur
                        if(paquetMove->idBomber==bomberman->getProperty<int>(PB_id))
                        {
                            gameType->updateNetwork(bomberman,paquet);
                        }
                    }
                    break;
                }
		}
	}
}

