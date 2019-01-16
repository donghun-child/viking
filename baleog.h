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
	BALEOG_RIGHT_SWORD_ATTACK_ONE, //오른쪽 첫번째 패턴 검공격
	BALEOG_LEFT_SWORD_ATTACK_ONE, //왼쪽 첫번째 패턴 검공격
	BALEOG_RIGHT_SWORD_ATTACK_TWO, //오른쪽 두번째 패턴 검공격
	BALEOG_LEFT_SWORD_ATTACK_TWO, //왼쪽 두번째 패턴 검공격
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

	//콜백함수 불러올 함수
	static void rightArrowFire(void* obj);
	static void leftArrowFire(void* obj);
	static void rightSwordFire(void* obj);
	static void leftSwordFire(void* obj);

	//벨로그 상태 접근자 설정자
	BALEOGSTATE getBaleogState() { return _baleogState; }
	void setBaleogState(BALEOGSTATE state) { _baleogState = state; }

	//벨로그 애니메이션 접근자 설정자
	animation* getBaleogMotion() {return _baleogMotion;}
	void setBaleogMotion(animation* motion) {_baleogMotion = motion;}
};

