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

//stage 클래스의 초기
//텍스트파일로 부터 데이터를 읽어온다.
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
	//맵은 스크롤 처리를 해야 한다.
	//플레이어가 이동한 위치로 부터 맵을 출력
	//출력 크기는 세로 4칸 가로 10칸
	// 0 : 벽, 1 : 길, 2 : 시작점, 3 : 도착점, 4 : 코인
	CPlayer* pPlayer = CObjectManager::GetInst()->GetPlayer();
	//플레이어의 x,y 좌표를 얻어온다.
	int iX = pPlayer->GetX();
	int iY = pPlayer->GetY();
	//맵의 출력은 플레이어의 위치를 중심으로 출력한다.
	for (int i = iY - 2;i <=  iY + 1;i++)
	{
		for (int j = iX;j < iX + 10;j++)
		{
			if (i == iY && j == iX)
				cout << "★";
			else if (m_cStage[i][j] == SBT_WALL)
				cout << "■";
			else if (m_cStage[i][j] == SBT_ROAD)
				cout << "  ";
			else if (m_cStage[i][j] == SBT_START)
				cout << "◎";
			else if (m_cStage[i][j] == SBT_END)
				cout << "▼";
			else if (m_cStage[i][j] == SBT_COIN)
				cout << "＠";
		}
		cout << endl;
	}
}