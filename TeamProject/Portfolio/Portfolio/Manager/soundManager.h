#pragma once

// FMOD ���̺귯�� ȣ���
#include "inc/fmod.hpp"
#pragma comment (lib, "fmodex_vc.lib")
using namespace FMOD;

// ���� ����
#define EXTRACHANNELBUFFER 15
#define SOUNDBUFFER 43

#define TOTALSOUNDBUFFER SOUNDBUFFER + EXTRACHANNELBUFFER

#define BGM_INDEX 0

#define g_SoundMgr soundManager::GetInstance()

class soundManager
{
	SINGLETON(soundManager);

private:
	typedef map<const wchar_t*, Sound*> mapSounds;
	typedef map<const wchar_t*, Channel*> arrChannels;

	typedef map<const wchar_t*, Sound*>::iterator mapSoundsIter;
	typedef map<const wchar_t*, Channel*>::iterator arrChannelsIter;

	System* pSystem;
	Sound** ppSound;
	Channel** ppChannel;
	mapSounds TotalSounds;

	bool isBGMOn;

public:
	void Update();

	void AddSound(const wchar_t* keyName, string soundName, bool isBgm, bool isLoop);
	void Play(const wchar_t* keyName, bool isBgm, float volume = 1.0f);				// ���� : 0.0 ~ 1.0(������ �ִ� 255)
	void Stop(bool isBgm, const wchar_t* keyName = L"");

	// ESC �Է½� �Ͻ����� ����� �����Ƿ� Pause �ʿ�
	void Pause(bool isBgm, const wchar_t* keyName);
	void Resume(bool isBgm, const wchar_t* keyName);

	bool IsPlaySound(const wchar_t* keyName, bool isBgm);
	bool IsPauseSound(const wchar_t* keyName, bool isBgm);
};

