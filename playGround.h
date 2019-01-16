#pragma once
#include "gameNode.h"
#include "stage1.h"
#include "menu.h"

//숫자패드 
//0 픽셀보이기
//1 렉트보이기
//2
//3
//4
//5
//6
//7
//8
//9



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

