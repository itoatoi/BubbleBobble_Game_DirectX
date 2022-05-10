//#define _CRT_NONSTDC_NO_DEPRECATE
#include "Include.h"


Ghost ghost1(650.0f, 20.0f);




Ghost::Ghost()
{

	

}

Ghost::Ghost(double _nowX, double _nowY)
{
	g_nowX = _nowX;
	g_nowY = _nowY;

	m_GhostLife = true;

	Time = GetTickCount64();
	Time2 = GetTickCount64();
	
	nowH = g_nowY; // target.m_H
	jumpH = 23; //점프 높이 초기
}

Ghost::~Ghost()
{

}

void Ghost::Init()
{
	char FileName[256];

	for (int i = 0; i < 2; i++)
	{
		sprintf_s (FileName, "./resource/Img/ghost/%02d.png", i);
		Ghoimg[i].Create (FileName, false, D3DCOLOR_XRGB(0, 0, 0));
	}

}

void Ghost::Update()
{
	SetRect(&Ghost_rc2, g_nowX, g_nowY, g_nowX + 57, g_nowY + 57);
	Move(g_nowX, g_nowY);

	if (GetTickCount64() - m_GhostAniTime1 > 100.0f)
	{
		m_GhostCount++;
		if (m_GhostCount > 1) m_GhostCount = 0;
		m_GhostAniTime1 = GetTickCount64();
	}

}


void Ghost::Draw(double _nowX, double _nowY)
{
	if (Gmanager.m_GameStart == true)
	{
		if (m_GhostLife == true)
		{
			if (g_nowX > 640 )
			{
				Ghoimg[m_GhostCount].Render(g_nowX + 60, g_nowY, 0, -0.7, 0.7);
			}
			else if (g_nowX < 640 || g_nowY )
			{
				Ghoimg[m_GhostCount].Render(g_nowX , g_nowY, 0, 0.7, 0.7);
			}
		}
		
	}
	
}

void Ghost::GhostCreate(int _pos)
{

}

BOOL Ghost::GhostCol() //블럭이랑 충돌하는지
{
	for (int i = 0; i < 19; i++)
	{
		for (int j = 0; j < 32; j++)
		{
			if (mapArr[i][j] == 1)
			{
				if (IntersectRect(&temp, &Ghost_rc2, &map.b_rc[i][j]))
				{
					return true;
				}
			}
		}
	}
}

BOOL Ghost::GhostPlayerCol() //고스트랑 플레이어랑 충돌하는지
{
	for (int i = 0; i < 19; i++)
	{
		for (int j = 0; j < 32; j++)
		{
			if (mapArr[i][j] == 1)
			{
				if (IntersectRect(&temp, &target.p_rc2, &Ghost_rc2))
				{
					target.isAlive = false;
					target.isMonCol = true;
					sound.m_col->Play(NULL);
					
					return true;
				}
			}
		}
	}
}

void Ghost::Jump()
{

	if (g_nowY >= 0) {

		if (g_isJumping == TRUE)
		{
			jumpH--;
			g_nowY -= jumpH;

			if (jumpH < 0)
			{
				jumpH = 23;
				nowH = g_nowY;
				g_isJumping = FALSE;
			}
		}
		/*playerJR.Render(nowX, nowY, 0, 0.7, 0.7);*/
	}

}


void Ghost::Gravity()
{
	////isJumping = false;

	//if (gho.damgeY >= 700) //650 땅위치
	//{
	//	g_nowY = g_nowY;
	//	gho.damgeY = gho.damgeY;
	//}
	//else
	//{
	//	g_nowY += 6;
	//	gho.damgeY += 6;
	//}
}

void Ghost::Move(double _x, double _y) // 고스트 움직이는 함수
{
	static bool arrivedX = true;
	static bool arrivedY = true;

	double stop = 500.0f;

	if (m_GhostLife == true && g_nowX > 640)
	{

		if (g_nowX == 650.0f && arrivedX == true)
		{
			arrivedY = false;
			if (GetTickCount64() >= (Time + 3000)) //5초뒤에 움직임 시작
			{
				g_nowY += 3.0f; //계속내려가고

				if (g_nowY > stop) // 만약 y좌표가 스탑보다 크다면 멈춤 (스탑값 적용됨)
				{
					g_nowY = stop;
					arrivedY = true;
					Time = GetTickCount64();
				}
			}
		}

		if (g_nowY == stop && arrivedY == true) //y좌표가 스탑값이랑 같다면
		{
			arrivedX = false;
			if (GetTickCount64() >= (Time + 3000)) //9초뒤
			{
				g_nowX += 3.0f; // x좌표 이동

				if (g_nowX > stop + 640) //만약 x좌표가 스탑+640(반갈라서움직이기떄문에 640 기준으로둠) 보다 크다면
				{
					g_nowX = stop + 640; // 그값을대입함 멈춤
					arrivedX = true;
					Time = GetTickCount64();
				}
			}
		}

		if (g_nowX == stop + 640 && arrivedX == true) //만약  지금x좌표가 stop+640값이랑 같다면
		{
			arrivedY = false;
			if (GetTickCount64() >= (Time + 3000)) //13초뒤
			{
				g_nowY -= 5.0f; //다시 올라감

				if (20 > g_nowY) //만약 지금y좌표가 20보다 작아지면
				{
					g_nowY = 20; //20에 머물러있음
					arrivedY = true;
					Time = GetTickCount64();
				}
			}
		}

		if (g_nowY == 20 && arrivedY == true) //지금 nowY가 20이랑 같다면
		{
			arrivedX = false;
			if (GetTickCount64() >= (Time + 3000)) //17초뒤
			{
				g_nowX -= 5.0f; //x좌표가 다시 줄어듬

				if (650 > g_nowX) //x좌표가 650보다 작아진다면
				{
					g_nowX = 650; //지금  x좌표는 650으로 멈춤
					arrivedX = true;
					Time = GetTickCount64(); //여기서 타임 초기화 루틴이 끝나는자리
				}
			}
		}
		m_GhostAniTime = GetTickCount64();
	}

	/* 고스트가 3초전 타겟의 nowX,nowY 의 좌표를 따라감 */

}






