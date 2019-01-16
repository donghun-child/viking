#include "stdafx.h"
#include "playerManager.h"


playerManager::playerManager()
{
}


playerManager::~playerManager()
{
}

HRESULT playerManager::init()
{
	_rc[BALEOG] = RectMake(30, 30, 150, 150);
	_rc[ERIC] = RectMake(130, 30, 157, 157);
	_rc[OLAF] = RectMake(250, 30, 160, 160);

	_isDebug = false;


	return S_OK;
}

void playerManager::release()
{
}

void playerManager::update()
{
	if (KEYMANAGER->isOnceKeyDown(VK_NUMPAD1))
	{
		if (_isDebug)
		{
			_isDebug = false;
		}
		else
		{
			_isDebug = true;
		}
	}


}

void playerManager::render()
{
	if (_isDebug)
	{
		for (int i = 0; i < 3; ++i)
		{
			Rectangle(getMemDC(), _rc[i]);
		}
	}
}
