#pragma once
#include "gameNode.h"
#include "jump.h"

enum ERICSTATE
{
	ERIC_RIGHT_STOP,
	ERIC_LEFT_STOP,
	ERIC_RIGHT_MOVE,
	ERIC_LEFT_MOVE,
	ERIC_UP_MOVE,
	ERIC_DOWN_MOVE,
	ERIC_RIGHT_JUMP,
	ERIC_LEFT_JUMP,
	ERIC_RIGHT_DASH,
	ERIC_LEFT_DASH,

};
class eric : public gameNode
{
private:
	image* _ericImage;
	RECT _eric_rc;
	float _eric_X, _eric_Y;
	float _start_X, _start_Y;
	POINTFLOAT _cameraPos;

	float _acceleration; //대쉬할때 가속도
	float _speed;
	animation* _ericMotion; //에릭 모션
	ERICSTATE _ericState; //에릭상태

	jump* _ericJump;

public:
	eric();
	~eric();

	HRESULT init();
	void release();
	void update(POINTFLOAT StagePos, int choice);
	void render();

	static void rightDash(void* obj);
	static void leftDash(void* obj);
	static void rightJump(void* obj);
	static void leftJump(void* obj);

	ERICSTATE getEricState() {return _ericState;}
	void setEricState(ERICSTATE state) {_ericState = state;}

	animation* getEricMotion() {return _ericMotion;}
	void setEricMotion(animation* motion) {_ericMotion = motion;}

	float getplayerX() { return _eric_X; }
	float getplayerY() { return _eric_Y; }
};

