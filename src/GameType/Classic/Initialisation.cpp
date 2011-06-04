#include "Initialisation.h"

#include "../../Map.h"
#include "../../Server.h"
#include "Classic.h"
#include "../../CollisionDetector.h"
#include "../../Engine/util/Timer.h"
#include "../../Type/Paquet.h"

using namespace Engine;

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
		    gameType->getServer()->getMap()->buildMap();
            randomSpawn=rand()%(gameType->getServer()->getMap()->getCountSpawn()) +1;
            nbReady=0;
            prevSpawn=rand()%(gameType->getServer()->getMap()->getCountSpawn());
            waiting=false;

            this->nextEtat();
			/*if(this->gameType->getPlayerNetwork().size() >= 2)
			{*/

				/*Timer::getTimer()->addListener(this,this->gameType->getWaitingTime());

				this->nextEtat();*/

			//}
		}

		void Initialisation::run()
		{
            if(nbReady>=1 && !waiting)
            {
                waiting=true;
                Timer::getTimer()->addListenerOnce(this,this->gameType->getWaitingTime());
                cout << "Waiting " << this->gameType->getWaitingTime()/1000 << " secondes to Begin the Party !" << endl;
            }
		}

		void Initialisation::updateRecvBomberman(Bomberman* bomberman,Socket *socket,Paquet &paquet)
		{
            char type=(paquet.getData())[0];
            switch(type)
            {
                case 'a'://Demande d'information
                {
                    PaquetAsk *paquetAsk=paquet.getData<PaquetAsk*>();
                    switch(paquetAsk->paquet)
                    {
                        case 's'://spawn
                        {
                            nbReady++;
                            //Calcule du nouveau spawn
                            int t= gameType->getServer()->getMap()->getCountSpawn();
                            prevSpawn=(prevSpawn+randomSpawn)%gameType->getServer()->getMap()->getCountSpawn()+1;

                            PaquetSpawn paquetSpawn={'s', Engine::Timer::getTimer()->getTime(),bomberman->getProperty<int>(PB_id),prevSpawn-1,""};

                            bomberman->getName().copy(paquetSpawn.name,bomberman->getName().size());

                            gameType->updateAllNetwork<PaquetSpawn>(paquetSpawn);

                            vector<PaquetSpawn>::iterator it;

                            for ( it=listSpawn.begin() ; it < listSpawn.end(); it++ )
                            {
                                bomberman->sendData<PaquetSpawn>(&(*it));
                            }

                            listSpawn.push_back(paquetSpawn);
                        }
                        break;
                    }
                }
                break;
            }
		}

		void Initialisation::updateTimer(unsigned int delay)
		{
			end(P_Next);
		}
	}
}
