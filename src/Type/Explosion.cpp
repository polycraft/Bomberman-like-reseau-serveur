#include "Explosion.h"
#include "ExplosionFlare.h"

Explosion::Explosion(EExplose type,int x,int y, ExplosionFlare *explosionOwner):x(x),y(y)
{
	this->explosionOwner = explosionOwner;
	this->typeExplosion = type;
}

Explosion::~Explosion()
{
}


EType Explosion::getType()
{
	return T_Explosion;
}


ExplosionFlare* Explosion::getExplosionFlare()
{
	return this->explosionOwner;
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
