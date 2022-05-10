#include "Include.h"

/* 이터레이터, 컨테이너 관련 버블헤더부터 볼것!
재복이 소스가 일부섞여있어서 걸러서볼것!
bubble.h
bubble.cpp
game.cpp
game.h
gamemanager.h
gamemanager.cpp
target.h
target.cpp에 관련된거 있음
*/


class Bubble
{
public:
	typedef struct bubble //나중에 몬스터와 충돌을위해 존재하는 데미지존.. target.damageX처럼 변경해두댐, private영역에있으니 아래 get,set함수에서 접근할수있음
	{
		float dx, dy, dz, drx, dry, drz;
	};

	float bubble_x, bubble_y; //큰버블 이동의 위치 
	int pos; //버블 방향.. 아직 AWSD 누르면 버블나감 수정전

	bool m_Life1; //버블 상태 확인1 부딛혔냐 안부딛혔냐
	bool m_Life2; //버블 상태 확인2
	

	float sbubble_x, sbubble_y; //캐릭터위치

	Bubble(); //생성자
	~Bubble(); //소멸자
	bubble m_bubble; //위 private에 선언된 구조체 bubble 충돌값에 접근(m_bubble.dx..이런식)

	DWORD m_BubbleAniTime; //버블재생을 위한 애니메이션
	int m_BubbleCount; //스프라이트 카운트해주는것


	DWORD m_BmAniTime; 
	int m_BmCount; //이것도 스프라이트 카운트해주는거
	DWORD  aniTime2;

	DWORD m_PopAniTime;
	int m_PopCount;


	BOOL BubbleCollision(); //버블과 벽충돌
	RECT bub_rc; //버블의 Rect
	RECT bub_rc2;
	RECT temp;

	void BubblePlayerCol();
	double b_Left; //타겟과 버블의 원형충돌
	double b_High;
	BOOL bubblecol = false; //타겟과 버블원형충돌시 true

	void Init();
	void Update();
	void Draw();
	void move();
	

	void Move(float _x, float _y); //private 에서 은닉된 bubble_x, bubble_y에 접근하는 함수
	void SetPos(int _p); //버블 방향 private 에서 은닉된 pos에 접근하는 함수
	int GetPos();		//버블 방향 private 에서 은닉된 pos에 접근하는 함수

	void Setm_Life1(bool _L); // private 에서 은닉된 버블상태1에 접근하는 함수
	bool Getm_Life1(); // private 에서 은닉된 버블상태1에 접근하는 함수

	void Setm_Life2(bool _L); // private 에서 은닉된 버블상태2에 접근하는 함수
	bool Getm_Life2();// private 에서 은닉된 버블상태2에 접근하는 함수

	float GetX(); //  private 에서 은닉된 버블위치값에 접근하는 함수 
	float GetY();  //  private 에서 은닉된 버블위치값에 접근하는 함수 

	float GetstX(); //private 에서 은닉된 sbubble_x충돌값에 접근하는 함수 
	float GetstY();//private 에서 은닉된 sbubble_y충돌값에 접근하는 함수 

	unsigned __int64 Time;//버블삭제쿨타임을위한 unsigend변수. int가 아닌이유는 자료형이 계속변하는 geticktime을 받을수없기때문..
	unsigned __int64 Time2;//버블삭제쿨타임을위한 unsigend변수
	unsigned __int64 Time3;//버블삭제뒤 pop스프라이트를위한 unsigend변수
};

extern Bubble bubble;