#pragma once
#include "gameNode.h"
#include "stage1.h"
#include "menu.h"
#include "sound.h"

//�����е� 
//0 �ȼ����̱�
//1 ��Ʈ���̱�
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
	menu* _menu;
	stage1* _stage1;
	sound* _sound;


public:
	virtual HRESULT init();
	virtual void release();
	virtual void update();
	virtual void render();
	

	playGround();
	~playGround();
};

