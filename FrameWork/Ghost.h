#pragma once
#include "Include.h"
/* 몬스터 객채 특징

 1. 첨 생성시 정해진 위치에서 생성
 2. 시간에 따라 속도가 빨라짐
 3. 멈춤 없이 계속 움직임
 4. 점프 가능, 점프할때 도리도리 움직임
 5. 버블캡쳐상태
 6. 공룡이 버블캡쳐상태를 일정시간동안 충돌하지 않으면 다시 라이프 트루가됨

 5. 우리가 몬스터의 움직임 패턴을 정해줘야 함
 6. 시간제한이 되면 (약1분) 앵그리모드로 바뀌면서 빨라지는걸 구현해야함
 7. 공룡 버블사거리에 (내뿜을시) 닿으면 바로 버블캡쳐상태가 되어 무력화됨
 8. 버블(버블은 꼭대기에 모여있으니까)을 터트리면 중력에의해 아이템을이 드랍됨
 9. 공룡과 충돌하면 공룡을 죽일 수 있음

 또 특징있으면 적어주삼 변수 뺼거 넣을거 생각하기 ㅎ

 */

//typedef struct Gho
//{
//	double  damgeX; //dx
//	double	damgeY; //dy
//};

class Ghost
{
public:

	bool m_GhostLife;
	bool m_GhostDeath;
	bool m_BubbleCapture;
	int m_Heart;
	int m_GhostCount;
	float heat[1];

	double g_nowX;//
	double g_nowY;
	int nowH; //NowH; 캐릭의 현재 높이
	int jumpH;//JumpH; 캐릭의 점프 높이

public:
	Ghost();
	~Ghost();

	Ghost(double _nowX,double _nowY);

	Sprite Ghoimg[2];

	DWORD m_GhostAniTime;
	DWORD m_GhostAniTime1;

	//Gho gho;
	BOOL g_isJumping;

	
	void Init();
	void Update();
	void Draw(double _nowX, double _nowY);

	void Jump();
	void Gravity();
	void Move(double _x, double _y);
	void GhostCreate(int _pos);

	BOOL GhostCol();
	BOOL GhostPlayerCol();

	RECT Ghost_rc2;
	RECT temp;

	unsigned __int64 Time;
	unsigned __int64 Time2;

};

extern Ghost ghost1;
