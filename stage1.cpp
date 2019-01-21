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

	_playerManager = new playerManager;
	_playerManager->init();

	_item = new item;
	_bubble = new item;
	_item->getPlayerManagerLinkAddress(_playerManager);
	_bubble->getPlayerManagerLinkAddress(_playerManager);

	_ui = new ui;
	_ui->init();

	_uiChange = false;

	_bubbleTime = 5.0f;
	_worldTime = TIMEMANAGER->getWorldTime();

	//아이템 만들거면 크리에이트 아이템 한후 
	//좌표 입력후    무슨아이템인지 이넘문   그다음칸은 프레임Y입력
	//_item->createItem("item", 500,200, REDKEY, 0);
	//_item->createItem("item", 800, 300, REDLOCK, 0);

	return S_OK;
}

void stage1::release()
{
	SAFE_DELETE(_playerManager);
	SAFE_DELETE(_item);
	SAFE_DELETE(_bubble);
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
		//픽셀 보이게하는 함수
		viewPixel();
		_item->update();
		_bubble->update();
		createBubble();
	}
	else _ui->update();

	_ui->profileUpdate(_playerManager->getChoice());
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
	_bubble->render();
	_ui->render();




	char str[100];
	sprintf_s(str, "플레이어 x : %d", _playerManager->getChoice());
	TextOut(getMemDC(), 300, 30, str, strlen(str));
	//sprintf_s(str, "플레이어 y : %f", _playerManager->getEricY());
	//TextOut(getMemDC(), 300, 40, str, strlen(str));
	//sprintf_s(str, "카메라 X : %f", _playerManager->getCamera()->getCameraX());
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

void stage1::createBubble()
{
	//_bubbleTime 설정한 시간 마다 버블 생성
	if (_bubbleTime + _worldTime <= TIMEMANAGER->getWorldTime())
	{
		_worldTime = TIMEMANAGER->getWorldTime();

		_bubble->createItem("bubble", 1666, 2060, 0, 0);
	}

	_bubbleFrameTime++;
	for (int i = 0; i < _bubble->getVItem().size(); ++i)
	{
		//버블이 730높이보다 크면 높이가 감소되며 프레임이 0 1 반복
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
		//버블 높이가 730보다 작아지면 시간에 따라 프레임이 증가하며 삭제된다.
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





