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

 /*

	 기본 충동처리

	 = 사각형 출동 판정 처리
	 플레이어기의 충돌 판정 좌표를 (ML, MT) ~ (MR, MB), 탄의 충돌 판정 좌표를 (BL, BT) ~ (BR, BB)라고 해보자.
	 (ML, MT), (BL, BT)는 각각의 사각형의 왼쪽 위 좌표이고 (MR. MB), (BR, BB)는 사각형의 오른쪽 아래 좌표이다.
	 이 경우, 플레이어기에 탄의 충돌 조건은 다음과 같다.
	 * ML < BR && BL < MR && MT < BB && BT < MB

	 = 원을 이용한 충돌 판정 처리
	 원을 이용한 충돌 판정 처리는 다음과 같다.
	 플레이어기의 중심좌표를 (MX, MY), 탄의 중심좌표를 (BX, BY)라고 하고, 플레이어기의 충돌 판정 반경을 MR,
	 탄의 충돌 판정 반경을 BR이라고 하자. 이때 플레이어기와 탄의 충돌 조건은 아래와 같다.
	 * (MX-BX)*(MX-BX) + (MY-BY)*(MY-BY) < (MR+BR)*(MR+BR)

 */

class Monster
{
public:
	
	struct Point
	{
		double damgeX, damgeY;
	};

	double m_nowX;
	double m_nowY;

	double m_jumpH;
	double m_nowH;

	double m_speed;

	double tempPositionX;
	double tempPositionY;

	float heat[1];

	DWORD aniTime2;

	Point a;
	Point b;
	Point mon;

	RECT m_rc;
	RECT temp;

	Sprite m_img[4]; //평상시 이미지
	int m_Count1;
	DWORD m_AniTime1;

	Sprite m_capture[3]; //캡쳐된 이미지
	int m_Count2;
	DWORD m_AniTime2;

	Sprite m_die[11]; //죽는 이미지
	int m_Count3;
	DWORD m_AniTime3;

	Sprite m_timeout[6]; //버블빨간 이미지
	int m_Count4;
	DWORD m_AniTime4;

	int m_Count5;
	DWORD m_AniTime5;

	bool isAlive;
	bool isPlayerCol;
	bool isBubbleCol;
	bool isJumping;
	bool isTimeOut;
	bool isWall;
	bool isDir;

	unsigned __int64 Time;
	
public:

	Monster();
	Monster(double _mX, double _mY);
	~Monster();

	void Init();
	void Update();
	void Draw(double _mX, double _mY);

	void Jump();
	void Gravity();
	void Move();
	
	//double Distance(Point& p1, Point& p2);
	BOOL BlockCollision();
	BOOL Wall();
	BOOL BubbleWallCollision();
	BOOL TarMonCollision();

	void SearchMove();
	void CaptureMove();
	//void Reset();
};

extern Monster monster1;
extern Monster monster2;
extern Monster monster3;