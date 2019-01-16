#pragma once
#include "gameNode.h"

enum OLAFDIRECTION
{
	OLAF_DIRECTION_RIGHT_STOP,
	OLAF_DIRECTION_LEFT_STOP,
	OLAF_DIRECTION_RIGHT_SHIELD,
	OLAF_DIRECTION_LEFT_SHIELD,
	OLAF_DIRECTION_RIGHT_MOVE,
	OLAF_DIRECTION_LEFT_MOVE,
	OLAF_DIRECTION_RIGHT_JUMP,
	OLAF_DIRECTION_LEFT_JUMP
};



class olaf : public gameNode
{
private:

	OLAFDIRECTION _olafDirection;

	image* _olafimg;
	float _olaf_x, _olaf_y;
	RECT _olaf_rc;

	bool _changeMode;
	int num;
	animation* _olafMotion;

public:

	olaf();
	~olaf();

	HRESULT init();
	void release();
	void update();
	void render();

	OLAFDIRECTION getOlafDirection() { return _olafDirection; }
	void setOlafDirection(OLAFDIRECTION direction) { _olafDirection = direction; }

	animation* getOlafMotion() { return _olafMotion; }
	void setOlafMotion(animation* ani) { _olafMotion = ani; }


	void olafMovement();
};

