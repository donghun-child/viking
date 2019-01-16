#pragma once
#include "gameNode.h"

struct tagArrow
{
	image* arrowImage;
	float x, y;
	RECT arrowRc;
	float speed;
	float angle;
	float fireX, fireY;
	float radius;
};
class arrow : public gameNode
{
private:
	vector<tagArrow>			_vArrow;
	vector<tagArrow>::iterator  _viArrow;

	const char* _imageName;
	float _range;
	int _arrowMax;

	int _currentFrameX, _currentFrameY;
	int _frameCount;
public:
	arrow();
	~arrow();

	HRESULT init(const char* imageName, int arrowMax, float range);
	void release();
	void update();
	void render();

	void arrowFire(float x, float y, float angle, float speed);
	void arrowMove();
};

