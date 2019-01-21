#pragma once
#include "gameNode.h"

class ui : public gameNode
{
private:
	int _ericCurrentX, _ericCurrentY;
	int _baleogCurrentX, _baleogCurrentY;
	int _olafCurrentX, _olafCurrentY;

	int _choice;
public:
	ui();
	~ui();

	HRESULT init();
	void release();
	void update();
	void render();

	void profileUpdate(int choice);
};

