#include "Core.h"
#include "MapManager.h"
#include "CObjectManager.h"
#include "CPlayer.h"

CCore* CCore::m_pInst = NULL;

// cpp ���Ͽ��� Ŭ������ �����κ��� �ִ�.
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
	// �� �����ڸ� �ʱ�ȭ�Ѵ�. ���н� false�� �����Ѵ�.
	if (!CMapManager::GetInst()->Init())
		return false;

	//������Ʈ ������ �ʱ�ȭ
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
