#pragma once
#include "gameNode.h"



class camera : public gameNode
{
private:
	image* _mapimage;

	POINTFLOAT _camera;

	float _mapX, _mapY;
	bool change;

	float Distance;
	float angle;

public:
	camera();
	~camera();

	HRESULT init();
	void release();
	void update(float playerX, float playerY, int choice, float changespeed);
	void render();

	POINTFLOAT getCameraPos() { return _camera; }

	float getMapx() { return _mapX; }
	float getMapy() { return _mapY; }

	//카메라 전환
	void setChange(bool v) { change = v; }
	//플레이어간의 거리 
	void setDistance(float v) { Distance = v; }
	void setAngle(float v) { Distance = v; }
};

