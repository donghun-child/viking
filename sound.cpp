#include "stdafx.h"
#include "sound.h"


sound::sound()
{
}


sound::~sound()
{
}

HRESULT sound::init()
{
	SOUNDMANAGER->addSound("baleog", "sound/baleog.mp3", false, false);
	SOUNDMANAGER->addSound("baleog_2", "sound/baleog_2.mp3", false, false);
	SOUNDMANAGER->addSound("baleog_3", "sound/baleog_3.mp3", false, false);
	SOUNDMANAGER->addSound("baleog_4", "sound/baleog_4.mp3", false, false);
	SOUNDMANAGER->addSound("baleog_5", "sound/baleog_5.mp3", false, false);
	SOUNDMANAGER->addSound("baleog_Arrow", "sound/baleog_Arrow.mp3", false, false);
	SOUNDMANAGER->addSound("baleog_ArrowPull", "sound/baleog_ArrowPull.mp3", false, false);
	SOUNDMANAGER->addSound("baleog_Attack", "sound/baleog_Attack.mp3", false, false);
	SOUNDMANAGER->addSound("baleog_Attack2", "sound/baleog_Attack2.mp3", false, false);
	SOUNDMANAGER->addSound("eric", "sound/eric.mp3", false, false);
	
	
	return S_OK;
}

void sound::release()
{
}

void sound::update()
{
}

void sound::render()
{
}
