#pragma once
#include "gameNode.h"
#include <vector>

struct tagItem
{
	image* image;
	float x;
	float y;
	RECT rc;
	bool isLive;
	int frameX;
	int frameY;
};

class item : public gameNode
{
private:
	vector<tagItem>				_vItem;
	vector<tagItem>::iterator	_viItem;

	bool _isFrame;
	const char* _itemName;
	int _frameY;

public:
	item();
	~item();

	HRESULT init(const char* imageName,bool isFrame = 0,int frameY = 0);
	void release();
	void update();
	void render();

	void createItem(float x, float y,float width,float height);
	void removeItem();

	vector<tagItem> getVItem() { return _vItem; }
	vector<tagItem>* getVItemAddress() { return &_vItem; }
	vector<tagItem>::iterator getViItem() { return _viItem; }

};

