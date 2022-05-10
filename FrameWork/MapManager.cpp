#include "Include.h"

MapManager Mmanager;


MapManager::MapManager()
{
	blockX = 0;
	blockY = 0;
}

MapManager::~MapManager()
{

}

void MapManager::BlockDraw()
{

	for (int i = 0; i < 19; i++)
	{
		for (int j = 0; j < 32; j++)
		{
			if (blockArr[i][j] == 1)
			{
				SetRect(&b_rc, j * 40, i * 40, blockX + 40, blockY + 40);
			}
		}
	}
}

void MapManager::BlockCollition()
{
	
}