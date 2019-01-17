#pragma once
#include "gameNode.h"

class menu : public gameNode
{
private:
	int _menuSelect_X, _menuSelect_Y;
	int _imageAlphaValue;

	bool _padeIn, _padeOut;					//���̵� ��, ���̵� �ƿ� ȿ�� 
	bool _menuGameStart;					//�޴� ���� ���� �Ұ�
	bool _opening;
public:
	menu();
	~menu();

	HRESULT init();
	void release();
	void update();
	void render();

	bool getMenuQuit() { return _menuGameStart; }
};

