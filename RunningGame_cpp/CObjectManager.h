#pragma once
#include "value.h"
class CObjectManager
{
	CObjectManager();
	~CObjectManager();

private:
	static CObjectManager* m_pInst;
public:
	static CObjectManager* GetInst() {
		if (!m_pInst)
			m_pInst = new CObjectManager;
		return m_pInst;
	}
	static void DestroyInst() {
		SAFE_DELETE(m_pInst);
	}
private:
	//가장 위에 하는 것이 아닌 해당타입을 사용하고자 할때 전방선언을
	//해줄 수도 있다.
	class CPlayer* m_pPlayer;

public:
	class CPlayer* GetPlayer() {
		return m_pPlayer;
	}

public:
	bool Init();
};

