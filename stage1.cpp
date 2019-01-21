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

	_playerManager = new playerManager;
	_playerManager->init();

	_item = new item;
	_item->getPlayerManagerLinkAddress(_playerManager);

	_ui = new ui;
	_ui->init();

	_uiChange = false;

	//������ ����Ÿ� ũ������Ʈ ������ ���� 
	//��ǥ �Է���    �������������� �̳ѹ�   �״���ĭ�� ������Y�Է�
	//_item->createItem("item", 500,200, REDKEY, 0);
	//_item->createItem("item", 800, 300, REDLOCK, 0);

	return S_OK;
}

void stage1::release()
{
	SAFE_DELETE(_playerManager);
	SAFE_DELETE(_item);
}

void stage1::update()
{
	if (KEYMANAGER->isOnceKeyDown(VK_TAB))
	{
		_uiChange = true;
	}

	if (!_uiChange)
	{
		_playerManager->update();
		//�ȼ� ���̰��ϴ� �Լ�
		viewPixel();
		_item->update();
	}
	else _ui->update();
}

void stage1::render()
{
	IMAGEMANAGER->render("backGround", getMemDC(), 0, 0, _playerManager->getCamera()->getCameraX(), _playerManager->getCamera()->getCameraY(), WINSIZEX, WINSIZEY);

	if (_isPixel)
	{
		IMAGEMANAGER->render("pixel", getMemDC(), 0, 0, _playerManager->getCamera()->getCameraX(), _playerManager->getCamera()->getCameraY(), WINSIZEX, WINSIZEY);
	}
	_playerManager->render();
	_item->render();
	_ui->render();




	//char str[100];
	//sprintf_s(str, "�÷��̾� x : %f", _playerManager->getEricX());
	//TextOut(getMemDC(), 300, 20, str, strlen(str));
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





