#include "Include.h"

Map map;


Map::Map()
{
    

}

Map::~Map()
{
}

void Map::Init()
{
	char FileName[256];

	sprintf_s(FileName, "./resource/Img/map1/pink.png");
	block.Create(FileName, false, D3DCOLOR_XRGB(0, 0, 0));

	sprintf_s(FileName, "./resource/Img/map1/black.png");
	backGround.Create(FileName, false, D3DCOLOR_XRGB(0, 0, 0));


}

void Map::Update(double frame)
{

}

void Map::Draw()
{

	if (Gmanager.m_GameStart == true)
	{
		for (int i = 0; i < 19; i++)
		{
			for (int j = 0; j < 32; j++)
			{
				if (mapArr[i][j] == 1)
				{
					block.RenderDraw(j * 40, i * 40, 0, 0, 40, 40, 0, 1, 1);
					SetRect(&b_rc[i][j], j * 40, i * 40, j * 40 + 40, i * 40 + 40);
                    
				} else if (mapArr[i][j] == 0)
				{
					backGround.RenderDraw(j * 40, i * 40, 0, 0, 40, 40, 0, 1, 1);
				}
			}
		}

	}


    if (Gmanager.m_GameStart == true)
    {
        for (int i = 0; i < 19; i++)
        {
            for (int j = 0; j < 32; j++)
            {
                if (mapArr[i][j] == 1)
                {
                    SetRect(&b_rcbubble[i][j], j * 40, i * 40, j * 40 + 40, i * 40 + 40);
                }
                else if (mapArr[i][j] == 0)
                {
                  
                }
            }
        }

    }
}

// 만약[row][col]의 값이 1일때

//타겟(플레이어)의 사각형 밑(pl,pb)(pr,pb) 이 블록사각형(bl,bt)(br,bt)값과 같으면
//그 위치가 지금의 캐릭위치 (밟고올라가있는 모습)이 됨
// 
// 이렇게 생각하지말고 rect[i][j] 에 충돌구현 다해주고, 플레이어가 점프하는중일땐 rect충돌 false반환
// 그렇지않고 점프하는중이 아닐때(떨어지고있을때) rect 충돌  true반환 

BOOL Map::BlockCollision() //플레이어와 블록이 충돌 했는지 알려주는 함수
{
    for (int i = 0; i < 19; i++)
    {
        for (int j = 0; j < 32; j++)
        {
            if (mapArr[i][j] == 1)
            {

                if (target.p_rc2.left >= map.b_rc[i][j].left &&
                    target.p_rc2.left <= map.b_rc[i][j].right &&
                    target.p_rc2.top >= map.b_rc[i][j].top &&
                    target.p_rc2.top <= map.b_rc[i][j].bottom)
                {

                    target.nowY++;
                  
                    return true;
                }
                
                   

                if (target.p_rc2.left >= map.b_rc[i][j].left &&
                    target.p_rc2.left <= map.b_rc[i][j].right &&
                    target.p_rc2.bottom >= map.b_rc[i][j].top &&
                    target.p_rc2.bottom <= map.b_rc[i][j].bottom)


                {
                    
                    return true;
                }

                if (target.p_rc2.right >= map.b_rc[i][j].left &&
                    target.p_rc2.right <= map.b_rc[i][j].right &&
                    target.p_rc2.top >= map.b_rc[i][j].top &&
                    target.p_rc2.top <= map.b_rc[i][j].bottom)

                   
                {
                 
                    return true;
                }

                if (target.p_rc2.right >= map.b_rc[i][j].left &&
                    target.p_rc2.right <= map.b_rc[i][j].right &&
                    target.p_rc2.bottom >= map.b_rc[i][j].top &&
                    target.p_rc2.bottom <= map.b_rc[i][j].bottom)

                {
                    
                    return true;
                }
            }
        }
    }


    return false;
}