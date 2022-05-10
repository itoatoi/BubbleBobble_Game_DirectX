#pragma once
#include "Include.h"

/* 변수 앞이름은 소문자로 썼음!
	AniTime -> aniTime
	함수 이름은 대문자로 시작
	Target();
*/

/*
*
	공룡의 상태

1. 시작 지정한위치에 서있음
2. 점프중이 아님
3. 키가 움직이전가진 멈춤상태(걸어가는 포즈 x)

	공룡의 능력

1. 버블 발사 스페이스 한번에 버블 한번만 나옴(데미지존)
2. 버블 발사 범위에 몬스터가 닿으면 캡쳐 x축을 이용해 범위지정
3. 캡쳐한 버블을 터트리기
3. 점프키 한번에 한번점프
4. 떨어질때 아무것도하지 못하고 떨어짐 좌우만 가능
4. 아이템 획득

*/

typedef struct Tar //뎀지존 strcutb
{
	//2d게임이기 떄문에 xy만 일단 쓰는걸로 생각함 추가할게 있으면 추가하삼
	double  damgeX; //dx
	double	damgeY; //dy
		/*, drx, dry, drz*/	// 데미지존 
};

class Target //플레이어로쓰는 타겟클래스 
{

	char test[256];
	Tar tg;
	list<Bubble> bubble;

public:
	//배열수는 스프라이트 장수에따라 상이함
	// p_count -> 스프라이트 넘겨주는 변수, 스프라이트도 추가할땐 9->10숫자만 바꾸기
	// anitime -> 애니메이션 타임 변수 , 애니타임은 순서대로 해놨으니 추가로 넣을거면 숫자만바꾸게하면됨
	// 두개는 이름 그대로 씀 !
#pragma region Sprite
	Sprite line;
	int l_count;
	DWORD linetime;

	Sprite playerR[7]; //Tgimg_right[7] 오른움직임
	int p_Count1;  //오른움직임
	DWORD aniTime1; //오른움직임

	Sprite playerL[7];//Tgimg_left[7] 왼움직임
	int p_Count2; //왼움직임
	DWORD aniTime2; //왼움직임

	Sprite player; //Tgimg_stand; 서있음
	int p_Count0; //서있음
	int p_Count;
	DWORD aniTime0; //서있음
	DWORD aniTime0_1;

	Sprite playerJR; //점프 오른
	int p_Count3; //점프오른
	DWORD aniTime3; //점프오른

	Sprite playerJL[1]; //점프 왼
	int p_Count4; //점프 왼
	DWORD aniTime4; //점프 왼

	Sprite playerSR[2]; //슛(버블발사) 오른
	int p_Count7; //슛(버블발사) 오른
	DWORD aniTime7; //슛(버블발사) 오른

	Sprite playerSL[10]; //슛(버블) 왼
	int p_Count8; //슛(버블) 왼
	DWORD aniTime8; //슛(버블) 왼

	Sprite playerD[6]; //죽음 //죽음효과는 버블이랑 몬스터 충돌한 뒤에 쓰기로 하장
	int p_Count9;
	DWORD aniTime9;
 #pragma endregion

	DWORD AniTime2;

	 //입열고 있ㅇ으면 트루 아니면 펄스
	BOOL isAlive = true; //m_Life; 살아있으면 트루
	BOOL isMove = false; //target_move; 움직이고 있으면 트루
	BOOL isDir = false; //target_move_dir; 바라보는 방향 false->왼쪽,true-> 오른쪽
	BOOL isJumping = false; //isJump; 점프를 하는중인지 하는중이면 true
	BOOL JumpState; //이건 뭔지 몰라서 걍 냅둠 

	BOOL isAttack = false; //공격하는지 공격하면 트루 안하면 펄스
	BOOL isAttactDir = false;
	BOOL isMonCol = false; //몬스터와 충돌했는지 맞으면 트루 안하면 펄스
	BOOL GravityState = true;



	double nowX;//m_W; 캐릭의 현재 위치 x
	double nowY;//m_H; 캐릭의 현재 위치 y

	int nowH; //NowH; 캐릭의 현재 높이
	int jumpH;//JumpH; 캐릭의 점프 높이

	Tar target; //타켓위치 스트럭트 

	RECT p_rc; //m_rc; 플레이어q버블 충돌상자 충돌사거리를 설명하는거 같음
	RECT p_rc2; //플래이어의 충돌크기


	Target();
	~Target();

	void Move();
	void Gravity();
	void Init();
	void Update();
	void Draw();
	void Reset();
	void Jump();
	void EraseBubble();
	void TouchEraseBubble();

	///////////////////////
	void BubbleCreate(int _pos);

	list<Bubble>* GetBubble()
	{
		return &bubble;
	}


};


extern Target target;