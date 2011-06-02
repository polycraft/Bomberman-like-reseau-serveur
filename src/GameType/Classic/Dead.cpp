#include "Dead.h"

#include "Classic.h"
#include "../../CollisionDetector.h"
#include "../../Type/Bomberman.h"

using namespace Engine;

namespace GameTypeSpace
{
	namespace ClassicSpace
	{
		Dead::Dead(GameTypeSpace::Classic *gameType,CollisionDetector *collision)  : PhaseClassic(gameType,collision)
		{
		}

		Dead::~Dead()
		{

		}

		void Dead::init()
		{
            this->gameType->getPlayer()->setVisible(false);
            this->nextEtat();
		}

		void Dead::run()
		{

		}

		void Dead::updateRecv(Socket *socket,Paquet &paquet)
		{

		}
	}
}
