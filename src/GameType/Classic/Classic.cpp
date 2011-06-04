#include "Classic.h"

#include "../../CollisionDetector.h"
#include "../../Type/ManagerExplosion.h"
#include "../../Type/ExplosionFlare.h"
#include "../../Type/Bomberman.h"
#include "../../Type/Bomb.h"
#include "../../Type/Paquet.h"
#include "../../Server.h"
#include "../../Map.h"
#include "../../Engine/util/Timer.h"


#include "Initialisation.h"
#include "Running.h"
#include "HurryUp.h"
#include "Dead.h"
#include "Ending.h"

namespace GameTypeSpace
{
    using namespace ClassicSpace;
    using namespace Engine;
	Classic::Classic(Server *server,Socket *socket):GameType(server,10, socket)
	{
		this->partTime = 60000;
		this->waitTime = 4000;
	    phaseCurrent=P_Initialisation;

	    collision=new CollisionDetector(server->getMap());

	    phase[P_Initialisation-2]=new Initialisation(this,collision);
	    phase[P_Running-2]=new Running(this,collision);
	    phase[P_Dead-2]=new Dead(this,collision);
	    phase[P_HurryUp-2]=new HurryUp(this,collision);
		phase[P_Ending-2]=new Ending(this,collision);
		cout << "GameType Launched"<<endl;
		cout << "--------------Initialisation Step--------------" << endl;
		cout << "Waiting for players" << endl;
	}

	Classic::~Classic()
	{
	    delete collision;
	    delete phase[P_Initialisation-2];
	    delete phase[P_Running-2];
	    delete phase[P_HurryUp-2];
	}


	void Classic::update()
	{

	    Phase* t=getPhase(phaseCurrent);
        EPhase nextPhase=static_cast<EPhase>(getPhase(phaseCurrent)->update());
        int tmp;
        switch(nextPhase)
        {
            case P_Current:

            break;
            case P_Next:
				{

					if(phaseCurrent == P_Ending)
					{
						phaseCurrent = P_Initialisation;
						cout<<"Next Round => Packet send" << endl;
						cout << "--------------Initialisation Step--------------" << endl;
						cout << "Waiting for players" << endl;
						//Reinitialisation des Phases
						phase[P_Initialisation-2]->setEtat(E_Init);
						phase[P_Initialisation-2]->end(P_Initialisation);
						phase[P_Running-2]->setEtat(E_Init);
						phase[P_Running-2]->end(P_Running);
						phase[P_HurryUp-2]->setEtat(E_Init);
						phase[P_HurryUp-2]->end(P_HurryUp);
						phase[P_Ending-2]->setEtat(E_Init);
						phase[P_Ending-2]->end(P_Ending);
						//

						/*for(set<Bomberman*, CompareBomberman>::iterator it = this->playerNetwork.begin(); it !=this->playerNetwork.end(); it++)
						{
							(*it)->sendData<PaquetPhase>(&paquet);
						}*/
						break;
					}
					else
					{
						tmp=phaseCurrent+1;
						phaseCurrent=static_cast<EPhase>(tmp);
						cout << "Phase Changed => Packet send" << endl;

						/*for(set<Bomberman*, CompareBomberman>::iterator it = this->playerNetwork.begin(); it !=this->playerNetwork.end(); it++)
						{
							(*it)->sendData<PaquetPhase>(&paquet);
						}*/
					}
                    PaquetPhase paquet = {'p', Timer::getTimer()->getTime() , phaseCurrent};
                    this->updateAllNetwork<PaquetPhase>(paquet);


				}
            break;
            default:
                phaseCurrent=nextPhase;
            break;
        }
	}

	void Classic::explode(Bomb* bomb,int speed,int power)
	{
	    int tmpX=bomb->getTransX();tmpX=tmpX/10-1;
	    int tmpY=bomb->getTransY();tmpY=tmpY/10-1;

	    this->server->getMap()->set(NULL,tmpX,tmpY);
	    delete bomb;

	    new ManagerExplosion(tmpX,tmpY,bomb->getOwner(), speed, power, this);
	}

	void Classic::updateExplosion(ExplosionFlare *flare,int power,int x,int y)
	{
	    if(flare->getType()==T_Emitter)
	    {
	        flare->endExplose();
	    }
	    else
	    {
            switch(flare->getType())
            {
                case T_Left:
                    x-=power;
                    break;
                case T_Right:
                    x+=power;
                    break;
                case T_Up:
                    y+=power;
                break;
                case T_Down:
                    y-=power;
                break;
            }
            Type *object;
            switch(this->collision->detect(T_Explosion,x,y))
            {
                case C_Explose:
                    object=this->server->getMap()->get(x,y);
                    if(object->getType()==T_Bomb)
                    {
                        dynamic_cast<Bomb*>(this->server->getMap()->get(x,y))->explode();
                    }
                    else if(object->getType()==T_BreakableBloc)
                    {
                        this->server->getMap()->set(NULL,x,y);
                        object->destroy();
                        //créer bonus
                    }
                    flare->endExplose();
                break;
                case C_Kill:
                    //destruction du bonus
                break;
                case C_Block:
                    flare->endExplose();
                break;
                case C_Nothing:
                    flare->nextExplose();
                break;
            }
	    }
	}

	void Classic::destroyManagerExplosion(ManagerExplosion* manager)
	{
	    manager->getOwner()->setProperty<int>(PB_nbBomb,manager->getOwner()->getProperty<int>(PB_nbBomb)+1);

	     delete manager;
	}

    Phase* Classic::getPhase(EPhase phase)
    {
        switch(phase)
        {
            case P_Current:
                return this->phase[phaseCurrent-2];
            break;
            case P_Next:
                return this->phase[phaseCurrent+1-2];
            break;
            default:
                return this->phase[phase-2];
            break;
        }
    }

    void Classic::updateRecvBomberman(Bomberman* bomberman,Socket *socket,Paquet &paquet)
    {
        dynamic_cast<PhaseClassic*>(this->phase[phaseCurrent-2])->updateRecvBomberman(bomberman,socket,paquet);
        char type=(paquet.getData())[0];
        switch(type)
        {
            case 'a'://Demande d'information
            {
                PaquetAsk *paquetAsk=paquet.getData<PaquetAsk*>();
                switch(paquetAsk->paquet)
                {
                    case 'i'://id
                    {
                        PaquetId paquetId={'i', Engine::Timer::getTimer()->getTime(),bomberman->getProperty<int>(PB_id)};
                        bomberman->sendData<PaquetId>(&paquetId);
                        bomberman->setConnected(true);
                    }
                    break;
                    case 'p':
                    {
                         PaquetPhase paquetPhase={'p', Engine::Timer::getTimer()->getTime(),phaseCurrent};
                        bomberman->sendData<PaquetPhase>(&paquetPhase);
                    }
                    break;
                }
				
            }
            break;

			case 'm'://Mouvement a accepter
			{
				double tmpX = bomberman->getTransX();
				double tmpY = bomberman->getTransY();
				int x=tmpX;x=x/10-1;
				int y=tmpY;y=y/10-1;

				PaquetMove *paquetMove=paquet.getData<PaquetMove*>();
				//verif du deplacement
				double vitesse=bomberman->getProperty<double>(PB_vitesse)*Timer::getTimer()->getTimePerFrame();
				if(vitesse>8)
				{
					vitesse=8;
				}
				double distance=3.75;

				double xMin=(tmpX-vitesse-distance);
				double yMin=(tmpY-vitesse-distance);
				double xMax=(tmpX-vitesse+distance);
				double yMax=(tmpY-vitesse+distance);

				double rotate=0;

				if(paquetMove->rotation == 180)//vers la gauche
				{
					int point[4]={xMin-vitesse,xMax,yMin,yMax};
					point[0]=point[0]/10-1;
					point[2]=point[2]/10-1;
					point[3]=point[3]/10-1;

					int position=tmpX;
					position=position/10-1;

					if((position==point[0]) || (collision->detect(T_Bomberman,point[0],point[2])!=C_Block && collision->detect(T_Bomberman,point[0],point[3])!=C_Block))
					{
						this->getPlayer()->translation(-vitesse,0,0);
						this->getPlayer()->setRotation(0,0,paquetMove->rotation);
					}
					else//envoi du paquet d'erreur
					{
						PaquetError error= {'r', Engine::Timer::getTimer()->getTime(), 'm'};
					}
				}

				if(paquetMove->rotation == 0)//vers la droite
				{
					int point[4]={xMin,xMax+vitesse,yMin,yMax};
					point[1]=point[1]/10-1;
					point[2]=point[2]/10-1;
					point[3]=point[3]/10-1;

					int position=tmpX;
					position=position/10-1;

					if((position==point[1]) || (collision->detect(T_Bomberman,point[1],point[2])!=C_Block && collision->detect(T_Bomberman,point[1],point[3])!=C_Block))
					{
						this->getPlayer()->translation(vitesse,0,0);
						this->getPlayer()->setRotation(0,0,paquetMove->rotation);
					}
					else//envoi du paquet d'erreur
					{
						PaquetError error= {'r', Engine::Timer::getTimer()->getTime(), 'm'};
					}

				}

				if(paquetMove->rotation == 90)//vers le haut
				{
					int point[4]={xMin,xMax,yMin,yMax+vitesse};
					point[0]=point[0]/10-1;
					point[1]=point[1]/10-1;
					point[3]=point[3]/10-1;

					int position=tmpY;
					position=position/10-1;

					if((position==point[3]) || (collision->detect(T_Bomberman,point[0],point[3])!=C_Block && collision->detect(T_Bomberman,point[1],point[3])!=C_Block))
					{
						this->getPlayer()->translation(0,vitesse,0);
						this->getPlayer()->setRotation(0,0,paquetMove->rotation);
					}
					else//envoi du paquet d'erreur
					{
						PaquetError error= {'r', Engine::Timer::getTimer()->getTime(), 'm'};
					}
				}

				if(paquetMove->rotation == -90)//vers le bas
				{
					int point[4]={xMin,xMax,yMin-vitesse,yMax};
					point[0]=point[0]/10-1;
					point[1]=point[1]/10-1;
					point[2]=point[2]/10-1;

					int position=tmpY;
					position=position/10-1;

					if((position==point[2]) || (collision->detect(T_Bomberman,point[0],point[2])!=C_Block && collision->detect(T_Bomberman,point[1],point[2])!=C_Block))
					{
						this->getPlayer()->translation(0,-vitesse,0);
						this->getPlayer()->setRotation(0,0,paquetMove->rotation);
					}
					else//envoi du paquet d'erreur
					{
						PaquetError error= {'r', Engine::Timer::getTimer()->getTime(), 'm'};
					}
				}
			}
			break;
        }
    }

	int Classic::getWaitingTime()
	{
		return this->waitTime;
	}

	int Classic::getPartTime()
	{
		return this->partTime;
	}
}
