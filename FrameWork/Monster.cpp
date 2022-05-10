#include "Include.h"

Monster monster1(640.0f, -10.0f);
Monster monster2(640.0f, -100.0f);
Monster monster3(640.0f, -500.0f);

//double tempPosition;

Monster::Monster()
{

}

Monster::Monster(double _mX, double _mY)
{
	m_nowX = _mX;
	m_nowY = _mY;

	m_jumpH = 23.0f;
	m_nowH = m_nowY;

	m_speed = 2.0f;

	tempPositionX = 40;

	Point a = { m_nowX, m_nowY };
	Point b = { target.nowX, target.nowY };

	isAlive = true;
	isPlayerCol = false;
	isBubbleCol = false;
	isJumping = false;
	isWall = false;
	isDir = true; //왼쪽
	isTimeOut = false;
	

	//Time = GetTickCount64();
}

Monster::~Monster()
{

}

void Monster::Init()
{
	char FileName[256];

	for (int i = 0; i < 4; i++)
	{
		sprintf_s(FileName, "./resource/Img/monster/%02d.png", i);
		m_img[i].Create(FileName, false, D3DCOLOR_XRGB(0, 0, 0));
	}
	
	for (int i = 0; i < 3; i++)
	{
		sprintf_s(FileName, "./resource/Img/monster/capture/%02d.png", i);
		m_capture[i].Create(FileName, false, D3DCOLOR_XRGB(0, 0, 0));
	}

	for (int i = 0; i < 11; i++)
	{
		sprintf_s(FileName, "./resource/Img/monster/death/%02d.png", i);
		m_die[i].Create(FileName, false, D3DCOLOR_XRGB(0, 0, 0));
	}

	for (int i = 0; i < 6; i++)
	{
		sprintf_s(FileName, "./resource/Img/monster/capture/timeout/%02d.png", i);
		m_timeout[i].Create(FileName, false, D3DCOLOR_XRGB(0, 0, 0));
	}
}

void Monster::Update()
{
	SetRect(&m_rc, m_nowX, m_nowY, m_nowX + 57, m_nowY + 57); // 충돌상자 만들어주기
	//TarMonCollision();

	mon.damgeX = m_nowX + 20.0f;	//고스트의 충돌범위		
	mon.damgeY = m_nowY + 20.0f;

	if (isBubbleCol == false)
	{
		if (GetTickCount64() - m_AniTime1 > 100.0f) //계속 이미지 랜더중
		{
			m_Count1++;
			if (m_Count1 > 1) m_Count1 = 0;
			m_AniTime1 = GetTickCount64();
		}
		//SearchMove();
		Move();
		//Jump();
	}
	
	if (isBubbleCol == true)
	{
		if (GetTickCount64() - m_AniTime2 > 300.0f) //초록 버블 이미지
		{
			m_Count2++;
			if (m_Count2 > 2) m_Count2 = 0;
			m_AniTime2 = GetTickCount64();
		}

		if (GetTickCount64() - m_AniTime4 > 300.0f) //버블 점점빨간 이미지
		{
			m_Count4++;
			if (m_Count2 > 5) m_Count4 = 0;
			m_AniTime4 = GetTickCount64();
		}

		if (GetTickCount64() - m_AniTime5 > 300.0f) //초록 버블 이미지
		{
			m_Count5++;
			if (m_Count5 > 10) m_Count5 = 0;
			m_AniTime5 = GetTickCount64();
		}
		//Time = GetTickCount64();
		CaptureMove();
	}

	if (TarMonCollision() == true)
	{
		if (GetTickCount64() - m_AniTime3 > 300.0f) //계속 이미지 랜더중
		{
			m_Count3++;
			if (m_Count3 > 10) m_Count3 = 0;
			m_AniTime3 = GetTickCount64();
		}
	}

	//버블 사거리 안에 들어오면 버블지워지는 업뎃
	for (auto iter = target.GetBubble()->begin(); iter != target.GetBubble()->end(); ++iter) //첫버블부터 막버블까지 찾으면서
	{
		for (int i = 0; i < 1; i++)
		{

			heat[i] = (float)sqrt((mon.damgeX - iter->bubble_x) * (mon.damgeX - iter->bubble_x) +	// 버블과 몬스터의 충돌값이
				(mon.damgeY - iter->bubble_y) * (mon.damgeY - iter->bubble_y));

			if (heat[i] < 40)	//충돌거리								
			{

				if (iter->Getm_Life2() == true) //버블상태(라이프)가 참이라면 (빠른랜더)
				{
				
				}
				iter->Setm_Life2(true);

				if (iter->Getm_Life1() == true)
				{
					isBubbleCol = true;
					sound.m_death->Play(NULL);
					iter = target.GetBubble()->erase(iter);
					//MessageBox(NULL, "버블과 타겟충돌", "asd", 0);
					break;
				}
			}
		}
		break;			//break
	}
}

void Monster::Draw(double _mX, double _mY)
{

	if (isAlive == true && isDir == true && isBubbleCol == false) //왼쪽랜더
	{
		m_img[m_Count1].Render(_mX , _mY, 0, 0.7, 0.7);
	}

	if (isAlive == true &&  isDir == false && isBubbleCol == false) //오른쪽랜더
	{
		//MessageBox(NULL, "00", "벽", 0);
		m_img[m_Count1].Render(_mX + 60, _mY, 0, -0.7, 0.7);
	}

	if (isBubbleCol == true)
	{
		m_capture[m_Count2].Render(_mX, _mY, 0, 0.5, 0.5);
	}

	if (isBubbleCol == true && isTimeOut == false)
	{
		m_capture[m_Count2].Render(_mX, _mY, 0, 0.5, 0.5);
	}

	if (TarMonCollision() == true)
	{
		m_die[m_Count3].Render(_mX, _mY, 0, 0.5, 0.5);
	}

	if (isBubbleCol == true && isTimeOut == true )
	{
		m_timeout[m_Count4].Render(_mX, _mY, 0, 0.5, 0.5);
	}
}

void Monster::Gravity()
{
	if (m_nowY >= 800) //650 땅위치
	{
		m_nowX = 640; //0 최좌측 초기값 0
		m_nowY = -20; // 좌측하단생성 초기값580
		//Reset();
	}
	else
	{
		m_nowY += 3;
	}
}

void Monster::Jump()
{
	if (m_nowY >= 0) {

		if (isJumping == TRUE)
		{
			m_jumpH--;
			m_nowY -= m_jumpH;
			//Reset();

			if (m_jumpH < 0)
			{
				m_jumpH = 23;
				m_nowH = m_nowY;
				isJumping = FALSE;
			}
		}
	}
}

//기본 움직임 함수 
void Monster::Move()
{
	double m_speed = 3.0f;
	

	if (BlockCollision() == false) //떨어질 때 그래비티
	{
		Gravity();
	}
	else if (BlockCollision() == true && Wall() == false && isDir == true) //왼으로 갈때 (벽이아닐때)
	{
		m_nowX -= m_speed;
	}
	else if (BlockCollision() == true && Wall() == false && isDir == false)//오른으로 갈때 (벽이 아닐때)
	{
		m_nowX += m_speed;
	}
	else if (BlockCollision() == true && Wall() == true && isDir == true) //왼쪽방향인데 벽에 닿았을때
	{
		m_nowX += m_speed; //다시 돌아서 가!
		
	}
	else if (BlockCollision() == true && Wall() == true && isDir == false) //오른쪽방향인데 벽에 닿았을때
	{
		m_nowX -= m_speed; //다시 돌아서 가!
	}
	
}


//블록과 몬스터가 충돌했는지 알려주는 함수
BOOL Monster::BlockCollision()
{
	for (int i = 0; i < 19; i++)
	{
		for (int j = 0; j < 32; j++)
		{
			if (mapArr[i][j] == 1)
			{
				if (m_rc.left >= map.b_rc[i][j].left &&
					m_rc.left <= map.b_rc[i][j].right &&
					m_rc.top >= map.b_rc[i][j].top &&
					m_rc.top <= map.b_rc[i][j].bottom)
				{

					//m_nowY++;

					return true;
				}



				if (m_rc.left >= map.b_rc[i][j].left &&
					m_rc.left <= map.b_rc[i][j].right &&
					m_rc.bottom >= map.b_rc[i][j].top &&
					m_rc.bottom <= map.b_rc[i][j].bottom)


				{
					return true;
				}

				if (m_rc.right >= map.b_rc[i][j].left &&
					m_rc.right <= map.b_rc[i][j].right &&
					m_rc.top >= map.b_rc[i][j].top &&
					m_rc.top <= map.b_rc[i][j].bottom)


				{
					return true;
				}

				if (m_rc.right >= map.b_rc[i][j].left &&
					m_rc.right <= map.b_rc[i][j].right &&
					m_rc.bottom >= map.b_rc[i][j].top &&
					m_rc.bottom <= map.b_rc[i][j].bottom)

				{
					return true;
				}
				
				
			}
		}
	}


	return false;
}

//캡쳐된 버블과 블록테두리가 충돌 했는지 알려주는 함수
BOOL Monster::BubbleWallCollision()
{
	for (int i = 0; i < 19; i++)
	{
		for (int j = 0; j < 32; j++)
		{
			if (mapArr[i][j] == 1)
			{
				if (IntersectRect(&temp, &map.b_rc[i][0], &m_rc))
				{
					
					return true;
					break;
				}
				else if (IntersectRect(&temp, &map.b_rc[i][31], &m_rc))
				{
					
					return true;
					break;
				}
				else if (IntersectRect(&temp, &map.b_rc[0][j], &m_rc))
				{
					//MessageBox(NULL, "00", "벽", 0);
					
					return true;
					break;
				}
				else if (IntersectRect(&temp, &map.b_rc[18][j], &m_rc))
				{
					//MessageBox(NULL, "00", "벽", 0);
					
					return true;
					break;
				}
				
			}
			else
			{
				return false;
			}
		}
	}

	
}


//몬스터가 벽(블록테두리) 인지아닌지 알아채는 함수
BOOL Monster::Wall()
{
	for (int i = 0; i < 19; i++)
	{
		for (int j = 0; j < 32; j++)
		{

			if (IntersectRect(&temp, &map.b_rc[i][0], &m_rc)) //맵 블록 맨첫줄테두리에 콩 닫는지 닿으면 구문실행
			{
				isDir = false; //위치바뀌고 
				break; //계속 벽에닿았다고 호출되면 안되니까 브레이크 걸기
				return true; //닿았다고 트루
			}

			else if (IntersectRect(&temp, &map.b_rc[i][31], &m_rc)) //맵 블록 맨끝줄테두리에 콩 닫는지 닿으면 구문실행
			{
				isDir = true; //위치 바뀌고
				break; //계속 벽에 닿았다고 호출되면 안되니까 브레이크 걸기
				return true;
				
			}

		}
	}

	return false;
}

//타겟(공룡)을 찾아다니는 함수  미완성
void Monster::SearchMove() 
{
	double m_speed = 3.0f;

	if (target.nowY == m_nowY)
	{
		if (target.nowX <= m_nowX)
		{
			m_nowX -= m_speed;

			for (int i = 0; i < 19; i++)
			{
				for (int j = 0; j < 32; j++)
				{
					if (IntersectRect(&temp, &map.b_rc[18][j], &m_rc) == false)
					{
						Jump();
					}
				}
			}
				
		}
		else if (target.nowX >= m_nowX)
		{
			//MessageBox(NULL, "c", "", 0);
			m_nowX += m_speed;
		}
	}
	if (target.nowY != m_nowY)
	{
		
	}
}

//몬스터가 버블에 갇혀있을시 움직이는 함수
void Monster::CaptureMove() //여기 수정 (시간되면 빨개지는거 못하겠음)
{
	double m_speed = 1.0f;

	
	if (BubbleWallCollision() == false) //버블이된 몬스터와 맵블럭충돌이 false라면
	{

		m_nowY -= m_speed;

		if (m_nowY <= -50)
		{							 //천장너머에 닿으면
			m_nowY = 780;			 //바닥너머 780좌표로 버블이동
		}

		//isTimeOut = true;
	}

	else if (BubbleWallCollision() == true)
	{

		m_nowX += m_speed;

		if (m_nowX > 640) //640
		{
			m_nowX -= m_speed;
		}

		//isTimeOut = true;

	}

}

//if (BubbleWallCollision() == true)
//{
//	m_nowX += m_speed;
//
//	if (m_nowX > 640) //640
//	{
//		m_nowX -= m_speed;
//	}
//
//	Time = GetTickCount64();
//	isTimeOut = true;
//}
//몬스터가 타겟이랑 부딪힐때 상태변환해주는 함수
BOOL Monster::TarMonCollision() //타겟이랑 몬스터랑 충돌되는지 
{
	if (isBubbleCol == true) //버블에 맞았으면
	{
		if (IntersectRect(&temp, &m_rc, &target.p_rc2) == true) //타겟이랑 버블된몬스터랑 충돌되면
		{
			isBubbleCol = false; //버블상태 해제
			isAlive = false; //죽음
			return true;
		}
	}
	
}

//else if (GetTickCount64() >= (Time + 15000))
		//{
		//	MessageBox(NULL, "00", "벽", 0);
		//	m_nowY -= m_speed;

		//	if (m_nowY <= -50)
		//	{							 //천장너머에 닿으면
		//		m_nowY = 780;			 //바닥너머 780좌표로 버블이동
		//	}

		//	isTimeOut = true;
		//	
		//}


//m_nowY -= m_speed;
//
//
//if (m_nowY <= -50)
//{							 //천장너머에 닿으면
//	m_nowY = 780;			 //바닥너머 780좌표로 버블이동
//}
//
//if (GetTickCount64() >= (Time + 10000)) //5초뒤
//{
//	//MessageBox(NULL, "", "", 0);
//
//
//	//if (BubbleWallCollision() == false) //버블이된 몬스터와 맵블럭충돌이 false라면
//	//{
//
//	//	m_nowY -= m_speed;
//
//	//	if (m_nowY <= -50)
//	//	{							 //천장너머에 닿으면
//	//		m_nowY = 780;			 //바닥너머 780좌표로 버블이동
//	//	}
//
//	//	isTimeOut = true;
//	//}
//
//	//else if (BubbleWallCollision() == true)
//	//{
//
//	//	m_nowX += m_speed;
//
//	//	if (m_nowX > 640) //640
//	//	{
//	//		m_nowX -= m_speed;
//	//	}
//
//	//	isTimeOut = true;
//	//	
//	//}
//
//	isTimeOut = true;
//	Time = GetTickCount64();
//}
//
//}
//	else
//	{
//	m_nowX += m_speed;
//
//	if (m_nowX > 640) //640
//	{
//		m_nowX -= m_speed;
//	}
//
//	if (GetTickCount64() >= (Time + 10000)) //5초뒤
//	{
//		//MessageBox(NULL, "", "", 0);
//
//
//		//if (BubbleWallCollision() == false) //버블이된 몬스터와 맵블럭충돌이 false라면
//		//{
//
//		//	m_nowY -= m_speed;
//
//		//	if (m_nowY <= -50)
//		//	{							 //천장너머에 닿으면
//		//		m_nowY = 780;			 //바닥너머 780좌표로 버블이동
//		//	}
//
//		//	isTimeOut = true;
//		//}
//
//		//else if (BubbleWallCollision() == true)
//		//{
//
//		//	m_nowX += m_speed;
//
//		//	if (m_nowX > 640) //640
//		//	{
//		//		m_nowX -= m_speed;
//		//	}
//
//		//	isTimeOut = true;
//		//	
//		//}
//
//		isTimeOut = true;
//		Time = GetTickCount64();
//	}
//	}

//if (BubbleWallCollision() == false && isBubbleCol == true) //버블이된 몬스터와 맵블럭충돌이 false라면 && isTimeOut이 false라면
//{
//	captureTickCount = GetTickCount64();
//
//	if (captureTickCount - startTickCount >= 0) //바로 움직임 시작
//	{
//		m_nowY -= m_speed;
//
//		if (m_nowY <= -50)
//		{
//			m_nowY = 780;
//		}
//	}
//	if (captureTickCount - startTickCount >= 5000)
//	{
//		MessageBox(NULL, "00", "5", 0);
//		changeTickCount = GetTickCount64();
//
//		if (startTickCount - changeTickCount >= 20000)
//		{
//			MessageBox(NULL, "00", "20", 0);
//			isTimeOut = true;
//
//			m_nowY -= m_speed;
//
//			if (m_nowY <= -50)
//			{
//				m_nowY = 780;
//			}
//			Time = GetTickCount64();
//		}
//	}
//
//}