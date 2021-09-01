#include "MapManager.h"
#include "Stage.h"
#include "CPlayer.h"
#include "CObjectManager.h"

CMapManager* CMapManager::m_pInst = NULL;

CMapManager::CMapManager()
{
	for (int i = 0; i < STAGE_MAX_COUNT; ++i)
	{
		m_pStage[i] = NULL;
	}
}

CMapManager::~CMapManager()
{
	// 스테이지 메모리 해제
	for (int i = 0; i < STAGE_MAX_COUNT; ++i)
	{
		SAFE_DELETE(m_pStage[i]);
	}
}

CMapManager * CMapManager::GetInst()
{
	if (!m_pInst)
		m_pInst = new CMapManager;

	return m_pInst;
}

void CMapManager::DestroyInst()
{
	SAFE_DELETE(m_pInst);
}

bool CMapManager::Init()
{
	char* pStageFile[3] = { "Stage1.txt","Stage2.txt","Stage3.txt" };

	for (int i = 0; i < STAGE_MAX_COUNT; ++i)
	{
		m_pStage[i] = new CStage;

		if (!m_pStage[i]->Init(pStageFile[i]))
			return false;
	}

	return true;
}

void CMapManager::Run()
{
	CPlayer* pPlayer = CObjectManager::GetInst()->GetPlayer();
	while (true) {
		m_iSelectStage = SelectStage();

		if (m_iSelectStage == 4)
			break;
		else if (m_iSelectStage == 0)
			continue;

		pPlayer->Update(m_pStage[m_iSelectStage]);

		m_pStage[m_iSelectStage - 1]->Render();

		Sleep(100);
	}
}

void CMapManager::Render(int iStageSelect)
{
	m_pStage[iStageSelect]->Render();
}

int CMapManager::SelectStage()
{
	cout << "1. stage1.txt" << endl;
	cout << "2. stage2.txt" << endl;
	cout << "3. stage3.txt" << endl;
	cout << "4. exit" << endl;
		
	m_iSelectStage = InputInt();
	return m_iSelectStage;
}
