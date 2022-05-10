#pragma once

class Sound
{
	
public:
	Sound(void);
	~Sound(void);

	
CSoundManager* g_pSoundManager;
CSound*		m_Bk1;
CSound*		m_Shot;
CSound*		m_Jump;
CSound*     m_death;
CSound*     m_col;
CSound*		m_bb;

int m_Select;

	

	void Init();
	
	
};

extern Sound sound;