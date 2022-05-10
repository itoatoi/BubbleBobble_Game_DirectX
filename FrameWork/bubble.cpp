#include "Include.h"

Bubble bubble;

Bubble::Bubble()
{
	bubble_x = target.nowX; //버블의 x위치. 캐릭터 몸에서 버블이 나와야하니까 bubble의 위치에 대입
	bubble_y = target.nowY; //버블의 y위치. 캐릭터 몸에서 버블이 나와야하니까 bubble의 위치에 대입
	sbubble_x = target.nowX; //캐릭터위치를 버블 충돌 위치에 대입
	sbubble_y = target.nowY;//캐릭터위치를 버블 충돌 위치에 대입
	m_BubbleCount = 0; // 버블 이미지 장수. 버블터질때나옴 
	m_BmCount = 0; // 버블 이미지 장수. 
	pos = 0; //버블 방향
	m_Life1 = true; // 버블의 이미지를 삭제하기위한 상태변수
	m_Life2 = true; // 버블팝을 그리기위한 상태변수
	m_BubbleAniTime = 0; // 버블 애니메이션
	m_bubble.dx = sbubble_x + 30.0f; //버블 충돌값
	m_bubble.dy = sbubble_y + 30.0f;//버블 충돌값

	m_bubble.drx = bubble_x;
	m_bubble.dry = bubble_y;
	Time = GetTickCount64();
	Time2 = GetTickCount64();
	Time3 = GetTickCount64();
}

Bubble::~Bubble()
{
}

void Bubble::Init()
{
}

void Bubble::Update()
{
	SetRect(&bub_rc, bubble_x, bubble_y, bubble_x + 41, bubble_y + 41);
	move();


	b_Left = m_bubble.drx;
	b_High = m_bubble.dry;


	if (m_Life2 == true) //버블 상태가 true일때
	{

		if (pos == 2) //방향이 A면
		{
			Move(-60.0f, 0); //A방향으로 10만큼 버블이 계속 이동
		}

		else if (pos == 4) //방향이 D면
		{
			Move(60.0f, 0); //10만큼 버블이 계속 이동
		}



		m_bubble.dx = sbubble_x + 40.0f; //버블의 충돌범위
		m_bubble.dy = sbubble_y + 30.0f; //버블의 충돌범위

		if (GetTickCount() - m_BubbleAniTime > 150)
		{
			if (m_BubbleCount >= 10) //버블 이미지가 마지막일 때
			{
				m_BubbleCount == 10; //마지막 버블 이미지에서 바뀌지않음 
			}
			else
			{
				m_BubbleCount++; //버블 이미지 증가
			}
		}
	}
	else if (m_Life2 == false)
	{

		if (GetTickCount() - m_BmAniTime > 168)
		{
			if (m_BmCount >= 39)									//버블 이미지가 마지막일때 
			{
				m_Life1 = false;									// 마지막 버블 이미지에서 바뀌지 않음

			}
			else
			{
				m_BmCount++;									// 버블 이미지 증가
			}

			m_BmAniTime = GetTickCount();
		}
	}

	BubblePlayerCol();
}

void Bubble::Draw() {



	if (m_Life2 == false)										// 버블이 false일때 큰버블 이미지 Draw
	{
		Gmanager.bbpimg[m_BmCount].Render(bubble_x, bubble_y, 0, 0.6, 0.6);
	}
	else if (m_Life2 == true)									// 버블이 true일때 작은버블 이미지 Draw
	{
		Gmanager.bbimg[m_BubbleCount].Render(bubble_x + 10, bubble_y + 10, 0, 0.6, 0.6);
		
	}


	
}

BOOL Bubble::BubbleCollision() //버블과 블록이 충돌 했는지 알려주는 함수
{
	for (int i = 0; i < 19; i++)
	{
		for (int j = 0; j < 32; j++)
		{
			if (mapArr[i][j] == 1)
			{
				if (IntersectRect(&temp, &bub_rc, &map.b_rcbubble[i][j]))
				{
					
					return true;
				}
			}
		}
	}

	return false;
}

void Bubble::BubblePlayerCol() //버블이랑 플레이어랑 충돌되는지 함수
{
	if (bubble_x >= 640) { //중앙좌표 640보다 작거나 같을때 버블과 타겟 원형충돌

		float distance = (float)sqrt((target.target.damgeX - bubble_x) * (target.target.damgeX - bubble_x) +
			(target.target.damgeY - bubble_y) * (target.target.damgeY - bubble_y));
		if (distance < 40) //충돌거리
		{

			SetRect(&bub_rc2, b_Left, b_High, b_Left + 100, b_High + 100);
			sound.m_bb->Play(NULL);
			bubble_x += 10; //충돌시 x축으로 10만큼 버블을 밀어내기
			bubblecol = true; //버블제거 true

		}
	}
	else if (bubble_x <= 1240) 
	{
		float distance = (float)sqrt((target.target.damgeX - bubble_x) * (target.target.damgeX - bubble_x) +
			(target.target.damgeY - bubble_y) * (target.target.damgeY - bubble_y));
		if (distance < 40)
		{

			SetRect(&bub_rc2, b_Left, b_High, b_Left + 100, b_High + 100);
			bubble_x -= 5;

			bubblecol = true;

		}
	}

	//if (bubblecol == true)
	//{
	//	if (GetTickCount64() >= Time3 + 1140)
	//	{
	//		//Gmanager.bbppimg[m_PopCount].Render(bubble_x-26, bubble_y-20, 0, 2.6,2.6);
	//	}

	//}
		
}

void Bubble::move()
{

	if (GetTickCount64() - aniTime2 >= 0)
	{


		if (BubbleCollision() == false)
		{						 //버블충돌이 false라면(즉 거의항상)

			float Yspeed = 0.9f;
			bubble_y -= Yspeed;

			if (bubble_y <= -50)
			{							 //천장너머에 닿으면
				bubble_y = 780; // 바닥너머 780좌표로 버블이동
			}
		}
		else
		{ //버블이 벽에 충돌시

			float Xspeed = 0.9f;

			if (bubble_x < 640)  //640
			{
				bubble_x += Xspeed;

				if (bubble_x == 300)
				{
					bubble_x = 300;
				}
			}

			if (bubble_x > 640) //640
			{
				bubble_x -= Xspeed;
			}
			/*	else
				{
					bubble_x += Xspeed;
				}*/

		}

		aniTime2 = GetTickCount64();
	}



}


#pragma region Set Get
void Bubble::SetPos(int _p)
{
	pos = _p;
}

int Bubble::GetPos()
{
	return pos;
}

void Bubble::Setm_Life1(bool _L)	// private에 접근하기 위한 Set함수
{
	m_Life1 = _L;						// 함수 호출시 버블 상태에 값을 넣음
}

bool Bubble::Getm_Life1()			// private의 값을 가져오기 위함 Get함수 
{
	return m_Life1;						// 함수 호출시 버블 상태를 가져옴
}

void Bubble::Setm_Life2(bool _L)	// private에 접근하기 위한 Set함수
{
	m_Life2 = _L;						// 함수 호출시 버블 상태에 값을 넣음
}

bool Bubble::Getm_Life2()			// private의 값을 가져오기 위함 Get함수 
{
	return m_Life2;						// 함수 호출시 버블 상태를 가져옴
}

float Bubble::GetX()				// private의 값을 가져오기 위함 Get함수 
{
	return bubble_x;						// 함수 호출시 버블 위치값을 가져옴
}

float Bubble::GetY()				// private의 값을 가져오기 위함 Get함수 
{
	return bubble_y;						// 함수 호출시 버블 위치값을 가져옴
}

float Bubble::GetstX()
{
	return sbubble_x;
}

float Bubble::GetstY()
{
	return sbubble_y;
}

void Bubble::Move(float _x, float _y)
{
	bubble_x += _x;
	bubble_y += _y;
}
#pragma endregion

