#pragma once
#include "gameNode.h"
#include "arrow.h"

struct baleogPlayer
{
	float x, y;
	image* baleogImage;
	image* arrowImage;
	RECT baleogRc;
	float speed;
};


enum BALEOGSTATE //벨로그 상태
{
	BALEOG_RIGHT_STOP, //오른쪽 기본상태
	BALEOG_LEFT_STOP, //왼쪽 기본상태
	BALEOG_RIGHT_MOVE, //오른쪽 움직임
	BALEOG_LEFT_MOVE, //왼쪽 움직임
	BALEOG_UP_MOVE, //사다리 탈경우 위로 움직임
	BALEOG_DOWN_MOVE, //사다리 탈경우 아래로 움직임
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
	BALEOG_SPEED = 5,
};

class baleog : public gameNode
{
private:
	BALEOGSTATE _baleogState;
	baleogPlayer _baleogPlayer;
	
	arrow* _arrow;
	animation* _baleogMotion; //벨로그 모션 담아줄 빈 애니메이션

	int _rndAttack;

	bool _isLadderColision; //사다리 충돌했니
	bool _arrowFireStop;

public:
	baleog();
	~baleog();

	HRESULT init();
	void release();
	void update(float baleogX, float baleogY);
	void render();

	void keySetting(float baleogX, float baleogY); //키셋팅
	void arrowAttack(); //화살공격
	void swordAttack(); //검공격
	void arrowFire(); //모션이 취해질때 화살 발사할 함수

	//콜백함수 불러올 함수
	static void rightFire(void* obj);
	static void leftFire(void* obj);

public:
	//벨로그 상태 접근자 설정자
	BALEOGSTATE getBaleogState() { return _baleogState; }
	void setBaleogState(BALEOGSTATE state) { _baleogState = state; }

	//벨로그 애니메이션 접근자 설정자
	animation* getBaleogMotion() {return _baleogMotion;}
	void setBaleogMotion(animation* motion) {_baleogMotion = motion;}

	//사다리 충돌했는지 접근자 설정자
	bool getLadderCollision() {return _isLadderColision;}
	void setLadderCollision(bool collision) {_isLadderColision = collision;}
};

