#pragma once
#include "gameNode.h"
#include "playerManager.h"
#include "item.h"
#include "ui.h"

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
	item* _bubble;
	ui* _ui;

	bool _isPixel;
	bool _uiChange;

	float _bubbleTime;
	float _worldTime;
	int _bubbleFrameTime;
	int _bubbleRemoveTime;

public:
	stage1();
	~stage1();

	HRESULT init();
	void release();
	void update();
	void render();

	void viewPixel();
	
	void createBubble();


};

