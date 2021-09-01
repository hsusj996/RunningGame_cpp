#include "Stage.h"
#include "CFileStream.h"
#include "CPlayer.h"
#include "CObjectManager.h"

enum STAGE_BLOCK_TYPE {
	SBT_WALL = '0',
	SBT_ROAD = '1',
	SBT_START = '2',
	SBT_END = '3',
	SBT_COIN = '4'
};

CStage::CStage()
{
}

CStage::~CStage()
{
}

bool CStage::Init()
{
	return true;
}

//stage Ŭ������ �ʱ�
//�ؽ�Ʈ���Ϸ� ���� �����͸� �о�´�.
bool CStage::Init(char * pFileName)
{
	CFileStream file;

	if (!file.Open(pFileName, "rt"))
		return false;

	for (int i = 0;i < 10;i++)
	{
		int iSize = 0;
		file.ReadLine(m_cStage[i], iSize);
	}

	return true;
}

void CStage::Render()
{
	//���� ��ũ�� ó���� �ؾ� �Ѵ�.
	//�÷��̾ �̵��� ��ġ�� ���� ���� ���
	//��� ũ��� ���� 4ĭ ���� 10ĭ
	// 0 : ��, 1 : ��, 2 : ������, 3 : ������, 4 : ����
	CPlayer* pPlayer = CObjectManager::GetInst()->GetPlayer();
	//�÷��̾��� x,y ��ǥ�� ���´�.
	int iX = pPlayer->GetX();
	int iY = pPlayer->GetY();
	//���� ����� �÷��̾��� ��ġ�� �߽����� ����Ѵ�.
	for (int i = iY - 2;i <=  iY + 1;i++)
	{
		for (int j = iX;j < iX + 10;j++)
		{
			if (i == iY && j == iX)
				cout << "��";
			else if (m_cStage[i][j] == SBT_WALL)
				cout << "��";
			else if (m_cStage[i][j] == SBT_ROAD)
				cout << "  ";
			else if (m_cStage[i][j] == SBT_START)
				cout << "��";
			else if (m_cStage[i][j] == SBT_END)
				cout << "��";
			else if (m_cStage[i][j] == SBT_COIN)
				cout << "��";
		}
		cout << endl;
	}
}