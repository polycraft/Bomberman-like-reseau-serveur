#include "HurryUp.h"

#include "Classic.h"
#include "../../CollisionDetector.h"
#include "../../Engine/util/Timer.h"
#include "../../Map.h"
#include "../../Server.h"
#include "../GameType.h"
#include "../../Type/Explosion.h"
#include "../../Type/ExplosionFlare.h"
#include "../../Type/StaticBloc.h"

using namespace Engine;

namespace GameTypeSpace
{
	namespace ClassicSpace
	{
		HurryUp::HurryUp(GameTypeSpace::Classic *gameType,CollisionDetector *collision)  : Running(gameType,collision)
		{
			this->actuTime = 20;
			this->blocx = 0;
			this->blocy = 0;
			this->blocz = 50;
			this->direction = D_Haut;
			this->nbIteration = 0;
			this->countIteration = 1;
			this->nbFailure=0;
			this->direction = D_Haut;
		}

		HurryUp::~HurryUp()
		{
		}

		void HurryUp::init()
		{

			Timer::getTimer()->addListener(this,this->actuTime);
			cout << "HurryUp Running" << endl;
			this->nextEtat();
		}

		void HurryUp::run()
		{
		}

		void HurryUp::updateTimer(unsigned int delay)
		{
			if(delay == this->actuTime)
			{
				if(blocz>=0)
					{
						this->blocz -= Engine::Timer::getTimer()->getTimePerFrame()/4;
					}
				else
				{
						this->blocz = 50;
						EType type;
						if(this->gameType->getServer()->getMap()->get(this->blocx,this->blocy) != NULL)
						{
							type = this->gameType->getServer()->getMap()->get(this->blocx,this->blocy)->getType();

							if( type == T_BreakableBloc || type == T_Bonus)
							{
								this->gameType->getServer()->getMap()->addObject(new StaticBloc(), this->blocx, this->blocy, T_Dyn);
							}
							else if( type == T_Bomb)
							{
								this->gameType->getServer()->getMap()->addObject(new StaticBloc(), this->blocx, this->blocy, T_Dyn);
							}
							else if(type == T_Explosion)
							{
								Explosion* explosion = dynamic_cast<Explosion*>(this->gameType->getServer()->getMap()->get(this->blocx,this->blocy));
								explosion->getExplosionFlare()->removeExplosion(explosion);
								this->gameType->getServer()->getMap()->addObject(new StaticBloc(), this->blocx, this->blocy, T_Dyn);
							}
						}
						else
						{
							this->gameType->getServer()->getMap()->addObject(new StaticBloc(), this->blocx, this->blocy, T_Dyn);
						}
						switch(this->direction)
						{
							case D_Haut:

								if(this->blocy >= this->gameType->getServer()->getMap()->getHeight()-1 - nbIteration)//verif changement de direction
								{
									this->direction = D_Droite;
									this->countIteration++;
									nbFailure++;
								}
								else
								{
									this->blocy++;//ajoute en hauteur
									nbFailure = 0;
								}
								if(countIteration >=2)
								{
									nbIteration++;//enleve un bloc au bout de 2 ligne/colonnes
									countIteration = 0;
								}
						

							break;

							case D_Bas:
								if(this->blocy <= -1 + nbIteration)//verif changement de direction
								{
							
									this->direction = D_Gauche;
									this->countIteration++;
									nbFailure++;
								}
								else
								{
									this->blocy--;//ajoute en hauteur
									nbFailure = 0;
								}
								if(countIteration >=2)
								{
									nbIteration++;//enleve un bloc au bout de 2 ligne/colonnes
									countIteration = 0;
								}

							break;

							case D_Droite:
								if(this->blocx > this->gameType->getServer()->getMap()->getWidth()-1 - nbIteration)//verif changemant de direction
								{
									this->direction = D_Bas;
									this->countIteration++;
									nbFailure++;
								}
								else
								{
									this->blocx++;//ajoute en hauteur
									nbFailure = 0;
								}
								if(countIteration >=2)
								{
									nbIteration++;//enleve un bloc au bout de 2 ligne/colonnes
									countIteration = 0;
								}

							break;
							case D_Gauche:
								if(this->blocx <= -1+ nbIteration)//verif changemant de direction
								{
									cout << nbFailure << endl;
									this->direction = D_Haut;
									this->nbIteration -=1;//important sinon difference de 1carré a chaque tours
									this->countIteration++;
									nbFailure++;
									if(nbFailure >=2)
									{
										//on stoppe le timer
										Engine::Timer::getTimer()->removeListener(this,this->actuTime);
									}

								}
								else
								{
									this->blocx--;//ajoute en hauteur
									nbFailure = 0;
								}
								if(countIteration >=2)
								{
									nbIteration++;//enleve un bloc au bout de 2 ligne/colonnes
									countIteration = 0;
								}
								break;
	
						}
				}
			}
		}
	}
}
