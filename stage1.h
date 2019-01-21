#pragma once
#include "gameNode.h"
#include "playerManager.h"
#include "item.h"

enum ITEM
{
	REDKEY,
	REDLOCK,
	GOLDKEY,
	GOLDLOCK,
	MEAT,
	BANANA
};


class stage1 : public gameNode
{
private:
	playerManager* _playerManager;
	item* _item;

	bool _isPixel;


public:
	stage1();
	~stage1();

	HRESULT init();
	void release();
	void update();
	void render();

	void viewPixel();
	



};

