#include "CObjectManager.h"
#include "CPlayer.h"

CObjectManager* CObjectManager::m_pInst = NULL;

CObjectManager::CObjectManager() :
	m_pPlayer(NULL)
{
}

CObjectManager::~CObjectManager()
{
}

bool CObjectManager::Init()
{
	m_pPlayer = new CPlayer;

	m_pPlayer->Init();

	return true;
}
