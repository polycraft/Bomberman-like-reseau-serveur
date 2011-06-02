#ifndef MAP_H
#define MAP_H

#include <vector>
#include <string>
#include "Engine/Ressource.h"
#include "Engine/MainEngine.h"
#include "Engine/GraphicEngine/Scene.h"




class Type;
class Bomberman;


enum EScene{
	T_World=0,
	T_Map=1,
	T_Dyn=2
};

enum EGameType{
	T_Classic,
	T_CaptureTheFlag
};

typedef struct SCoordinate
{
	int x;
	int y;
} SCoordinate;

class Map : public Engine::Ressource
{

public:
	Map(std::string &name, EGameType gameType, int width, int lenght);
	~Map();
	void addBomberman(Bomberman *bomberman,SCoordinate coord);
	void addObject(Type* object, int x, int y, EScene scene);
	void addSpawn(int x, int y);
	SCoordinate getSpawn(int id);
	int getWidth();
	int getHeight();
	Type* get(int x,int y);
	void set(Type* object,int x,int y);
	void setEngine(Engine::MainEngine* engine);
	void setDataMap(char* dataMap);
	void buildMap();

private:
	int gameType;
	int width;
	int height;
	std::vector<Engine::Scene*> scene;
	std::vector<SCoordinate> spawn;
	Type ***map;

	char *mapData;

	Engine::MainEngine* engine;

};



#endif // MAP_H
