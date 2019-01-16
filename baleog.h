#pragma once
#include "gameNode.h"

struct baleogPlayer
{
	float x, y;
	image* baleogImage;
	RECT baleogRc;
	float speed;
};


enum BALEOGSTATE //벨로그 상태
{
	BALEOG_RIGHT_STOP, //오른쪽 기본상태
	BALEOG_LEFT_STOP, //왼쪽 기본상태
	BALEOG_RIGHT_MOVE, //오른쪽 움직임
	BALEOG_LEFT_MOVE, //왼쪽 움직임
	BALEOG_RIGHT_SWORD_ATTACK, //오른쪽 검공격
	BALEOG_LEFT_SWORD_ATTACK, //왼쪽 검공격
	BALEOG_RIGHT_ARROW_ATTACK, //오른쪽 화살공격
	BALEOG_LEFT_ARROW_ATTACK, //왼쪽 화살공격
};

enum BALEOGINFO // 벨로그 정보들
{
	BALEOG_X = WINSIZEX / 2,
	BALEOG_Y = WINSIZEY / 2,
	BALEOG_SPEED = 0,
};

class baleog : public gameNode
{
private:
	BALEOGSTATE _baleogState;
	baleogPlayer _baleogPlayer;

	animation* _baleogMotion; //벨로그 모션 담아줄 빈 애니메이션
public:

	baleog();
	~baleog();

	HRESULT init();
	void release();
	void update();
	void render();


};

