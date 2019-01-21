#pragma once
#include "gameNode.h"

class ui : public gameNode
{
private:
	int _ericCurrentX, _ericCurrentY;
	int _baleogCurrentX, _baleogCurrentY;
	int _olafCurrentX, _olafCurrentY;

	int _choice;
	int _ericLife, _baleogLife, _olafLife;
	bool _ericCursor, _baleogCursor, _olafCursor;

	int _oldTime;

public:
	ui();
	~ui();

	HRESULT init();
	void release();
	void update(int choice, bool uiChange);
	void render();
	void profileUpdate(int choice);

	int getEricLife() { return _ericLife; }				// 35�� �������� life �ϳ��� �پ��~
	int getBaleogLife() { return _baleogLife; }
	int getOlafLife() { return _olafLife; }
};

