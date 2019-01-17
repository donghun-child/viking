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
		_camera->update(_playerManager->getEricX(), _playerManager->getEricY(), _choice, 10);
	}
	if (_choice == 2)
	{
		_camera->update(_playerManager->getBalogX(), _playerManager->getBalogY(), _choice, 10);
	}
	if (_choice == 3)
	{
		_camera->update(_playerManager->getOlafX(), _playerManager->getOlafY(), _choice, 10);
	}

	_playerManager->update();


	if (KEYMANAGER->isOnceKeyDown('1'))
	{
		_choice = 1;
		_camera->setChange(false);
		_camera->setDistance(getDistance(_playerManager->getEricX(), _playerManager->getEricY(), _playerManager->getBalogX(), _playerManager->getBalogY()));
		_camera->setAngle(getAngle(_playerManager->getEricX(), _playerManager->getEricY(), _playerManager->getBalogX(), _playerManager->getBalogY()));
	}


	if (KEYMANAGER->isOnceKeyDown('2'))
	{
		_choice = 2;
		_camera->setChange(false);
		_camera->setDistance(getDistance(_playerManager->getBalogX(),_playerManager->getBalogY(),_playerManager->getOlafX(),_playerManager->getOlafY()));
		_camera->setAngle(getAngle(_playerManager->getBalogX(), _playerManager->getBalogY(), _playerManager->getOlafX(), _playerManager->getOlafY()));
	}

	if (KEYMANAGER->isOnceKeyDown('3'))
	{
		_choice = 3;
		_camera->setChange(false);
		_camera->setDistance(getDistance(_playerManager->getOlafX(),_playerManager->getOlafY(),_playerManager->getEricX(),_playerManager->getEricY()));
		_camera->setAngle(getAngle(_playerManager->getOlafX(), _playerManager->getOlafY(), _playerManager->getEricX(), _playerManager->getEricY()));
	}

}

void stage1::render()
{
	IMAGEMANAGER->render("backGround", getMemDC(), 0, 0, _camera->getCameraX(), _camera->getCameraY(), WINSIZEX, WINSIZEY);
	if (_isPixel)
	{
		IMAGEMANAGER->render("pixel", getMemDC(), 0, 0, _camera->getCameraX(), _camera->getCameraY(), WINSIZEX, WINSIZEY);
	}
	_playerManager->render();
	_camera->render();
	
}


