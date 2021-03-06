#ifndef CLASSIC_H
#define CLASSIC_H



#include "../GameType.h"
#include "../../Engine/NetworkEngine/IObserverSocketRecv.h"
#include "../../Engine/NetworkEngine/Socket.h"
#include "../../Type/Bonus.h"

class Server;
class Bomberman;
class Bomb;
class ExplosionFlare;
class ManagerExplosion;
class CollisionDetector;
class Phase;

namespace GameTypeSpace
{
	namespace ClassicSpace
	{

	    typedef enum EPhase
	    {
	        P_Current=0,
	        P_Next=1,
	        P_Initialisation=2,
	        P_Running=3,
	        P_HurryUp=4,
			P_Ending=5,
			P_Dead=6
	    };
	}

	class Classic : public GameType
	{

	public:
		Classic(Server *server,Engine::Socket *socket);
		virtual ~Classic();
		void update();


		Phase* getPhase(ClassicSpace::EPhase phase);

        virtual void explode(Bomb* bomb,int speed,int power);
		void updateExplosion(ExplosionFlare *flare,int power,int x,int y);
        void destroyManagerExplosion(ManagerExplosion* manager);

        virtual void updateRecvBomberman(Bomberman* bomberman,Engine::Socket *sock,Engine::Paquet& paquet);

		ClassicSpace::EPhase getPhaseCurrent();
		int getPartTime();
		int getWaitingTime();

	private:
        EBonus randomBonus();
		int waitTime;
		int partTime;
		CollisionDetector *collision;
		ClassicSpace::EPhase phaseCurrent;
		Phase *phase[5];
	};
}



#endif // CLASSIC_H
