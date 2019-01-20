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
	_eric = new eric;
	_eric->init();
	_baleog = new baleog;
	_baleog->init();
	
	for (int i = 0; i < 3; ++i)
	{
		_x[i] = 30 + 120 * i;
		_y[i] = 75;
		_viewX[i] = _x[i];
		_viewY[i] = _y[i];
	}

	for (int i = 0; i < 3; ++i)
	{
		_rc[i] = RectMake(_viewX[i], _viewY[i], 100, 100);
	}

	_isDebug = false;

	for (int i = 0; i < 3; ++i)
	{
		//센터
		_prove_X[i] = (_rc[i].right - _rc[i].left) / 2 + _rc[i].left;
		_prove_Y[i] = _rc[i].bottom;
	}

	_jumpPower = 8.f;
	_gravity = 0.3;
	_isJump = false;
	_jumpNum = 1;
	_choice = 1;

	_camera = new camera;
	_camera->init();

	return S_OK;
}

void playerManager::release()
{
	SAFE_DELETE(_camera);
	SAFE_DELETE(_eric);
	SAFE_DELETE(_baleog);
}

void playerManager::update()
{
	//에릭의 점프
	jumpGravity(_choice);

	//픽셀충돌
	pixelCollisionGreen();
	pixelCollisionYellow();
	pixelCollisionEmerald();
	pixelCollisionRed();
	
	//캐릭터 무브
	characterMove();
	//캐릭터 고르기
	characterChoice();
	//카메라 체인지
	characterChange();
	
	//캐릭터박스 보이기용
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

	//가상좌표 갱신
	for (int i = 0; i < 3; ++i)
	{
		_viewX[i] = _x[i] - _camera->getCameraX();
		_viewY[i] = _y[i] - _camera->getCameraY();
	}

	//갱신
	for (int i = 0; i < 3; ++i)
	{
		_rc[i] = RectMake(_viewX[i], _viewY[i], 100, 100);
		_prove_X[i] = _x[i] + 50;
		_prove_Y[i] = _y[i] + 100;
	}

	if (_choice == 1)
	{
		_eric->update(_viewX[ERIC] - 50, _viewY[ERIC] - 50, &_x[ERIC], &_y[ERIC]);
	}
	else if (_choice == 2)
	{
		_baleog->update(_viewX[BALEOG] + 50, _viewY[BALEOG] + 50, &_x[BALEOG], &_y[BALEOG]);
	}

}

void playerManager::render()
{
	_eric->render(_viewX[ERIC] - 50, _viewY[ERIC] - 50);
	_baleog->render(_viewX[BALEOG] - 50, _viewY[BALEOG] - 50);
	if (_isDebug)
	{
		for (int i = 0; i < 3; ++i)
		{
			Rectangle(getMemDC(), _rc[i]);
		}
	}
	_camera->render();
	//char str[100];
	//sprintf_s(str, "_x : %d", _x[0]);
	//TextOut(getMemDC(), 300, 100, str, strlen(str));

	//sprintf_s(str, "_prove_X : %f", _prove_X[0]);
	//TextOut(getMemDC(), 300, 120, str, strlen(str));
	//
	//sprintf_s(str, "_prove_Y : %f", _prove_Y[0]);
	//TextOut(getMemDC(), 300, 140, str, strlen(str));
	//
	//sprintf_s(str, "중력값 : %f", _gravity);
	//TextOut(getMemDC(), 300, 160, str, strlen(str));
}

void playerManager::characterChoice()
{
	if (_choice == 1)
	{
		_camera->update(_x[ERIC], _y[ERIC]);
	}
	else if (_choice == 2)
	{
		_camera->update(_x[BALEOG], _y[BALEOG]);
	}
	else if (_choice == 3)
	{
		_camera->update(_x[OLAF], _y[OLAF]);
	}
}

void playerManager::characterMove()
{
	if (_camera->getChange() == false)
	{
		if (KEYMANAGER->isStayKeyDown(VK_LEFT) && _baleog->getBaleogState() != BALEOG_LEFT_SWORD_ATTACK_ONE && _baleog->getBaleogState() != BALEOG_LEFT_SWORD_ATTACK_TWO)
		{
			if (_choice == 1)
			{
				_x[ERIC] -= _eric->getSpeed();
			}
			else if (_choice == 2)
			{
				_x[BALEOG] -= _baleog->getSpeed();
			}
			else if (_choice == 3)
			{
				_x[OLAF] -= 5;
			}
		}
		if (KEYMANAGER->isStayKeyDown(VK_RIGHT) && _baleog->getBaleogState() != BALEOG_RIGHT_SWORD_ATTACK_ONE && _baleog->getBaleogState() != BALEOG_RIGHT_SWORD_ATTACK_TWO)
		{
			if (_choice == 1)
			{
				_x[ERIC] += _eric->getSpeed();
			}
			else if (_choice == 2)
			{
				_x[BALEOG] += _baleog->getSpeed();
			
			}
			else if (_choice == 3)
			{
				_x[OLAF] += 5;
			}
		}
		if (KEYMANAGER->isStayKeyDown(VK_UP))
		{
			if (_choice == 1)
			{
				_y[ERIC] -= 5;
			}
			else if (_choice == 2)
			{
				_y[BALEOG] -= 5;
			}
			else if (_choice == 3)
			{
				_y[OLAF] -= 5;
			}
		}
		if (KEYMANAGER->isStayKeyDown(VK_DOWN))
		{
			if (_choice == 1)
			{
				_y[ERIC] += 5;
			}
			else if (_choice == 2)
			{
				_y[BALEOG] += 5;
			}
			else if (_choice == 3)
			{
				_y[OLAF] += 5;
			}
		}
		if (KEYMANAGER->isOnceKeyDown('D'))
		{
			if (_choice == 2)
			{
				_baleog->swordAttack();
				_baleog->setSwordAttack(true);

			}
		}
		else if (KEYMANAGER->isOnceKeyUp('D'))
		{
			_baleog->setSwordAttack(false);
		}

		
	}
}

void playerManager::characterChange()
{
	if (KEYMANAGER->isOnceKeyDown('Q'))
	{
		if (_choice == 1)
		{
			_choice = 2;
			_camera->cameraChange(_x[BALEOG], _y[BALEOG]);
		}
		else if (_choice == 2)
		{
			_choice = 3;
			_camera->cameraChange(_x[OLAF], _y[OLAF]);
		}
		else if (_choice == 3)
		{
			_choice = 1;
			_camera->cameraChange(_x[ERIC], _y[ERIC]);
		}
	}
}

void playerManager::pixelCollisionGreen()
{
	//위로 올라서게
	if (!_isJump)
	{
		//if (select == 1)
		{
			//에릭
			for (int i = _prove_Y[ERIC] - 10; i < _prove_Y[ERIC] + 10; ++i)
			{
				COLORREF color = GetPixel(IMAGEMANAGER->findImage("pixel")->getMemDC(), _prove_X[ERIC], i);

				int r = GetRValue(color);
				int g = GetGValue(color);
				int b = GetBValue(color);

				if (r == 0 && g == 255 && b == 0)
				{
					_y[ERIC] = i - 100;
					_jumpNum = 1;

					break;
				}
			}
		}
		//else if (select == 2)
		{
			//벨로그
			for (int i = _prove_Y[BALEOG] - 10; i < _prove_Y[BALEOG] + 10; ++i)
			{
				COLORREF color = GetPixel(IMAGEMANAGER->findImage("pixel")->getMemDC(), _prove_X[BALEOG], i);

				int r = GetRValue(color);
				int g = GetGValue(color);
				int b = GetBValue(color);

				if (r == 0 && g == 255 && b == 0)
				{
					_y[BALEOG] = i - 100;

					break;
				}
			}
		}
		//else if (select == 3)
		{
			//올라프
			for (int i = _prove_Y[OLAF] - 10; i < _prove_Y[OLAF] + 10; ++i)
			{
				COLORREF color = GetPixel(IMAGEMANAGER->findImage("pixel")->getMemDC(), _prove_X[OLAF], i);

				int r = GetRValue(color);
				int g = GetGValue(color);
				int b = GetBValue(color);

				if (r == 0 && g == 255 && b == 0)
				{
					_y[OLAF] = i - 100;

					break;
				}
			}
		}
	}
}

void playerManager::pixelCollisionYellow()
{
	//왼쪽벽
	//if (select == 1)
	{
		//에릭
		for (int i = _prove_X[ERIC] - 40; i > _prove_X[ERIC] - 50; --i)
		{
			COLORREF color = GetPixel(IMAGEMANAGER->findImage("pixel")->getMemDC(), i, _prove_Y[ERIC] - 50);

			int r = GetRValue(color);
			int g = GetGValue(color);
			int b = GetBValue(color);

			if (r == 255 && g == 255 && b == 0)
			{
				_x[ERIC] = i;

				break;
			}
		}
	}
	//else if (select == 2)
	{
		//벨로그
		for (int i = _prove_X[BALEOG] - 40; i > _prove_X[BALEOG] - 50; --i)
		{
			COLORREF color = GetPixel(IMAGEMANAGER->findImage("pixel")->getMemDC(), i, _prove_Y[BALEOG] - 50);

			int r = GetRValue(color);
			int g = GetGValue(color);
			int b = GetBValue(color);

			if (r == 255 && g == 255 && b == 0)
			{
				_x[BALEOG] = i;

				break;
			}
		}
	}
	//else if (select == 3)
	{
		//올라프
		for (int i = _prove_X[OLAF] - 40; i > _prove_X[OLAF] - 50; --i)
		{
			COLORREF color = GetPixel(IMAGEMANAGER->findImage("pixel")->getMemDC(), i, _prove_Y[OLAF] - 50);

			int r = GetRValue(color);
			int g = GetGValue(color);
			int b = GetBValue(color);

			if (r == 255 && g == 255 && b == 0)
			{
				_x[OLAF] = i;

				break;
			}
		}
	}
}

void playerManager::pixelCollisionEmerald()
{
	//오른쪽벽
	//if (select == 1)
	{
		//에릭
		for (int i = _prove_X[ERIC] + 45; i < _prove_X[ERIC] + 50; ++i)
		{
			COLORREF color = GetPixel(IMAGEMANAGER->findImage("pixel")->getMemDC(), i, _prove_Y[ERIC] - 50);

			int r = GetRValue(color);
			int g = GetGValue(color);
			int b = GetBValue(color);

			if (r == 0 && g == 255 && b == 255)
			{
				_x[ERIC] = i - 100;

				break;
			}
		}
	}
	//else if (select == 2)
	{
		//벨로그
		for (int i = _prove_X[BALEOG] + 45; i < _prove_X[BALEOG] + 50; ++i)
		{
			COLORREF color = GetPixel(IMAGEMANAGER->findImage("pixel")->getMemDC(), i, _prove_Y[BALEOG] - 50);

			int r = GetRValue(color);
			int g = GetGValue(color);
			int b = GetBValue(color);

			if (r == 0 && g == 255 && b == 255)
			{
				_x[BALEOG] = i - 100;

				break;
			}
		}
	}
	//else if (select == 3)
	{
		//올라프
		for (int i = _prove_X[OLAF] + 45; i < _prove_X[OLAF] + 50; ++i)
		{
			COLORREF color = GetPixel(IMAGEMANAGER->findImage("pixel")->getMemDC(), i, _prove_Y[OLAF] - 50);

			int r = GetRValue(color);
			int g = GetGValue(color);
			int b = GetBValue(color);

			if (r == 0 && g == 255 && b == 255)
			{
				_x[OLAF] = i - 100;

				break;
			}
		}
	}
}

void playerManager::pixelCollisionRed()
{
	for (int i = _prove_Y[ERIC] - 95; i > _prove_Y[ERIC] - 100; i--)
	{
		COLORREF color = GetPixel(IMAGEMANAGER->findImage("pixel")->getMemDC(), _prove_X[ERIC], i);

		int r = GetRValue(color);
		int g = GetGValue(color);
		int b = GetBValue(color);
	
		if (r == 255 && g == 0 && b == 0)
		{
			_y[ERIC] = i;
			_y[ERIC] += 5.0f;
			_isJump = false;
		}
	}
}

void playerManager::jumpGravity(int select)
{
	for (int i = 0; i < 3; ++i)
	{
		if (_isJump)
		{
			_jumpCount++;
			_y[select - 1] -= _jumpPower;
			_jumpPower -= _gravity;

			if (_jumpCount > 50)
			{
				_isJump = false;
			}
		}
		else
		{
			_y[i] += 7.f;
			_jumpCount = 0;
		}
		if (select == 1)
		{
			if (_jumpNum > 0)
			{
				if (KEYMANAGER->isOnceKeyDown('F') && _camera->getChange() == false)
				{
					_jumpNum--;
					_jumpPower = 6.f;
					_gravity = 0.05f;
					_isJump = true;

					_eric->jumpKeySetting();
				}
			}
		}
	}
}
