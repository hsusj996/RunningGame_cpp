#pragma once

#include "value.h"

#define JUMP_BLOCK_MAX 3

enum JUMP_STATE {
	JS_UP,
	JS_STOP,
	JS_DOWN
};

class CPlayer
{
public:
	CPlayer();
	~CPlayer();

private:
	int m_iX;
	int m_iY;
	bool m_bJump;
	int m_iJumpPower;
	int m_eJumpState;
	int m_iJumpCount;
public:
	void SetPos(int x, int y) {
		m_iX = x;
		m_iY = y;
	}
public :
	int GetX() {
		return m_iX;
	}
	int GetY() {
		return m_iY;
	}
public:
	bool Init();
	void Update();
};


