#include "Include.h"

Sound sound;



Sound::Sound(void)
{
	//g_pSoundManager = NULL; 사용 안했다
}

Sound::~Sound(void)
{
}

void Sound::Init()
{
	g_pSoundManager->Create( &m_Bk1, (LPWSTR)L"./resource/Sound/BGM_0001.wav", 0, GUID_NULL ) ;
	g_pSoundManager->Create( &m_Shot, (LPWSTR)L"./resource/Sound/shot.wav", 0, GUID_NULL ) ;
	g_pSoundManager->Create( &m_Jump, (LPWSTR)L"./resource/Sound/Jump.wav", 0, GUID_NULL);
	g_pSoundManager->Create( &m_death, (LPWSTR)L"./resource/Sound/death.wav", 0, GUID_NULL);
	g_pSoundManager->Create( &m_col, (LPWSTR)L"./resource/Sound/col.wav", 0, GUID_NULL);
	g_pSoundManager->Create(&m_bb, (LPWSTR)L"./resource/Sound/bb.wav", 0, GUID_NULL);
}

