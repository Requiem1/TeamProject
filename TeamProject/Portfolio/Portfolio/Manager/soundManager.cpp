#include "../stdafx.h"
#include "soundManager.h"

soundManager::soundManager()
{
	isBGMOn = true;

	System_Create(&pSystem);

	pSystem->init(TOTALSOUNDBUFFER, FMOD_INIT_NORMAL, 0);

	//ä�ΰ� ����� �����Ҵ�!!
	ppSound = new Sound*[TOTALSOUNDBUFFER];
	ppChannel = new Channel*[TOTALSOUNDBUFFER];

	memset(ppSound, 0, sizeof(Sound*) * (TOTALSOUNDBUFFER));
	memset(ppChannel, 0, sizeof(Channel*) * (TOTALSOUNDBUFFER));
}


soundManager::~soundManager()
{
	SAFE_DELETE_ARRAY(ppSound);
	SAFE_DELETE_ARRAY(ppChannel);
}

void soundManager::Update()
{
	pSystem->update();

	if (!isBGMOn)	ppChannel[BGM_INDEX]->setVolume(0);
	else			ppChannel[BGM_INDEX]->setVolume(1);
}

void soundManager::AddSound(const wchar_t * keyName, string soundName, bool isBgm, bool isLoop)
{
	if (isLoop)
	{
		// createStream�� ã�ƺ���..
		if (isBgm)	pSystem->createStream(soundName.c_str(), FMOD_LOOP_NORMAL, 0, &ppSound[TotalSounds.size()]);
		else		pSystem->createSound(soundName.c_str(), FMOD_LOOP_NORMAL, 0, &ppSound[TotalSounds.size()]);

		wcout << keyName << endl;
		cout << soundName << endl;
	}
	else
	{
		if (isBgm)	pSystem->createStream(soundName.c_str(), FMOD_DEFAULT, 0, &ppSound[TotalSounds.size()]);
		else		pSystem->createSound(soundName.c_str(), FMOD_DEFAULT, 0, &ppSound[TotalSounds.size()]);
	}

	TotalSounds.insert( make_pair(keyName, ppSound[TotalSounds.size()]) );
	printf("AddSound ȣ��!! ���� TotalSound ũ�� : %d\n", TotalSounds.size());
}

void soundManager::Play(const wchar_t * keyName, bool isBgm, float volume)
{
	mapSoundsIter iter;

	int count = 1;
	//cout << "���� Play : ";
	//wcout << keyName;
	//cout << endl;

	// On�� ���ǵ��� ��� Play!
	for (iter = TotalSounds.begin(); iter != TotalSounds.end(); ++iter, count++)
	{
		if (keyName == iter->first)
		{
			if (!isBgm)
			{
				pSystem->playSound(FMOD_CHANNEL_REUSE, iter->second, false, &ppChannel[count]);
				ppChannel[count]->setVolume(volume);
			}

			if (isBgm)
			{
				bool isPlayingBool;
				ppChannel[BGM_INDEX]->isPlaying(&isPlayingBool);

				if (isPlayingBool)
					return;

				pSystem->playSound(FMOD_CHANNEL_REUSE, iter->second, false, &ppChannel[BGM_INDEX]);
				ppChannel[BGM_INDEX]->setVolume(volume);
			}

			break;
		}
	}
}

void soundManager::Stop(bool isBgm, const wchar_t * keyName)
{
	//wcout << L"���� Stop : " << keyName << endl;

	if (isBgm)
	{
		ppChannel[BGM_INDEX]->stop();
		return;
	}

	mapSoundsIter iter = TotalSounds.begin();

	int count = 1;

	for (iter; iter != TotalSounds.end(); ++iter, count++)
	{
		if (keyName == iter->first)
			ppChannel[count]->stop();
	}
}

void soundManager::Pause(bool isBgm, const wchar_t * keyName)
{
	if (isBgm)
	{
		isBGMOn = false;
		return;
	}

	mapSoundsIter iter = TotalSounds.begin();

	int count = 0;

	for (iter; iter != TotalSounds.end(); ++iter, count++)
	{
		if (keyName == iter->first)
		{
			ppChannel[count]->setPaused(true);
			break;
		}
	}
}

void soundManager::Resume(bool isBgm, const wchar_t * keyName)
{
	if (isBgm)
	{
		// get/set playPosition �Լ��� �ʿ���... ���鵵�� ����
		ppChannel[BGM_INDEX]->setPosition(BGM_INDEX, FMOD_TIMEUNIT_MS);
		return;
	}

	mapSoundsIter iter = TotalSounds.begin();

	int count = 0;

	for (iter; iter != TotalSounds.end(); ++iter, count++)
	{
		if (keyName == iter->first)
		{
			ppChannel[count]->setPaused(false);
			break;
		}
	}
}

bool soundManager::IsPlaySound(const wchar_t * keyName, bool isBgm)
{
	bool isPlay;
	mapSoundsIter iter = TotalSounds.begin();

	int count = 1;

	for (iter; iter != TotalSounds.end(); ++iter, count++)
	{
		if (keyName == iter->first)
		{
			if (!isBgm)	ppChannel[count]->isPlaying(&isPlay);
			if (isBgm)	ppChannel[BGM_INDEX]->isPlaying(&isPlay);
			break;
		}
	}

	return isPlay;
}

bool soundManager::IsPauseSound(const wchar_t * keyName, bool isBgm)
{
	bool isPause;
	mapSoundsIter iter = TotalSounds.begin();

	int count = 1;

	for (iter; iter != TotalSounds.end(); ++iter, count++)
	{
		if (keyName == iter->first)
		{
			if (!isBgm)	ppChannel[count]->getPaused(&isPause);
			if (isBgm)	ppChannel[0]->getPaused(&isPause);
			break;
		}
	}
	return false;
}
