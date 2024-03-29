#pragma once

#define MAX_LIFE_POINTS 10
#define INITIAL_MONEY_AMOUNT 200
#define TILE_SIZE 32
#define FLOW_DISTANCE_MAX 255

#define SPAWN_TIMER_MS 200 

enum itemEnum
{
	WallItem,
	TurretItem,
	None
};



enum class TileType : char
{
	EMPTY,			//0
	WALL,			//1
	TURRET,			//2
	ENEMYSPAWNER,	//3
	TARGET,			//4
	FOREST,			//5
};

struct Tile {
	Tile()
		:type(TileType::EMPTY) {}
	Tile(TileType tileType)
		:type(tileType) {}

	TileType type;
	int flowDirectionX = 0;
	int flowDirectionY = 0;
	unsigned char flowDistance = FLOW_DISTANCE_MAX;
};

enum class GameState : char
{
	PAUSED,
	RUNNING,
	STOPPED,
	WAITING,
	VICTORY,
	GAMEOVER
};