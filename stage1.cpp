#include "stdafx.h"
#include "stage1.h"


stage1::stage1()
{
}


stage1::~stage1()
{
}

HRESULT stage1::init()
{
	IMAGEMANAGER->addImage("backGround", "image/map.bmp", 3000, 2240, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("pixel", "image/pixel.bmp", 3000, 2240, true, RGB(255, 0, 255));

	_camera = new camera;
	_camera->init();

	_playerManager = new playerManager;
	_playerManager->init();

	_camera->getPlayerManagerAddressLink(_playerManager);
	_playerManager->getCameraAddressLink(_camera);

	_olaf = new olaf;
	_olaf->init();

	_eric = new eric;
	_eric->init();

	_play = new player3;
	_play->init();

	_choice = 1;

	_isPixel = false;

	return S_OK;
}

void stage1::release()
{
	SAFE_DELETE(_playerManager);
	SAFE_DELETE(_camera);
}

void stage1::update()
{
	//ÇÈ¼¿º¸ÀÌ±â¿ë
	if (KEYMANAGER->isOnceKeyDown(VK_NUMPAD0))
	{
		if (_isPixel)
		{
			_isPixel = false;
		}
		else
		{
			_isPixel = true;
		}
	}

	if (_choice == 1)
	{
		_camera->update(_olaf->getplayerX(), _olaf->getplayerY(), _choice, 10);
	}
	if (_choice == 2)
	{
		_camera->update(_eric->getplayerX(), _eric->getplayerY(), _choice, 10);
	}
	if (_choice == 3)
	{
		_camera->update(_play->getplayerX(), _play->getplayerY(), _choice, 10);
	}

	_playerManager->update();


	_olaf->update(_camera->getCameraPos(), _choice);

	_eric->update(_camera->getCameraPos(), _choice);

	_play->update(_camera->getCameraPos(), _choice);

	if (KEYMANAGER->isOnceKeyDown('1'))
	{
		_choice = 1;
		_camera->setChange(false);
		_camera->setDistance(getDistance(_eric->getplayerX(), _eric->getplayerY(), _olaf->getplayerX(), _olaf->getplayerY()));
		_camera->setAngle(getAngle(_eric->getplayerX(), _eric->getplayerY(), _olaf->getplayerX(), _olaf->getplayerX()));
	}


	if (KEYMANAGER->isOnceKeyDown('2'))
	{
		_choice = 2;
		_camera->setChange(false);
		_camera->setDistance(getDistance(_olaf->getplayerX(), _olaf->getplayerY(), _play->getplayerX(), _play->getplayerY()));
		_camera->setAngle(getAngle(_olaf->getplayerX(), _olaf->getplayerY(), _play->getplayerX(), _play->getplayerX()));
	}

	if (KEYMANAGER->isOnceKeyDown('3'))
	{
		_choice = 3;
		_camera->setChange(false);
		_camera->setDistance(getDistance(_play->getplayerX(), _play->getplayerY(), _eric->getplayerX(), _eric->getplayerY()));
		_camera->setAngle(getAngle(_play->getplayerX(), _play->getplayerY(), _eric->getplayerX(), _eric->getplayerX()));
	}

}

void stage1::render()
{
	IMAGEMANAGER->render("backGround", getMemDC(), 0, 0, _camera->getCameraX() - WINSIZEX / 2, _camera->getCameraY() - WINSIZEY / 2, WINSIZEX, WINSIZEY);
	if (_isPixel)
	{
		IMAGEMANAGER->render("pixel", getMemDC(), 0, 0, _camera->getCameraX() - WINSIZEX / 2, _camera->getCameraY() - WINSIZEY / 2, WINSIZEX, WINSIZEY);
	}
	_playerManager->render();
	_camera->render();
	_olaf->render();
	_eric->render();
	_play->render();
}


