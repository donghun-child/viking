#pragma once
#include "gameNode.h"

class ui : public gameNode
{
public:
	ui();
	~ui();

	HRESULT init();
	void release();
	void update();
	void render();
};

