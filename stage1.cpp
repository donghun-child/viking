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
	IMAGEMANAGER->addFrameImage("item", "image/item.bmp", 330, 55, 6, 1, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("bubble", "image/bubble.bmp", 900, 180, 5, 1, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("dari", "image/dari.bmp", 2200, 436, 10, 2, true, RGB(255, 0, 255));

	_playerManager = new playerManager;
	_playerManager->init();

	_redKey = new item;
	_redLock = new item;
	_clockDari = new item;
	_banana = new item;
	_meat = new item;

	_bubble = new item;
	_bubble->init();

	//������
	_redKey->getPlayerManagerLinkAddress(_playerManager);
	_playerManager->getItemLinkAddress(_redKey);
	_redLock->getPlayerManagerLinkAddress(_playerManager);
	_playerManager->getItemLinkAddress(_redLock);
	_clockDari->getPlayerManagerLinkAddress(_playerManager);
	_playerManager->getItemLinkAddress(_clockDari);
	_banana->getPlayerManagerLinkAddress(_playerManager);
	_playerManager->getItemLinkAddress(_banana);
	_meat->getPlayerManagerLinkAddress(_playerManager);
	_playerManager->getItemLinkAddress(_meat);

	//����
	_bubble->getPlayerManagerLinkAddress(_playerManager);
	_playerManager->getItemLinkAddress(_bubble);

	//ui
	_ui = new ui;
	_ui->init();

	_uiChange = false;

	_bubbleTime = 5.0f;
	_worldTime = TIMEMANAGER->getWorldTime();

	_redKey->createItem("item", 2930, 390, REDKEY, 0);
	_redLock->createItem("item", 1100, 760, REDLOCK, 0);
	_clockDari->createItem("dari", 870, 675, 0, 0);
	_banana->createItem("item", 1435, 1670, BANANA, 0);
	_meat->createItem("item", 2880, 2000, MEAT, 0);

	return S_OK;
}

void stage1::release()
{
	SAFE_DELETE(_playerManager);
	SAFE_DELETE(_redKey);
	SAFE_DELETE(_redLock);
	SAFE_DELETE(_clockDari);
	SAFE_DELETE(_bubble);
	SAFE_DELETE(_banana);
	SAFE_DELETE(_meat);
	SAFE_DELETE(_ui);
}

void stage1::update()
{
	if (KEYMANAGER->isOnceKeyDown(VK_TAB))
	{
		if (_uiChange) _uiChange = false;
		else _uiChange = true;
	}

	if (!_uiChange)
	{
		_playerManager->update();
		//�ȼ� ���̰��ϴ� �Լ�
		viewPixel();
		_redKey->update();
		_redLock->update();
		_clockDari->update();
		_banana->update();
		_meat->update();
		_bubble->update();
		createBubble();
		itemCollision();
	}
	_ui->update(_playerManager->getChoice(), _uiChange);
	_ui->profileUpdate(_playerManager->getChoice());

	

	//�ٸ� �����̱�
	//if (KEYMANAGER->isOnceKeyDown(VK_NUMPAD9))
	//{
	//	for (int i = 0; i < _clockDari->getVItem().size(); ++i)
	//	{
	//		(*_clockDari->getVItemAddress())[i].frameX += 1;
	//	}
	//}
	//if (KEYMANAGER->isOnceKeyDown(VK_NUMPAD8))
	//{
	//	for (int i = 0; i < _clockDari->getVItem().size(); ++i)
	//	{
	//		(*_clockDari->getVItemAddress())[i].frameX -= 1;
	//	}
	//}
}

void stage1::render()
{
	IMAGEMANAGER->render("backGround", getMemDC(), 0, 0, _playerManager->getCamera()->getCameraX(), _playerManager->getCamera()->getCameraY(), WINSIZEX, WINSIZEY);

	if (_isPixel)
	{
		IMAGEMANAGER->render("pixel", getMemDC(), 0, 0, _playerManager->getCamera()->getCameraX(), _playerManager->getCamera()->getCameraY(), WINSIZEX, WINSIZEY);
	}
	_playerManager->render();
	_redKey->render();
	_redLock->render();
	_clockDari->render();
	_banana->render();
	_meat->render();
	_bubble->render();
	_ui->render();

	char str[100];
	sprintf_s(str, "�÷��̾� x : %d", _currentFrameX);
	TextOut(getMemDC(), 300, 30, str, strlen(str));
	//sprintf_s(str, "�÷��̾� y : %f", _playerManager->getEricY());
	//TextOut(getMemDC(), 300, 40, str, strlen(str));
	//sprintf_s(str, "ī�޶� X : %f", _playerManager->getCamera()->getCameraX());
	//TextOut(getMemDC(), 300, 60, str, strlen(str));
}

void stage1::viewPixel()
{
	//�ȼ����̱��
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

void stage1::createBubble()
{
	//_bubbleTime ������ �ð� ���� ���� ����
	if (_bubbleTime + _worldTime <= TIMEMANAGER->getWorldTime())
	{
		_worldTime = TIMEMANAGER->getWorldTime();

		_bubble->createItem("bubble", 1666, 2060, 0, 0);
	}

	_bubbleFrameTime++;
	for (int i = 0; i < _bubble->getVItem().size(); ++i)
	{
		//������ 730���̺��� ũ�� ���̰� ���ҵǸ� �������� 0 1 �ݺ�
		if (_bubble->getVItem()[i].y > 730 && _bubbleFrameTime % 50 < 25)
		{
			(*_bubble->getVItemAddress())[i].y -= 2;
			(*_bubble->getVItemAddress())[i].frameX = 0;
		}
		else if (_bubble->getVItem()[i].y > 730 && _bubbleFrameTime % 50 >= 25)
		{
			(*_bubble->getVItemAddress())[i].y -= 2;
			(*_bubble->getVItemAddress())[i].frameX = 1;
		}
		//���� ���̰� 730���� �۾����� �ð��� ���� �������� �����ϸ� �����ȴ�.
		else if (_bubble->getVItem()[i].y <= 730)
		{
			_bubbleRemoveTime++;
			if (_bubbleRemoveTime < 10)
			{
				(*_bubble->getVItemAddress())[i].frameX = 2;
			}
			else if (_bubbleRemoveTime < 20)
			{
				(*_bubble->getVItemAddress())[i].frameX = 3;
			}
			else if (_bubbleRemoveTime < 30)
			{
				(*_bubble->getVItemAddress())[i].frameX = 4;
			}
			else if (_bubbleRemoveTime < 35)
			{
				(*_bubble->getVItemAddress())[i].isLive = false;
				_bubbleRemoveTime = 0;
			}
		}
	}
}

void stage1::itemCollision()
{
	//����Ű �浹
	for (int i = 0; i < _redKey->getVItem().size(); ++i)
	{
		//����
		if (IntersectRect(&temp, &(*_redKey->getVItemAddress())[i].rc, &_playerManager->getEricRect()))
		{
			_currentFrameX = (*_redKey->getVItemAddress())[i].frameX;
			(*_redKey->getVItemAddress())[i].isLive = false;
			_ui->setEricFrameX(_currentFrameX);
		}
		//���α�
		if (IntersectRect(&temp, &(*_redKey->getVItemAddress())[i].rc, &_playerManager->getBaleogRect()))
		{
			_currentFrameX = (*_redKey->getVItemAddress())[i].frameX;
			(*_redKey->getVItemAddress())[i].isLive = false;
			
		}
		//�ö���
		if (IntersectRect(&temp, &(*_redKey->getVItemAddress())[i].rc, &_playerManager->getOlafRect()))
		{
			_currentFrameX = (*_redKey->getVItemAddress())[i].frameX;
			(*_redKey->getVItemAddress())[i].isLive = false;
			
		}
	}
	//�����ڹ��� �浹
	for (int i = 0; i < _redLock->getVItem().size(); ++i)
	{
		//����
		if (IntersectRect(&temp, &(*_redLock->getVItemAddress())[i].rc, &_playerManager->getEricRect()))
		{


		}
		//���α�
		if (IntersectRect(&temp, &(*_redLock->getVItemAddress())[i].rc, &_playerManager->getBaleogRect()))
		{


		}
		//�ö���
		if (IntersectRect(&temp, &(*_redLock->getVItemAddress())[i].rc, &_playerManager->getOlafRect()))
		{


		}
	}
	//�ٳ��� �浹
	for (int i = 0; i < _banana->getVItem().size(); ++i)
	{
		//����
		if (IntersectRect(&temp, &(*_banana->getVItemAddress())[i].rc, &_playerManager->getEricRect()))
		{
			_currentFrameX = (*_banana->getVItemAddress())[i].frameX;
			(*_banana->getVItemAddress())[i].isLive = false;

		}
		//���α�
		if (IntersectRect(&temp, &(*_banana->getVItemAddress())[i].rc, &_playerManager->getBaleogRect()))
		{
			_currentFrameX = (*_banana->getVItemAddress())[i].frameX;
			(*_banana->getVItemAddress())[i].isLive = false;

		}
		//�ö���
		if (IntersectRect(&temp, &(*_banana->getVItemAddress())[i].rc, &_playerManager->getOlafRect()))
		{
			_currentFrameX = (*_banana->getVItemAddress())[i].frameX;
			(*_banana->getVItemAddress())[i].isLive = false;

		}
	}
	//��� �浹
	for (int i = 0; i < _meat->getVItem().size(); ++i)
	{
		//����
		if (IntersectRect(&temp, &(*_meat->getVItemAddress())[i].rc, &_playerManager->getEricRect()))
		{
			_currentFrameX = (*_meat->getVItemAddress())[i].frameX;
			(*_meat->getVItemAddress())[i].isLive = false;

		}
		//���α�
		if (IntersectRect(&temp, &(*_meat->getVItemAddress())[i].rc, &_playerManager->getBaleogRect()))
		{
			_currentFrameX = (*_meat->getVItemAddress())[i].frameX;
			(*_meat->getVItemAddress())[i].isLive = false;

		}
		//�ö���
		if (IntersectRect(&temp, &(*_meat->getVItemAddress())[i].rc, &_playerManager->getOlafRect()))
		{
			_currentFrameX = (*_meat->getVItemAddress())[i].frameX;
			(*_meat->getVItemAddress())[i].isLive = false;

		}
	}
	//���� �浹
	for (int i = 0; i < _bubble->getVItem().size(); ++i)
	{
		//����
		if (IntersectRect(&temp, &(*_bubble->getVItemAddress())[i].rc, &_playerManager->getEricRect()))
		{
			if (_playerManager->getEricRect().left > (*_bubble->getVItemAddress())[i].rc.left && _playerManager->getEricRect().right < (*_bubble->getVItemAddress())[i].rc.right)
			{
				if ((*_bubble->getVItemAddress())[i].rc.bottom - 50 < _playerManager->getEricRect().bottom)
				{
					_bottomTum = (_playerManager->getEricRect().bottom) - ((*_bubble->getVItemAddress())[i].rc.bottom - 50);

					_playerManager->setEricY(_playerManager->getEricY() - _bottomTum);
				}
			}
		}

		//���α�
		if (IntersectRect(&temp, &(*_bubble->getVItemAddress())[i].rc, &_playerManager->getBaleogRect()))
		{
			if (_playerManager->getBaleogRect().left > (*_bubble->getVItemAddress())[i].rc.left && _playerManager->getBaleogRect().right < (*_bubble->getVItemAddress())[i].rc.right)
			{
				if ((*_bubble->getVItemAddress())[i].rc.bottom - 50 < _playerManager->getBaleogRect().bottom)
				{
					_bottomTum = (_playerManager->getBaleogRect().bottom) - ((*_bubble->getVItemAddress())[i].rc.bottom - 50);

					_playerManager->setBalogY(_playerManager->getBalogY() - _bottomTum );
				}
			}
		}

		//�ö���
		if (IntersectRect(&temp, &(*_bubble->getVItemAddress())[i].rc, &_playerManager->getOlafRect()))
		{
			if (_playerManager->getOlafRect().left > (*_bubble->getVItemAddress())[i].rc.left && _playerManager->getOlafRect().right < (*_bubble->getVItemAddress())[i].rc.right)
			{
				if ((*_bubble->getVItemAddress())[i].rc.bottom - 50 < _playerManager->getOlafRect().bottom)
				{
					_bottomTum = (_playerManager->getOlafRect().bottom) - ((*_bubble->getVItemAddress())[i].rc.bottom - 50);

					_playerManager->setOlafY(_playerManager->getOlafY() - _bottomTum );
				}
			}
		}
	}
}





