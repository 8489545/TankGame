#include "stdafx.h"
#include "SoundMgr.h"


SoundMgr::SoundMgr()
{
}


SoundMgr::~SoundMgr()
{
}

void SoundMgr::Play(const WCHAR* pFileName, bool loop)
{
	WCHAR szFullPath[256] = L"../Sound/";
	lstrcatW(szFullPath, pFileName);

	if (!loop)
	{
		sndPlaySoundW(szFullPath, SND_ASYNC | SND_NOSTOP);
	}
	else if (loop)
	{
		sndPlaySoundW(szFullPath, SND_ASYNC | SND_LOOP | SND_NOSTOP);
	}
}

void SoundMgr::Stop()
{
	sndPlaySoundW(nullptr, SND_ASYNC);
}