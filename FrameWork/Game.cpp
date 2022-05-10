#include "Include.h"

Game::Game()
{
}

Game::~Game()
{
}

void Game::Init()
{
	map.Init();
	target.Init();
	monster1.Init();
	monster2.Init();
	monster3.Init();
	ghost1.Init();

	sound.Init();
	Gmanager.Init();
	
	//ghost2.Init();

	// 데이타 베이스///////////////////
	//sql.Init();
}

void Game::Draw()
{
	map.Draw();
	monster1.Draw(monster1.m_nowX, monster1.m_nowY);
	monster2.Draw(monster2.m_nowX, monster2.m_nowY);
	monster3.Draw(monster3.m_nowX, monster3.m_nowY);
	target.Draw();
	ghost1.Draw(ghost1.g_nowX, ghost1.g_nowY);

	Gmanager.Draw();
	//ghost2.Draw(ghost2.g_nowX, ghost2.g_nowY);

	// 데이타 베이스///////////////////
	//sql.Draw();

	//이터레이터를 그려줘야함
	if (target.GetBubble()->size() != 0)
	{
		for (auto iter = target.GetBubble()->begin(); iter != target.GetBubble()->end(); ++iter) {

			iter->Draw();
		}
	}
}

// Chap, 재정의 함수 호출
void Game::Update(double frame)
{
	//static int a = 0;
	//if(a == 0) 
	//{
	//	GameTime = GetTickCount();
	//	a = 1;
	//}
	static DWORD a = 0;

	if (GetTickCount64() - a > frame)
	{
		key.Update();
		target.Update();
		ghost1.Update();
		monster1.Update();
		monster2.Update();
		monster3.Update();

		// 입 맛에 맞게
		map.Update(130);
		Gmanager.Update();
	
		// 데이타 베이스///////////////////
		// 입 맛에 맞게 (여기선 안쓰임..프레임 값이 필요 할때만.. 그냥 방법만...)
		//sql.Update(frame+3000);


		//이터레이터를 업데이트해줘야함.
		if (target.GetBubble()->size() != 0)
		{
			for (auto iter = target.GetBubble()->begin(); iter != target.GetBubble()->end(); ++iter) 
			{
				iter->Update();
			}
		}

		a = GetTickCount64();
	}


}

void Game::OnMessage(MSG* msg)
{

}