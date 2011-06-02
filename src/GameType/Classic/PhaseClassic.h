#ifndef PHASECLASSIC_H
#define PHASECLASSIC_H

#include "../Phase.h"
#include "../../Engine/NetworkEngine/IObserverSocketRecv.h"

namespace GameTypeSpace
{
    class Classic;
}
class CollisionDetector;
class Bomberman;

namespace GameTypeSpace
{
    namespace ClassicSpace
    {
        class PhaseClassic : public Phase
        {
        public:
            PhaseClassic(GameTypeSpace::Classic *gameType,CollisionDetector *collision);
            virtual ~PhaseClassic();
            virtual void init()=0;
			virtual void run()=0;
            virtual void updateRecvBomberman(Bomberman* bomberman,Engine::Socket *,Engine::Paquet &paquet)=0;
        protected:
            Classic *gameType;
        };
    }
}

#endif // PHASE_H
