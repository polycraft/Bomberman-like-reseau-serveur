#include "Explosion.h"

Explosion::Explosion(EExplose type,int x,int y):x(x),y(y)
{
	this->typeExplosion = type;
}

Explosion::~Explosion()
{

}


EType Explosion::getType()
{
	return T_Explosion;
}

void Explosion::changeExplose(EExplose typeExplose)
{
	this->typeExplosion = typeExplose;
}

int Explosion::getX()
{
    return x;
}

int Explosion::getY()
{
    return y;
}
