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

	//벨로그 화살부분
	IMAGEMANAGER->addFrameImage("화살", "image/bullet.bmp", 85, 20, 5, 2, true, RGB(255, 0, 255));
	_arrow = new arrow;
	_arrow->init("화살", 0, 600);
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

	//사다리 부분
	_ladder[0].x = 920;
	_ladder[0].y = 1350;
	_ladder[0].viewX = _ladder[0].x;
	_ladder[0].viewY = _ladder[0].y;
	_ladder[0].rc = RectMake(_ladder[0].viewX, _ladder[0].viewY, 30, 285);

	_ladder[1].x = 2000;
	_ladder[1].y = 1170;
	_ladder[1].viewX = _ladder[1].x;
	_ladder[1].viewY = _ladder[1].y;
	_ladder[1].rc = RectMake(_ladder[1].viewX, _ladder[1].viewY, 30, 650);

	_ladder[2].x = 2140;
	_ladder[2].y = 1825;
	_ladder[2].viewX = _ladder[2].x;
	_ladder[2].viewY = _ladder[2].y;
	_ladder[2].rc = RectMake(_ladder[2].viewX, _ladder[2].viewY, 30, 275);

	_ladder[3].x = 2515;
	_ladder[3].y = 1540;
	_ladder[3].viewX = _ladder[3].x;
	_ladder[3].viewY = _ladder[3].y;
	_ladder[3].rc = RectMake(_ladder[3].viewX, _ladder[3].viewY, 30, 235);

	_ladder[4].x = 2890;
	_ladder[4].y = 1305;
	_ladder[4].viewX = _ladder[4].x;
	_ladder[4].viewY = _ladder[4].y;
	_ladder[4].rc = RectMake(_ladder[4].viewX, _ladder[4].viewY, 30, 475);
	
	_isDebug = false;

	for (int i = 0; i < 3; ++i)
	{
		//센터
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

	_isCameraMode = false;

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
	//벨로그 화살
	_arrow->update();
	for (int i = 0; i < _arrow->getVArrow().size(); i++)
	{
		(*_arrow->getVArrowAddress())[i].viewX = (*_arrow->getVArrowAddress())[i].x - _camera->getCameraX();
		(*_arrow->getVArrowAddress())[i].viewY = (*_arrow->getVArrowAddress())[i].y - _camera->getCameraY();
	}

	//에릭의 점프
	jumpGravity(_choice);

	//사다리 충돌
	ladderCollision();
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

	//사다리 갱신
	for (int i = 0; i < 5; i++)
	{
		_ladder[i].viewX = _ladder[i].x - _camera->getCameraX();
		_ladder[i].viewY = _ladder[i].y - _camera->getCameraY();
	}
	_ladder[0].rc = RectMake(_ladder[0].viewX, _ladder[0].viewY, 30, 285);
	_ladder[1].rc = RectMake(_ladder[1].viewX, _ladder[1].viewY, 30, 650);
	_ladder[2].rc = RectMake(_ladder[2].viewX, _ladder[2].viewY, 30, 275);
	_ladder[3].rc = RectMake(_ladder[3].viewX, _ladder[3].viewY, 30, 235);
	_ladder[4].rc = RectMake(_ladder[4].viewX, _ladder[4].viewY, 30, 475);

	//갱신
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

	for (int i = 0; i < 5; i++)
	{
		Rectangle(getMemDC(), _ladder[i].rc);
	}
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
	//_camera->render();
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

	//카메라모드 활성화
	if (KEYMANAGER->isOnceKeyDown('W'))
	{
		if (!_isCameraMode)
		{
			_isCameraMode = true;
		}
		else if (_isCameraMode)
		{
			_isCameraMode = false;
		}
	}
	if (_isCameraMode)
	{
		_camera->update(_camerc_x, _camerc_y);
	}
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
		//벨로그 화살쏘는부분
		if (_choice == BALEOG)
		{
			baleogArrow();
		}
	}
	//카메라 체인지 도중이면 다른애들 움직여도 멈추게함.
	else if (_camera->getChange() == true)
	{
		if (_choice == ERIC)
		{
			if (_baleog->getBaleogState() == BALEOG_RIGHT_MOVE)
			{
				_baleog->setBaleogState(BALEOG_RIGHT_STOP);
				_baleog->setBaleogMotion(KEYANIMANAGER->findAnimation("벨로그캐릭터", "rightStop"));
				_baleog->getBaleogMotion()->start();
			}
			else if (_baleog->getBaleogState() == BALEOG_LEFT_MOVE)
			{
				_baleog->setBaleogState(BALEOG_LEFT_STOP);
				_baleog->setBaleogMotion(KEYANIMANAGER->findAnimation("벨로그캐릭터", "leftStop"));
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
				_baleog->setBaleogMotion(KEYANIMANAGER->findAnimation("벨로그캐릭터", "rightStop"));
				_baleog->getBaleogMotion()->start();
			}
			else if (_baleog->getBaleogState() == BALEOG_LEFT_MOVE)
			{
				_baleog->setBaleogState(BALEOG_LEFT_STOP);
				_baleog->setBaleogMotion(KEYANIMANAGER->findAnimation("벨로그캐릭터", "leftStop"));
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

void playerManager::ladderCollision()
{
	for (int i = 0; i < 3; i++)
	{
		for (int j = 0; j < 5; j++)
		{
			RECT temp;
			if(IntersectRect(&temp, &_rc[i], &_ladder[j].rc))
			{
				_baleog->setLadderCollision(true); //사다리 충돌
				_eric->setLadderCollision(true);
				if (_camera->getChange() == false)
				{
					if (KEYMANAGER->isStayKeyDown(VK_UP))
					{
			
						if (_choice == ERIC)
						{
							_y[ERIC] -= _eric->getSpeed();
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
					else if (KEYMANAGER->isStayKeyDown(VK_DOWN))
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
				}
			}
			else if (!IntersectRect(&temp, &_rc[i], &_ladder[j].rc))
			{
				//_eric->setLadderCollision(false);
			}
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
					_eric->setIsJumpMotion(false); //픽셀충돌하면 점프모션 꺼라

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
				if (KEYMANAGER->isStayKeyDown(VK_LEFT))
				{
					_baleog->setBaleogState(BALEOG_LEFT_WALL_PUSH);
					_baleog->setBaleogMotion(KEYANIMANAGER->findAnimation("벨로그캐릭터", "leftPush"));
					_baleog->getBaleogMotion()->start();
				}
				else if ((KEYMANAGER->isOnceKeyUp(VK_LEFT)))
				{
					_baleog->setBaleogState(BALEOG_LEFT_STOP);
					_baleog->setBaleogMotion(KEYANIMANAGER->findAnimation("벨로그캐릭터", "leftStop"));
					_baleog->getBaleogMotion()->start();
				}
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

				if (KEYMANAGER->isStayKeyDown(VK_RIGHT))
				{
					_baleog->setBaleogState(BALEOG_RIGHT_WALL_PUSH);
					_baleog->setBaleogMotion(KEYANIMANAGER->findAnimation("벨로그캐릭터", "rightPush"));
					_baleog->getBaleogMotion()->start();
				}
				else if ((KEYMANAGER->isOnceKeyUp(VK_RIGHT)))
				{
					_baleog->setBaleogState(BALEOG_RIGHT_STOP);
					_baleog->setBaleogMotion(KEYANIMANAGER->findAnimation("벨로그캐릭터", "rightStop"));
					_baleog->getBaleogMotion()->start();
				}

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
