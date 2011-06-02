#include "CompareBomberman.h"

#include "Bomberman.h"

bool CompareBomberman::operator()(const Bomberman* a,const Bomberman *b)
{
    return a->getProperty<int>(PB_id)<b->getProperty<int>(PB_id);
}
