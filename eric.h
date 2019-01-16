#pragma once
#include "gameNode.h"

enum ERICDIRECTION
{
	ERIC_DIRECTION_RIGHT_STOP,
	ERIC_DIRECTION_LEFT_STOP,
	ERIC_DIRECTION_RIGHT_MOVE,
	ERIC_DIRECTION_LEFT_MOVE,
	ERIC_DIRECTION_RIGHT_JUMP,
	ERIC_DIRECTION_LEFT_JUMP
};

class eric
{
private:
	ERICDIRECTION _ericDirection;

	image* _ericimg;
	float _eric_x, _eric_y;
	RECT _eric_rc;

	string _ericName;
	bool _changeMode;
	int num;
	animation* _ericMotion;

public:
	eric();
	~eric();

	HRESULT init();
	HRESULT init(string name);
	void release();
	void update();
	void render();

	ERICDIRECTION getEricDirection() { return _ericDirection; }
	void setEricDirection(ERICDIRECTION direction) { _ericDirection = direction; }

	animation* getEricMotion() { return _ericMotion; }
	void setEricMotion(animation* ani) { _ericMotion = ani; }

	inline int getEricX() { return _eric_x; }
	void setEricX(int ericx) { _eric_x = ericx; }

	inline int getEricY() { return _eric_y; }
	void setEricY(int ericy) { _eric_y = ericy; }

	void ericMovement();

};

