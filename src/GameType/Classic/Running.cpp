#include "Running.h"

#include "Classic.h"
#include "../../CollisionDetector.h"
#include "../../Engine/util/Timer.h"
#include "../../Type/Paquet.h"
#include "../../Type/Bomb.h"
#include "../../Type/Effects/Effect.h"
#include "../../Server.h"
#include "../../Map.h"


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
			int nbDead=0;
			for(std::set<Bomberman*,CompareBomberman>::iterator it=this->gameType->getPlayerNetwork().begin(); it!=this->gameType->getPlayerNetwork().end(); ++it)
			{
				double tmpx=(*it)->getTransX();
				double tmpy=(*it)->getTransY();
				int x=tmpx;x=x/10-1;
				int y=tmpy;y=y/10-1;
				//Verification de la mort de chaque joueur
				//cout << x << y << endl;
				//cout << static_cast<int>(this->gameType->getServer()->getMap()->get(x,y)->getType()) << endl;
				if(collision->detect(T_Bomberman,x,y)==C_Kill && (*it)->getProperty<bool>(PB_invincible)==false)
				{
					(*it)->setProperty<int>(PB_life, 0);
					int idBomber = (*it)->getProperty<int>(PB_id);
					PaquetEtat paquetEtat = {'e', Engine::Timer::getTimer()->getTime(), idBomber, PB_life,0};
					gameType->updateAllNetwork(paquetEtat);
				}
				//si est mort
				if((*it)->getProperty<int>(PB_life) <= 0)
				{
					nbDead++;
				}
				
			}

			if(nbDead >= this->gameType->getPlayerNetwork().size())
			{
				end(P_Ending);
			}
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
                            paquetBomb->explodeTime=bomberman->getProperty<int>(PB_timerBomb);
                            paquetBomb->vitesseExplode=bomberman->getProperty<int>(PB_speedExplode);
                            paquetBomb->power=bomberman->getProperty<int>(PB_bombPower);
                            cout << "bomb !"<< endl;
                            Bomb* bomb=new Bomb(
                                        this->gameType,
                                        bomberman,
                                        paquetBomb->explodeTime,
                                        paquetBomb->vitesseExplode,
                                        paquetBomb->power);

                            gameType->getServer()->getMap()->addObject(bomb,paquetBomb->x,paquetBomb->y,T_Dyn);

                            bomberman->setProperty<int>(PB_nbBomb,bomberman->getProperty<int>(PB_nbBomb)-1);

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
							bomberman->setTransX(paquetMove->x);
							bomberman->setTransY(paquetMove->y);
							bomberman->setRotation(0,0,paquetMove->rotation);
                            gameType->updateNetwork(bomberman,paquet);
                        }

                        int x=paquetMove->x;x=x/10-1;
                        int y=paquetMove->y;y=y/10-1;

                        if(collision->detect(T_Bomberman,x,y)==C_Bonus)
                        {
                            Bonus *bonus = dynamic_cast<Bonus*>(this->gameType->getServer()->getMap()->get(x,y));
                            //Active l'effet du bonus:
                            bonus->getEffect()->enableEffect(bomberman);
                            //Ajoute le bonus au bomberman
                            bomberman->addBonus(bonus);
                            //fait disparaitre le bonus
                            this->gameType->getServer()->getMap()->set(NULL,x,y);

                            PaquetEffect paquetEffect={'f', Engine::Timer::getTimer()->getTime(),bomberman->getProperty<int>(PB_id),x,y};
                            this->gameType->updateAllNetwork<PaquetEffect>(paquetEffect);
                        }
                    }
                    break;
                }
		}
	}
}

