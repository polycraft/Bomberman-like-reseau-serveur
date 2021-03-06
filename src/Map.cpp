#include "Map.h"

#include "Type/Bomberman.h"
#include "Type/Type.h"
#include "Type/BreakableBloc.h"
#include "Type/StaticBloc.h"

using namespace Engine;

Map::Map(string &name, EGameType gameType, int width, int height)  : Ressource(name)
{
	this->gameType = gameType;
	this->width = width;
	this->height = height;
	this->spawnCount = 0;
	Type ***temp = new Type**[this->width];
	for(int x=0; x<this->width;x++)
	{
		temp[x]= new Type*[this->height];
		for(int y=0;y<height;y++)
		{
			temp[x][y] = NULL;
		}
	}

	this->map = temp;
}

Map::~Map()
{
}

void Map::addBomberman(Bomberman *bomberman,SCoordinate coord)
{
	double x1,y1,z1;
	x1=15;
	y1=15;
	z1=0;

	bomberman->setCoordonnes(coord.x*10+x1,coord.y*10+y1,z1);
}

void Map::addObject(Type* object, int x, int y,EScene scene)
{
	double x1,y1,z1;
	x1=15;
	y1=15;
	z1=5;

	this->map[x][y] = object;
	object->setCoordonnes(x*10+x1,y*10+y1,z1);
}

void Map::addSpawn(int x, int y)
{
	SCoordinate temp;
	temp.x=x;
	temp.y=y;
	this->spawn.push_back(temp);
}

SCoordinate Map::getSpawn(int id)
{
	return this->spawn[id];
}

int Map::getWidth()
{
	return this->width;
}

int Map::getHeight()
{
	return this->height;
}

Type* Map::get(int x,int y)
{
	return map[x][y];
}

void Map::set(Type* object,int x,int y)
{
    map[x][y]=object;
}

void Map::setEngine(MainEngine *engine)
{
	this->engine = engine;
}

void Map::setDataMap(char* dataMap)
{
	this->mapData = dataMap;
}

void Map::buildMap()
{
	for( int i=0; i< width*height;i++)
    {

		switch(this->mapData[i])
        {

            case 'a':
                this->addObject(new StaticBloc(), i%(width), height - i/(width)-1, T_Map );
                break;
            case 'b':
                this->addObject(new BreakableBloc(), i%(width), height - i/(width)-1, T_Dyn);
            break;
            case 'c':
				this->spawnCount++;
                this->addSpawn(i%(width), height - i/(width)-1);
            break;
        }
	}
}

int Map::getCountSpawn()
{
	return this->spawnCount;
}
