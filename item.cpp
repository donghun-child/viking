#include "stdafx.h"
#include "item.h"


item::item()
{
}


item::~item()
{
}

HRESULT item::init(const char* imageName, bool isFrame, int frameY)
{
	_isFrame = isFrame;
	_itemName = imageName;
	_frameY = frameY;

	return S_OK;
}

void item::release()
{
	for (_viItem = _vItem.begin(); _viItem != _vItem.end(); ++_viItem)
	{
		_viItem = _vItem.erase(_viItem);

		--_viItem;
	}
}

void item::update()
{
	removeItem();



}

void item::render()
{
	for (_viItem = _vItem.begin(); _viItem != _vItem.end(); ++_viItem)
	{
		if (!_isFrame)
		{
			_viItem->image->render(getMemDC(), _viItem->x, _viItem->y);
		}
		else
		{
			_viItem->image->frameRender(getMemDC(), _viItem->x, _viItem->y,_viItem->frameX, _frameY);
		}
	}
}

void item::createItem(float x, float y, float width, float height)
{
	tagItem item;
	ZeroMemory(&item, sizeof(item));
	item.image = IMAGEMANAGER->findImage(_itemName);
	item.frameX = 0;
	item.frameY = _frameY;
	item.x = x;
	item.y = y;
	item.isLive = true;
	if (!_isFrame)
	{
		item.rc = RectMake(x, y, item.image->GetWidth(), item.image->GetHeight());
	}
	else
	{
		item.rc = RectMake(x, y, item.image->getFrameWidth(), item.image->getFrameHeight());
	}

	_vItem.push_back(item);
}

void item::removeItem()
{
	for (_viItem = _vItem.begin(); _viItem != _vItem.end(); )
	{
		if ((*_viItem).isLive == false)
		{
			_vItem.erase(_viItem);
		}
		else
		{
			++_viItem;
		}
	}
}
