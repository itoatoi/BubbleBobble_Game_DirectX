#pragma once
#include "Include.h"

/*맵 배열은 define헤더 파일에 있음 ! 걍 클래스 안에 넣어도 무방할것같기두*/
class Map
{
	/* 맵 충돌처리
	1. 값이1인 배열의 크기를 바탕으로 충돌블럭 생성
	2. 플레이어, 몬스터, 아이템 모두 충돌블럭 위에 올라갈 수 있게 설정
	3. 점프시 블록 충돌 무시
	4. 중력은 몬스터와 아이템 플레이어에 설정 해주었기 때문에 중력설정 x

	필요한 함수들

	1. 생성자 소멸자
	2. 초기화 함수  init
	3. 충돌구현 함수 collision

	필요한 변수들

	1. 블록xy크기만큼의 충돌블럭들
	2.

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
	//list<Ghost> ghost;
public:
	Map();
	~Map();

	Sprite block; //핑크블록
	Sprite blockRect;
	Sprite backGround; //뒷배경검은색

	int x; //맵 x
	int y; //맵 y

	
	int m_Stage;

	RECT b_rc[19][32]; //충돌 블록 사각형만들기 변수

	RECT b_rcbubble[19][32];

	void Init();
	void Update(double frame);
	void Draw();
	BOOL BlockCollision(); //충돌블럭이 어케 작동되는지 정의하는 함수


	BOOL MonsterCollision();
	
	/*list<Ghost>* GetGhost()
	{
		return &ghost;
	}*/

	
};

extern Map map;
