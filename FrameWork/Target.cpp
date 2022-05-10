#define _CRT_NONSTDC_NO_DEPRECATE
#include "Include.h"


Target target;


Target::Target()
{
	nowX = 200; //현재캐릭X위치
	nowY = 580; //현재캐릭 y위치
	target.damgeX = 220; //데미지존 (struct tar target) 의 x위치
	target.damgeY = 600; //데미지존 (strcut tar target) 의 y위치

	nowH = nowY; // target.m_H
	jumpH = 23; //점프 높이 초기화
	
}

Target::~Target()
{
}

void Target::Init()
{
	char FileName[256];
	/* 왼쪽움직임 */
	for (int i = 0; i < 7; i++)
	{
		sprintf_s(FileName, "./resource/Img/taget/left_%02d.png", i + 1);
		playerL[i].Create(FileName, false, D3DCOLOR_XRGB(0, 0, 0));

	}

	/* 오른쪽 움직임*/
	for (int i = 0; i < 7; i++)
	{
		sprintf_s(FileName, "./resource/Img/taget/right_%02d.png", i + 1);
		playerR[i].Create(FileName, false, D3DCOLOR_XRGB(0, 0, 0));

	}
	/*멈춤*/
	player.Create("./resource/Img/stand/01.png", false, D3DCOLOR_XRGB(0, 0, 0));

	/*점프*/
	playerJR.Create("./resource/Img/jump/00.png", false, D3DCOLOR_XRGB(0, 0, 0));

	/*샷*/
	for (int i = 0; i < 2; i++)
	{
		sprintf_s(FileName, "./resource/Img/shot/%02d.png", i + 1);
		playerSR[i].Create(FileName, false, D3DCOLOR_XRGB(0, 0, 0));
	}
}

void Target::Update()
{
	SetRect(&p_rc2, nowX, nowY, nowX + 57, nowY + 57);
	Move();
	Jump();
	EraseBubble();
	TouchEraseBubble();
}

void Target::EraseBubble() {

	tg.damgeX = nowX + 30.0f; //캐릭터 충돌값
	tg.damgeY = nowY + 30.0f;


	if (GetBubble()->size() != 0) //버블이 존재할경우
	{
		for (auto iter = GetBubble()->begin(); iter != GetBubble()->end(); ++iter) //첫버블부터 막버블까지 버블이 있는지 확인
		{
			#pragma region Y축관련
			//if (iter->GetY() < -1/*iter->GetstY() - 500*/ || iter->GetY() > iter->GetstY() + 500) //일정범위내에 충돌하지않으면 일단은 -1로 하면 맵밖으로 나가면 즉시삭제한다.
			//{

			//	iter->Setm_Life2(false);
			//
			//	if (GetTickCount64() >= iter->Time + 10000) {
			//		iter->Time = GetTickCount64();
			//		GetBubble()->erase(iter);
			//		break;
			//	}
			//}
			#pragma endregion
			if (iter->GetX() < iter->GetstX() - 200 || iter->GetX() > iter->GetstX() + 200 ) //X축으로 일정 거리 이상 넘어갈시
			{
				iter->Setm_Life2(false);

				if (GetTickCount64() >= iter->Time + 7000) {

					iter->Time = GetTickCount64();
					GetBubble()->erase(iter);
					break;
				}
			}

			if (GetTickCount64() >= iter->Time + 7100) {
				GetBubble()->erase(iter);
				break;
			}
		}
	}
}


void Target::TouchEraseBubble() {

	for (auto iter = GetBubble()->begin(); iter != GetBubble()->end(); ++iter) {
		if (GetTickCount64() >= iter->Time2 + 1200) {
			if (iter->bubblecol == true)
			{

				GetBubble()->erase(iter);
				break;
			}
		}
	}
}



void Target::Draw()
{



#pragma region Stop

	if (isMove == false && isAttack == false && isJumping == false && isDir == true)  //left 왼쪽으로 수정
	{
		player.Render(nowX, nowY, 0, 0.7, 0.7);
	}

	if (isMove == false && isAttack == false && isJumping == false && isDir == false) //right 오른쪽으로 수정 
	{
		player.Render(nowX + 60, nowY, 0, -0.7, 0.7);
	}

#pragma endregion

#pragma region move Left Right
	if (isMove == true && isAttack == false && isJumping == false && isDir == true) //왼쪽움직임
	{
		playerL[p_Count2].Render(nowX, nowY, 0, 0.7, 0.7);
	}

	if (isMove == true && isAttack == false && isJumping == false && isDir == false) //오른쪽움직임
	{
		playerR[p_Count1].Render(nowX, nowY, 0, 0.7, 0.7);
	}
#pragma endregion 

#pragma region jump Left Right
	if (isAttack == false && isJumping == true && isDir == false) //점프랜더 오른쪽
	{
		playerJR.Render(nowX + 60, nowY, 0, -0.7, 0.7);
	}

	if (isAttack == false && isJumping == true && isDir == true)//점프랜더 왼쪽
	{
		playerJR.Render(nowX, nowY, 0, 0.7, 0.7);
	}

#pragma endregion

#pragma region shot Left Right
	if (isDir == false && isAttack == true && isJumping == false && isMove == true) //슛 오른쪽
	{
		playerSR[p_Count7].Render(nowX, nowY, 0, 0.7, 0.7);

	}

	if (isDir == true && isAttack == true && isJumping == false && isMove == true) //슛 왼쪽
	{
		playerSR[p_Count7].Render(nowX + 60, nowY, 0, -0.7, 0.7);
	}
#pragma endregion

#pragma region stop shot Left Right 
	if (isDir == false && isAttack == true && isJumping == false && isMove == false) //가만히 슛 오른쪽
	{
		playerSR[p_Count7].Render(nowX, nowY, 0, 0.7, 0.7);
	}

	if (isDir == true && isAttack == true && isJumping == false && isMove == false) //가만히 슛 왼쪽
	{
		playerSR[p_Count7].Render(nowX + 60, nowY, 0, -0.7, 0.7);
	}

#pragma endregion

#pragma region stop shot jump Left right 

	if (isDir == false && isAttack == true && isJumping == true && isMove == false) //가만히 슛 점프 오른쪽
	{
		playerSR[p_Count7].Render(nowX, nowY, 0, 0.7, 0.7);
	}

	if (isDir == true && isAttack == true && isJumping == true && isMove == false) //가만히 슛 점프 왼쪽
	{
		playerSR[p_Count7].Render(nowX + 60, nowY, 0, -0.7, 0.7);
	}

	if (isDir == false && isAttack == true && isJumping == true && isMove == true) //가면서 슛 점프 오른쪽 
	{
		playerSR[p_Count7].Render(nowX, nowY, 0, 0.7, 0.7);
	}

	if (isDir == true && isAttack == true && isJumping == true && isMove == true) //가면서 슛 점프 왼쪽 
	{
		playerSR[p_Count7].Render(nowX + 60, nowY, 0, -0.7, 0.7);
	}

#pragma endregion


	if (Gmanager.m_Collision == true)
	{
		SetRect(&p_rc, target.damgeX, target.damgeY, target.damgeX + 140, target.damgeY + 160);
		dv_font.Fonts->DrawTextA(NULL, "C", -1, &p_rc, DT_LEFT, D3DCOLOR_ARGB(255, 255, 0, 0));
	}

	if ( ghost1.GhostPlayerCol() == true )
	{
		dv_font.Fonts->DrawTextA(NULL, "D", -1, &p_rc2, DT_LEFT, D3DCOLOR_ARGB(255, 255, 0, 0));
	}


	itoa(GetBubble()->size(), test, 10); //게임화면에 컨테이너 용량표시
	dv_font.DrawString(test, 0, 0);

}


void Target::BubbleCreate(int _pos)
{

	bubble.push_front(Bubble()); //함수를 호출하면 버블 컨테이너에 버블을 생성한다
	auto iter = GetBubble()->begin(); //첫번째 버블에
	iter->SetPos(_pos); //방향값을 넣는다

	if (GetBubble()->size() >= 11) //컨테이너 수 15개 제한
	{
		bubble.resize(10); //15개를 넘어가면 삭제
	}
}

void Target::Reset()
{
	target.damgeX = nowX + 20;
	target.damgeY = nowY + 20;
}

void Target::Jump()
{
	if (nowY >= 0) {

		if (isJumping == TRUE)
		{
			jumpH--;
			nowY -= jumpH;
			Reset();

			if (jumpH < 0)
			{
				jumpH = 23;
				nowH = nowY;
				isJumping = FALSE;
			}
		}
		playerJR.Render(nowX, nowY, 0, 0.7, 0.7);
	}
}


void Target::Gravity()
{
	if (target.damgeY >= 800) //650 땅위치
	{
			nowX = 640; //0 최좌측 초기값 0
			nowY = -20; // 좌측하단생성 초기값580
			Reset();
	}
	else
	{
		nowY += 6;
		target.damgeY += 6;
	}
}

void Target::Move()
{

	if (map.BlockCollision() == false) //떨어질 때 그래비티
	{
		Gravity();

	}
	else
	{
		if (GetTickCount64() - aniTime7 > 100) //슛
		{
			p_Count7++;
			if (p_Count7 > 1) p_Count7 = 0;
			aniTime7 = GetTickCount64();
		}
		if (GetTickCount64() - aniTime2 > 100) //움직임 왼
		{
			p_Count2++;
			if (p_Count2 > 6) p_Count2 = 0;
			aniTime2 = GetTickCount64();
		}
		if (GetTickCount64() - aniTime1 > 100) //움직임 오른
		{
			p_Count1++;
			if (p_Count1 > 6) p_Count1 = 0;
			aniTime1 = GetTickCount64();
		}

	}
}

