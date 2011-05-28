#ifndef CLASSIC_H
#define CLASSIC_H


#include "../GameType.h"
#include "../../CollisionDetector.h"
#include "../Phase.h"
#include "../../Engine/NetworkEngine/IObserverSocketRecv.h"
#include "../../Type/ManagerExplosion.h"
#include "../../Type/ExplosionFlare.h"

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
	        P_Dead=4,
	        P_HurryUp=5
	    };
	}

	class Classic : public GameType, public Engine::IObserverSocketRecv
	{

	public:
		Classic(Server *server);
		virtual ~Classic();
		void update();


		Bomberman* getPlayer();
		void setPlayer(Bomberman*);
		

        Phase* getPhase(ClassicSpace::EPhase phase);

        virtual void explode(Bomb* bomb,int speed,int power);
		void updateExplosion(ExplosionFlare *flare,int power,int x,int y);
        void destroyManagerExplosion(ManagerExplosion* manager);

        void updateRecv(Socket *,Paquet &paquet);
	private:
		int partTime;
		CollisionDetector *collision;
		ClassicSpace::EPhase phaseCurrent;
		Bomberman *player;
		Phase *phase[4];
	};
}



#endif // CLASSIC_H
