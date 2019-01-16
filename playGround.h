#pragma once
#include "gameNode.h"
#include "stage1.h"
#include "menu.h"

class playGround : public gameNode
{
private:
	gameNode* _menu;
	gameNode* _stage1;



public:
	virtual HRESULT init();
	virtual void release();
	virtual void update();
	virtual void render();
	

	playGround();
	~playGround();
};

