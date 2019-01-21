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
	int _ericBox_X, _ericBox_Y;
	int	_baleogBox_X, _baleogBox_Y;
	int	_olafBox_X, _olafBox_Y;

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
	void keyControl(int choice);

	int getEricLife() { return _ericLife; }				// 35씩 뺄때마다 life 하나씩 줄어듬~
	int getBaleogLife() { return _baleogLife; }
	int getOlafLife() { return _olafLife; }
};

