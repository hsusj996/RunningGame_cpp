#include "Core.h"
#include "MapManager.h"
#include "CObjectManager.h"
#include "CPlayer.h"

CCore* CCore::m_pInst = NULL;

// cpp 파일에는 클래스의 구현부분이 있다.
CCore::CCore()
{
}

CCore::~CCore()
{
	CMapManager::DestroyInst();
	CObjectManager::DestroyInst();
}

CCore* CCore::GetInst()
{
	if (!m_pInst)
		m_pInst = new CCore;
	
	return m_pInst;
}

void CCore::DestroyInst()
{
	SAFE_DELETE(m_pInst);
}

bool CCore::Init()
{
	// 맵 관리자를 초기화한다. 실패시 false를 리턴한다.
	if (!CMapManager::GetInst()->Init())
		return false;

	//오브젝트 관리자 초기화
	if (!CObjectManager::GetInst()->Init())
		return false;

	return true;
}

void CCore::Run()
{
	//CMapManager::GetInst()->Render();
	CPlayer* pPlayer = CObjectManager::GetInst()->GetPlayer();
	char* cStage;


	while (true) {
		system("cls");

		CMapManager::GetInst()->Run();
	}
}
