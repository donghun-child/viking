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
	_changing = false;

	_time = CAMERA_CHANGING_SPEED;


	return S_OK;
}

void stage1::release()
{
	SAFE_DELETE(_playerManager);
	SAFE_DELETE(_camera);
}

void stage1::update()
{
	_playerManager->update();
	//픽셀 보이게하는 함수
	viewPixel();
	//캐릭터 중력
	_playerManager->gravity(_choice);
	//캐릭터 선택
	characterChoice();
	//캐릭터 무브
	characterMove();
	//캐릭터 체인지
	characterChange();
	//카메라 체인지
	changeMoving();
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

	//char str[100];
	//sprintf_s(str, "플레이어 x : %f", _playerManager->getEricX());
	//TextOut(getMemDC(), 300, 20, str, strlen(str));
	//sprintf_s(str, "플레이어 y : %f", _playerManager->getEricY());
	//TextOut(getMemDC(), 300, 40, str, strlen(str));
	//sprintf_s(str, "초이스 : %d", _choice);
	//TextOut(getMemDC(), 300, 60, str, strlen(str));
}

void stage1::viewPixel()
{
	//픽셀보이기용
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
}

void stage1::characterChoice()
{
	if (_choice == 1)
	{
		_camera->update(_playerManager->getEricX(), _playerManager->getEricY());
		_playerManager->pixelCollisionGreen();
		_playerManager->pixelCollisionYellow();
		_playerManager->pixelCollisionEmerald();
		_playerManager->pixelCollisionRed();
	}
	if (_choice == 2)
	{
		_camera->update(_playerManager->getBalogX(), _playerManager->getBalogY());
		_playerManager->pixelCollisionGreen();
		_playerManager->pixelCollisionYellow();
		_playerManager->pixelCollisionEmerald();
	}
	if (_choice == 3)
	{
		_camera->update(_playerManager->getOlafX(), _playerManager->getOlafY());
		_playerManager->pixelCollisionGreen();
		_playerManager->pixelCollisionYellow();
		_playerManager->pixelCollisionEmerald();
	}
}

void stage1::characterMove()
{
	if (!_changing)
	{
		if (KEYMANAGER->isStayKeyDown(VK_LEFT))
		{
			if (_choice == 1)
			{
				_playerManager->setEricX(_playerManager->getEricX() - 5);
			}
			if (_choice == 2)
			{
				_playerManager->setBalogX(_playerManager->getBalogX() - 5);
			}
			if (_choice == 3)
			{
				_playerManager->setOlafX(_playerManager->getOlafX() - 5);
			}
		}
		if (KEYMANAGER->isStayKeyDown(VK_RIGHT))
		{
			if (_choice == 1)
			{
				_playerManager->setEricX(_playerManager->getEricX() + 5);
			}
			if (_choice == 2)
			{
				_playerManager->setBalogX(_playerManager->getBalogX() + 5);
			}
			if (_choice == 3)
			{
				_playerManager->setOlafX(_playerManager->getOlafX() + 5);
			}

		}
		if (KEYMANAGER->isStayKeyDown(VK_UP))
		{
			if (_choice == 1)
			{
				_playerManager->setEricY(_playerManager->getEricY() - 5);
			}
			if (_choice == 2)
			{
				_playerManager->setBalogY(_playerManager->getBalogY() - 5);
			}
			if (_choice == 3)
			{
				_playerManager->setOlafY(_playerManager->getOlafY() - 5);
			}
		}
		if (KEYMANAGER->isStayKeyDown(VK_DOWN))
		{
			if (_choice == 1)
			{
				_playerManager->setEricY(_playerManager->getEricY() + 5);
			}
			if (_choice == 2)
			{
				_playerManager->setBalogY(_playerManager->getBalogY() + 5);
			}
			if (_choice == 3)
			{
				_playerManager->setOlafY(_playerManager->getOlafY() + 5);
			}
		}
	}
}

void stage1::characterChange()
{
	if (KEYMANAGER->isOnceKeyDown('Q'))
	{
		if (_choice == 1)
		{
			_changing = true;
			_choice = 2;
			cameraChange(_playerManager->getEricX(), _playerManager->getEricY(), _playerManager->getBalogX(), _playerManager->getBalogY());
		}
		else if (_choice == 2)
		{
			_changing = true;
			_choice = 3;
			cameraChange(_playerManager->getBalogX(), _playerManager->getBalogY(), _playerManager->getOlafX(), _playerManager->getOlafY());

		}
		else if (_choice == 3)
		{
			_changing = true;
			_choice = 1;
			cameraChange(_playerManager->getOlafX(), _playerManager->getOlafY(), _playerManager->getEricX(), _playerManager->getEricY());
		}
	}
}

void stage1::cameraChange(float orizinX, float orizinY, float newX, float newY)
{
	_orizin.x = orizinX;
	_orizin.y = orizinY;
	_new.x = newX;
	_new.y = newY;

	_camera->setChange(true);
	_orizin = cameraPos(orizinX, orizinY);
	_new = cameraPos(newX, newY);
	_orizin.x = _camera->getCameraX();
	_orizin.y = _camera->getCameraY();

	_Distance = getDistance(_orizin.x, _orizin.y, _new.x, _new.y);
	_angle = getAngle(_orizin.x, _orizin.y, _new.x, _new.y);
	_worldTime = TIMEMANAGER->getWorldTime();
	_time = CAMERA_CHANGING_SPEED;
}

POINTFLOAT stage1::cameraPos(float x, float y)
{
	//카메라의 현재 좌표를 포인트로 뱉어내는 함수
	POINTFLOAT _point;

	//4모서리에 있을때
	if (x < WINSIZEX / 2 && y < WINSIZEY / 2)
	{
		//x = 0;
		//y = 0;
		_point.x = 0;
		_point.y = 0;

		return _point;
	}
	else if (x > 3000 - WINSIZEX / 2 && y < WINSIZEY / 2)
	{
		_point.x = 3000 - WINSIZEX;
		_point.y = 0;

		return _point;
	}
	else if (x < WINSIZEX / 2 && y > 2240 - WINSIZEY / 2)
	{
		_point.x = 0;
		_point.y = 2240 - WINSIZEY;

		return _point;
	}
	else if (x > 3000 - WINSIZEX / 2 && y > 2240 - WINSIZEY / 2)
	{
		_point.x = 3000 - WINSIZEX;
		_point.y = 2240 - WINSIZEY;

		return _point;
	}
	//x좌표예외처리
	else if (x < WINSIZEX / 2)
	{
		_point.x = 0;
		_point.y = y - WINSIZEY / 2;

		return _point;
	}
	else if (x > 3000 - WINSIZEX / 2)
	{
		_point.x = 3000 - WINSIZEX;
		_point.y = y - WINSIZEY / 2;

		return _point;
	}
	//y좌표예외처리
	else if (y < WINSIZEY / 2)
	{
		_point.x = x - WINSIZEX / 2;
		_point.y = 0;

		return _point;
	}
	else if (y > 2240 - WINSIZEY / 2)
	{
		_point.x = x - WINSIZEX / 2;
		_point.y = 2240 - WINSIZEY;

		return _point;
	}
	//기본상태
	else
	{
		_point.x = x - WINSIZEX / 2;
		_point.y = y - WINSIZEY / 2;

		return _point;
	}
}

void stage1::changeMoving()
{
	if (_camera->getChange() == false) return;

	elapsedTime = TIMEMANAGER->getElpasedTime();

	moveSpeed = (elapsedTime / _time) * _Distance;;

	if (moveSpeed != 0)
	{
		_camera->setCameraX(_camera->getCameraX() + cosf(_angle) * moveSpeed);
		_camera->setCameraY(_camera->getCameraY() + -sinf(_angle) * moveSpeed);
	}

	if (_time + _worldTime <= TIMEMANAGER->getWorldTime() || moveSpeed == 0)
	{
		_worldTime = TIMEMANAGER->getWorldTime();

		_camera->setCameraX(_new.x);
		_camera->setCameraY(_new.y);

		_camera->setChange(false);
		_changing = false;
	}
}


