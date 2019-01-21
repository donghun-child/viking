#include "stdafx.h"
#include "playerManager.h"
#include "item.h"

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
	_olaf = new olaf;
	_olaf->init();

	//���α� ȭ��κ�
	IMAGEMANAGER->addFrameImage("ȭ��", "image/bullet.bmp", 85, 20, 5, 2, true, RGB(255, 0, 255));
	_arrow = new arrow;
	_arrow->init("ȭ��", 0, 600);
	_isArrowFireStop = false;

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
		//����
		_prove_X[i] = (_rc[i].right - _rc[i].left) / 2 + _rc[i].left;
		_prove_Y[i] = _rc[i].bottom;
	}

	_camerc_x = 100;
	_camerc_y = 100;
	_cameview_x = _camerc_x;
	_cameview_y = _camerc_y;

	_camerc = RectMake(_cameview_x, _cameview_y, 50, 50);

	_jumpPower = 8.f;
	_gravity = 0.3;
	_isJump = false;
	_jumpNum = 1;
	_choice = ERIC;

	_camera = new camera;
	_camera->init();

	return S_OK;
}

void playerManager::release()
{
	SAFE_DELETE(_camera);
	SAFE_DELETE(_eric);
	SAFE_DELETE(_baleog);
	SAFE_DELETE(_olaf);
	SAFE_DELETE(_arrow);
}

void playerManager::update()
{
	//���α� ȭ��
	_arrow->update();
	for (int i = 0; i < _arrow->getVArrow().size(); i++)
	{
		(*_arrow->getVArrowAddress())[i].viewX = (*_arrow->getVArrowAddress())[i].x - _camera->getCameraX();
		(*_arrow->getVArrowAddress())[i].viewY = (*_arrow->getVArrowAddress())[i].y - _camera->getCameraY();
	}

	//������ ����
	jumpGravity(_choice);

	//�ȼ��浹
	pixelCollisionGreen();
	pixelCollisionYellow();
	pixelCollisionEmerald();
	pixelCollisionRed();
	
	//ĳ���� ����
	characterMove();
	//ĳ���� ����
	characterChoice();
	//ī�޶� ü����
	characterChange();
	
	//ĳ���͹ڽ� ���̱��
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

	//������ǥ ����
	for (int i = 0; i < 3; ++i)
	{
		_viewX[i] = _x[i] - _camera->getCameraX();
		_viewY[i] = _y[i] - _camera->getCameraY();
	}

	//����
	for (int i = 0; i < 3; ++i)
	{
		_rc[i] = RectMake(_viewX[i], _viewY[i], 100, 100);
		_prove_X[i] = _x[i] + 50;
		_prove_Y[i] = _y[i] + 100;
	}

	if (_choice == ERIC)
	{
		_eric->update(_viewX[ERIC] - 40, _viewY[ERIC] - 60, &_x[ERIC], &_y[ERIC]);
	}
	else if (_choice == BALEOG)
	{
		_baleog->update(_viewX[BALEOG] + 50, _viewY[BALEOG] + 50, &_x[BALEOG], &_y[BALEOG]);
	}

	else if(_choice == OLAF)
	{
		_olaf->update(_viewX[OLAF] + 50, _viewY[OLAF] + 50, &_x[OLAF], &_y[OLAF]);
	}

	_cameview_x = _camerc_x - _camera->getCameraX();
	_cameview_y = _camerc_y - _camera->getCameraY();

	_camerc = RectMake(_cameview_x, _cameview_y, 50, 50);

	if (KEYMANAGER->isStayKeyDown('L'))
	{
		_camerc_x += 15;
	}
	if (KEYMANAGER->isStayKeyDown('J'))
	{
		_camerc_x -= 15;
	}
	if (KEYMANAGER->isStayKeyDown('K'))
	{
		_camerc_y += 15;
	}
	if (KEYMANAGER->isStayKeyDown('I'))
	{
		_camerc_y -= 15;
	}

}

void playerManager::render()
{
	_eric->render(_viewX[ERIC] - 40, _viewY[ERIC] - 60);
	_baleog->render(_viewX[BALEOG] - 40, _viewY[BALEOG] - 50);
	_olaf->render(_viewX[OLAF] - 50, _viewY[OLAF] - 50);

	for (int i = 0; i < _arrow->getVArrow().size(); i++)
	{
		_arrow->render((*_arrow->getVArrowAddress())[i].viewX, (*_arrow->getVArrowAddress())[i].viewY);
	}

	if (_isDebug)
	{
		for (int i = 0; i < 3; ++i)
		{
			Rectangle(getMemDC(), _rc[i]);
		}
	}

	//Rectangle(getMemDC(), _camerc);
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
	//sprintf_s(str, "�߷°� : %f", _gravity);
	//TextOut(getMemDC(), 300, 160, str, strlen(str));
}

void playerManager::characterChoice()
{
	if (_choice == ERIC)
	{
		_camera->update(_x[ERIC], _y[ERIC]);
		
	}
	else if (_choice == BALEOG)
	{
		_camera->update(_x[BALEOG], _y[BALEOG]);
	}
	else if (_choice == OLAF)
	{
		_camera->update(_x[OLAF], _y[OLAF]);
	}

	_camera->update(_camerc_x, _camerc_y);
}

void playerManager::characterMove()
{
	if (_camera->getChange() == false)
	{
		if (KEYMANAGER->isStayKeyDown(VK_LEFT) && _baleog->getBaleogState() != BALEOG_LEFT_SWORD_ATTACK_ONE && _baleog->getBaleogState() != BALEOG_LEFT_SWORD_ATTACK_TWO && _baleog->getBaleogState() != BALEOG_RIGHT_SWORD_ATTACK_ONE && _baleog->getBaleogState() != BALEOG_RIGHT_SWORD_ATTACK_TWO && _baleog->getBaleogState() != BALEOG_LEFT_ARROW_ATTACK && _baleog->getBaleogState() != BALEOG_RIGHT_ARROW_ATTACK)
		{
			if (_choice == ERIC)
			{
				_x[ERIC] -= _eric->getSpeed();
			}
			else if (_choice == BALEOG)
			{
				_x[BALEOG] -= _baleog->getSpeed();
			}
			else if (_choice == OLAF)
			{
				_x[OLAF] -= _olaf->getSpeed();
			}
		}
		if (KEYMANAGER->isStayKeyDown(VK_RIGHT) && _baleog->getBaleogState() != BALEOG_RIGHT_SWORD_ATTACK_ONE && _baleog->getBaleogState() != BALEOG_RIGHT_SWORD_ATTACK_TWO && _baleog->getBaleogState() != BALEOG_LEFT_SWORD_ATTACK_ONE && _baleog->getBaleogState() != BALEOG_LEFT_SWORD_ATTACK_TWO && _baleog->getBaleogState() != BALEOG_RIGHT_ARROW_ATTACK && _baleog->getBaleogState() != BALEOG_LEFT_ARROW_ATTACK)
		{
			if (_choice == ERIC)
			{
				_x[ERIC] += _eric->getSpeed();
			}
			else if (_choice == BALEOG)
			{
				_x[BALEOG] += _baleog->getSpeed();
			
			}
			else if (_choice == OLAF)
			{
				_x[OLAF] += _olaf->getSpeed();
			}
		}
		if (KEYMANAGER->isStayKeyDown(VK_UP))
		{
			if (_choice == ERIC)
			{
				_y[ERIC] -= 5;
			}
			else if (_choice == BALEOG)
			{
				_y[BALEOG] -= 5;
			}
			else if (_choice == OLAF)
			{
				_y[OLAF] -= 5;
			}
		}
		if (KEYMANAGER->isStayKeyDown(VK_DOWN))
		{
			if (_choice == ERIC)
			{
				_y[ERIC] += 5;
			}
			else if (_choice == BALEOG)
			{
				_y[BALEOG] += 5;
			}
			else if (_choice == OLAF)
			{
				_y[OLAF] += 5;
			}
		}
		//���α� ȭ���ºκ�
		if (_choice == BALEOG)
		{
			baleogArrow();
		}
	}
	//ī�޶� ü���� �����̸� �ٸ��ֵ� �������� ���߰���.
	else if (_camera->getChange() == true)
	{
		if (_choice == ERIC)
		{
			if (_baleog->getBaleogState() == BALEOG_RIGHT_MOVE)
			{
				_baleog->setBaleogState(BALEOG_RIGHT_STOP);
				_baleog->setBaleogMotion(KEYANIMANAGER->findAnimation("���α�ĳ����", "rightStop"));
				_baleog->getBaleogMotion()->start();
			}
			else if (_baleog->getBaleogState() == BALEOG_LEFT_MOVE)
			{
				_baleog->setBaleogState(BALEOG_LEFT_STOP);
				_baleog->setBaleogMotion(KEYANIMANAGER->findAnimation("���α�ĳ����", "leftStop"));
				_baleog->getBaleogMotion()->start();
			}
			if (_olaf->getOlafDirection() == OLAF_DIRECTION_RIGHT_MOVE)
			{
				_olaf->setOlafDirection(OLAF_DIRECTION_RIGHT_STOP);
				_olaf->setOlafMotion(KEYANIMANAGER->findAnimation("olafName", "olafRightStop"));
				_olaf->getOlafMotion()->start();
			}
			else if (_olaf->getOlafDirection() == OLAF_DIRECTION_LEFT_MOVE)
			{
				_olaf->setOlafDirection(OLAF_DIRECTION_LEFT_STOP);
				_olaf->setOlafMotion(KEYANIMANAGER->findAnimation("olafName", "olafLeftStop"));
				_olaf->getOlafMotion()->start();
			}
		}
		else if (_choice == BALEOG)
		{
			if (_eric->getEricState() == ERIC_RIGHT_MOVE)
			{
				_eric->setEricState(ERIC_RIGHT_STOP);
				_eric->setEricMotion(KEYANIMANAGER->findAnimation("ericName", "rightStop"));
				_eric->getEricMotion()->start();
			}
			else if (_eric->getEricState() == ERIC_LEFT_MOVE)
			{
				_eric->setEricState(ERIC_LEFT_STOP);
				_eric->setEricMotion(KEYANIMANAGER->findAnimation("ericName", "leftStop"));
				_eric->getEricMotion()->start();
			}
			if (_olaf->getOlafDirection() == OLAF_DIRECTION_RIGHT_MOVE)
			{
				_olaf->setOlafDirection(OLAF_DIRECTION_RIGHT_STOP);
				_olaf->setOlafMotion(KEYANIMANAGER->findAnimation("olafName", "olafRightStop"));
				_olaf->getOlafMotion()->start();
			}
			else if (_olaf->getOlafDirection() == OLAF_DIRECTION_LEFT_MOVE)
			{
				_olaf->setOlafDirection(OLAF_DIRECTION_LEFT_STOP);
				_olaf->setOlafMotion(KEYANIMANAGER->findAnimation("olafName", "olafLeftStop"));
				_olaf->getOlafMotion()->start();
			}
		}
		else if (_choice == OLAF)
		{
			if (_eric->getEricState() == ERIC_RIGHT_MOVE)
			{
				_eric->setEricState(ERIC_RIGHT_STOP);
				_eric->setEricMotion(KEYANIMANAGER->findAnimation("ericName", "rightStop"));
				_eric->getEricMotion()->start();
			}
			else if (_eric->getEricState() == ERIC_LEFT_MOVE)
			{
				_eric->setEricState(ERIC_LEFT_STOP);
				_eric->setEricMotion(KEYANIMANAGER->findAnimation("ericName", "leftStop"));
				_eric->getEricMotion()->start();
			}
			if (_baleog->getBaleogState() == BALEOG_RIGHT_MOVE)
			{
				_baleog->setBaleogState(BALEOG_RIGHT_STOP);
				_baleog->setBaleogMotion(KEYANIMANAGER->findAnimation("���α�ĳ����", "rightStop"));
				_baleog->getBaleogMotion()->start();
			}
			else if (_baleog->getBaleogState() == BALEOG_LEFT_MOVE)
			{
				_baleog->setBaleogState(BALEOG_LEFT_STOP);
				_baleog->setBaleogMotion(KEYANIMANAGER->findAnimation("���α�ĳ����", "leftStop"));
				_baleog->getBaleogMotion()->start();
			}
		}
	}
}

void playerManager::characterChange()
{
	if (KEYMANAGER->isOnceKeyDown('Q'))
	{
		if (_choice == ERIC)
		{
			_choice = BALEOG;
			_camera->cameraChange(_x[BALEOG], _y[BALEOG]);
			SOUNDMANAGER->play("UI_EricPic");
		}
		else if (_choice == BALEOG)
		{
			_choice = OLAF;
			_camera->cameraChange(_x[OLAF], _y[OLAF]);
			SOUNDMANAGER->play("UI_BaleogPic");
		}
		else if (_choice == OLAF)
		{
			_choice = ERIC;
			_camera->cameraChange(_x[ERIC], _y[ERIC]);
			SOUNDMANAGER->play("UI_OlafPic");
		}
	}
}

void playerManager::pixelCollisionGreen()
{
	//���� �ö󼭰�
	if (!_isJump)
	{
		//if (select == 1)
		{
			//����
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
					_eric->setIsJumpMotion(false); //�ȼ��浹�ϸ� ������� ����

					break;
				}
			}
		}
		//else if (select == 2)
		{
			//���α�
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
			//�ö���
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
	//���ʺ�
	//if (select == 1)
	{
		//����
		for (int i = _prove_X[ERIC] - 40; i > _prove_X[ERIC] - 50; --i)
		{
			COLORREF color = GetPixel(IMAGEMANAGER->findImage("pixel")->getMemDC(), i, _prove_Y[ERIC] - 50);

			int r = GetRValue(color);
			int g = GetGValue(color);
			int b = GetBValue(color);

			if (r == 255 && g == 255 && b == 0)
			{
				_x[ERIC] = i;
				if (KEYMANAGER->isStayKeyDown(VK_LEFT))
				{
					_eric->setEricState(ERIC_LEFT_WALL_PUSH);
					_eric->setEricMotion(KEYANIMANAGER->findAnimation("ericName", "leftPush"));
					_eric->getEricMotion()->start();
				}
				else if ((KEYMANAGER->isOnceKeyUp(VK_LEFT)))
				{
					_eric->setEricState(ERIC_LEFT_STOP);
					_eric->setEricMotion(KEYANIMANAGER->findAnimation("ericName", "leftStop"));
					_eric->getEricMotion()->start();
				}
				break;
			}
		}
	}
	//else if (select == 2)
	{
		//���α�
		for (int i = _prove_X[BALEOG] - 40; i > _prove_X[BALEOG] - 50; --i)
		{
			COLORREF color = GetPixel(IMAGEMANAGER->findImage("pixel")->getMemDC(), i, _prove_Y[BALEOG] - 50);

			int r = GetRValue(color);
			int g = GetGValue(color);
			int b = GetBValue(color);

			if (r == 255 && g == 255 && b == 0)
			{
				_x[BALEOG] = i;
				if (KEYMANAGER->isStayKeyDown(VK_LEFT))
				{
					_baleog->setBaleogState(BALEOG_LEFT_WALL_PUSH);
					_baleog->setBaleogMotion(KEYANIMANAGER->findAnimation("���α�ĳ����", "leftPush"));
					_baleog->getBaleogMotion()->start();
				}
				else if ((KEYMANAGER->isOnceKeyUp(VK_LEFT)))
				{
					_baleog->setBaleogState(BALEOG_LEFT_STOP);
					_baleog->setBaleogMotion(KEYANIMANAGER->findAnimation("���α�ĳ����", "leftStop"));
					_baleog->getBaleogMotion()->start();
				}
				break;
			}
		}
	}
	//else if (select == 3)
	{
		//�ö���
		for (int i = _prove_X[OLAF] - 40; i > _prove_X[OLAF] - 50; --i)
		{
			COLORREF color = GetPixel(IMAGEMANAGER->findImage("pixel")->getMemDC(), i, _prove_Y[OLAF] - 50);

			int r = GetRValue(color);
			int g = GetGValue(color);
			int b = GetBValue(color);

			if (r == 255 && g == 255 && b == 0)
			{
				_x[OLAF] = i;

				if (KEYMANAGER->isStayKeyDown(VK_LEFT))
				{
					_olaf->setOlafDirection(OLAF_DIRECTION_LEFT_WALL_PUSH);
					_olaf->setOlafMotion(KEYANIMANAGER->findAnimation("olafName", "olafLeftPush"));
					_olaf->getOlafMotion()->start();
				}
				else if ((KEYMANAGER->isOnceKeyUp(VK_LEFT)))
				{
					_olaf->setOlafDirection(OLAF_DIRECTION_LEFT_STOP);
					_olaf->setOlafMotion(KEYANIMANAGER->findAnimation("olafName", "olafLeftStop"));
					_olaf->getOlafMotion()->start();
				}
			
				break;
			}
		}
	}
}

void playerManager::pixelCollisionEmerald()
{
	//�����ʺ�
	//if (select == 1)
	{
		//����
		for (int i = _prove_X[ERIC] + 45; i < _prove_X[ERIC] + 50; ++i)
		{
			COLORREF color = GetPixel(IMAGEMANAGER->findImage("pixel")->getMemDC(), i, _prove_Y[ERIC] - 50);

			int r = GetRValue(color);
			int g = GetGValue(color);
			int b = GetBValue(color);

			if (r == 0 && g == 255 && b == 255)
			{
				_x[ERIC] = i - 100;

				if (KEYMANAGER->isStayKeyDown(VK_RIGHT))
				{
					_eric->setEricState(ERIC_RIGHT_WALL_PUSH);
					_eric->setEricMotion(KEYANIMANAGER->findAnimation("ericName", "rightPush"));
					_eric->getEricMotion()->start();
				}
				else if ((KEYMANAGER->isOnceKeyUp(VK_RIGHT)))
				{
					_eric->setEricState(ERIC_RIGHT_STOP);
					_eric->setEricMotion(KEYANIMANAGER->findAnimation("ericName", "rightStop"));
					_eric->getEricMotion()->start();
				}
				break;
			}
		}
	}
	//else if (select == 2)
	{
		//���α�
		for (int i = _prove_X[BALEOG] + 45; i < _prove_X[BALEOG] + 50; ++i)
		{
			COLORREF color = GetPixel(IMAGEMANAGER->findImage("pixel")->getMemDC(), i, _prove_Y[BALEOG] - 50);

			int r = GetRValue(color);
			int g = GetGValue(color);
			int b = GetBValue(color);

			if (r == 0 && g == 255 && b == 255)
			{
				_x[BALEOG] = i - 100;

				if (KEYMANAGER->isStayKeyDown(VK_RIGHT))
				{
					_baleog->setBaleogState(BALEOG_RIGHT_WALL_PUSH);
					_baleog->setBaleogMotion(KEYANIMANAGER->findAnimation("���α�ĳ����", "rightPush"));
					_baleog->getBaleogMotion()->start();
				}
				else if ((KEYMANAGER->isOnceKeyUp(VK_RIGHT)))
				{
					_baleog->setBaleogState(BALEOG_RIGHT_STOP);
					_baleog->setBaleogMotion(KEYANIMANAGER->findAnimation("���α�ĳ����", "rightStop"));
					_baleog->getBaleogMotion()->start();
				}

				break;
			}
		}
	}
	//else if (select == 3)
	{
		//�ö���
		for (int i = _prove_X[OLAF] + 45; i < _prove_X[OLAF] + 50; ++i)
		{
			COLORREF color = GetPixel(IMAGEMANAGER->findImage("pixel")->getMemDC(), i, _prove_Y[OLAF] - 50);

			int r = GetRValue(color);
			int g = GetGValue(color);
			int b = GetBValue(color);

			if (r == 0 && g == 255 && b == 255)
			{
				_x[OLAF] = i - 100;

				if (KEYMANAGER->isStayKeyDown(VK_RIGHT))
				{
					_olaf->setOlafDirection(OLAF_DIRECTION_RIGHT_WALL_PUSH);
					_olaf->setOlafMotion(KEYANIMANAGER->findAnimation("olafName", "olafRightPush"));
					_olaf->getOlafMotion()->start();
						
				}
				else if ((KEYMANAGER->isOnceKeyUp(VK_RIGHT)))
				{
					_olaf->setOlafDirection(OLAF_DIRECTION_RIGHT_STOP);
					_olaf->setOlafMotion(KEYANIMANAGER->findAnimation("olafName", "olafRightStop"));
					_olaf->getOlafMotion()->start();
				}
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
			_y[select] -= _jumpPower;
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
		if (select == ERIC)
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

void playerManager::baleogArrow()
{
	if (_arrow->getVArrow().size() == 0)
	{
		if (KEYMANAGER->isOnceKeyDown('S'))
		{
			_baleog->setIsFire(true);
		}
		else if (KEYMANAGER->isOnceKeyUp('S'))
		{
			_baleog->setIsFire(false);
			_baleog->getBaleogMotion()->resume();
			_isArrowFireStop = false;
		}

		if (KEYMANAGER->isStayKeyDown('S'))
		{
			_isArrowFireStop = true;
			if (_baleog->getBaleogMotion()->getFramePos().x == 750 && _baleog->getBaleogState() == BALEOG_RIGHT_ARROW_ATTACK)
			{
				_baleog->getBaleogMotion()->pause();
			}
			else if (_baleog->getBaleogMotion()->getFramePos().x == 300 && _baleog->getBaleogState() == BALEOG_LEFT_ARROW_ATTACK)
			{
				_baleog->getBaleogMotion()->pause();
			}
		}
	}
	if (_isArrowFireStop == false)
	{
		if (_baleog->getBaleogState() == BALEOG_RIGHT_ARROW_ATTACK)
		{
			if (_baleog->getBaleogMotion()->getFramePos().x == 750)
			{
				SOUNDMANAGER->play("baleog_ArrowPull");
				_arrow->arrowFire(_x[BALEOG], _y[BALEOG] + 50, 5, PI2);
				_arrow->setArrowState(ARROW_RIGHT_FIRE);
			}
		}
		else if (_baleog->getBaleogState() == BALEOG_LEFT_ARROW_ATTACK)
		{
			if (_baleog->getBaleogMotion()->getFramePos().x == 300)
			{
				SOUNDMANAGER->play("baleog_ArrowPull");
				_arrow->arrowFire(_x[BALEOG], _y[BALEOG] + 50, 5, PI);
				_arrow->setArrowState(ARROW_LEFT_FIRE);
			}
		}
	}
}
