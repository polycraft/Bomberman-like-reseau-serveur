#include "Classic.h"


#include "Initialisation.h"
#include "Running.h"
#include "HurryUp.h"
#include "Dead.h"

namespace GameTypeSpace
{
    using namespace ClassicSpace;
	Classic::Classic(Server *server,Socket *socket):GameType(server,10, socket)
	{
		this->partTime = 4000;
		this->waitTime = 4000;
		this->player = NULL;
	    phaseCurrent=P_Initialisation;

	    collision=new CollisionDetector(server->getMap());

	    phase[P_Initialisation-2]=new Initialisation(this,collision);
	    phase[P_Running-2]=new Running(this,collision);
	    phase[P_Dead-2]=new Dead(this,collision);
	    phase[P_HurryUp-2]=new HurryUp(this,collision);
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
					
					if(phaseCurrent == P_HurryUp)
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
						//

						PaquetPhase paquet = {'p', Timer::getTimer()->getTime() , phaseCurrent};
						for(set<Bomberman*, CompareBomberman>::iterator it = this->playerNetwork.begin(); it !=this->playerNetwork.end(); it++)
						{
							(*it)->sendData<PaquetPhase>(&paquet);
						}
						break;
					}
					else
					{
						tmp=phaseCurrent+1;
						phaseCurrent=static_cast<EPhase>(tmp);
						cout << "Phase Changed => Packet send" << endl;
						PaquetPhase paquet = {'p', Timer::getTimer()->getTime() , phaseCurrent};
						for(set<Bomberman*, CompareBomberman>::iterator it = this->playerNetwork.begin(); it !=this->playerNetwork.end(); it++)
						{
							(*it)->sendData<PaquetPhase>(&paquet);
						}
					}

					

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

	    new ManagerExplosion(tmpX,tmpY,bomb->getIdOwner(), speed, power, this);
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
	    delete manager;
	    player->setProperty<int>(PB_nbBomb,player->getProperty<int>(PB_nbBomb)+1);
	}

	Bomberman* Classic::getPlayer()
	{
		return player;
	}

	void Classic::setPlayer(Bomberman* bomber)
	{
	    player=bomber;
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

    void Classic::updateRecv(Socket *socket,Paquet &paquet)
    {
        dynamic_cast<PhaseClassic*>(this->phase[phaseCurrent-2])->updateRecv(socket,paquet);
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
