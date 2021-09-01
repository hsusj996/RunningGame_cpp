#include "CFileStream.h"

CFileStream::CFileStream() :
	m_pFile(NULL),
	m_iFileSize(0),
	m_bOpen(false)
{
}

CFileStream::~CFileStream()
{
	Close();
}

bool CFileStream::Open(char* pFileName, char* pMode)
{
	// 파일이 이미 열려서 사용하고 있다면 다시 열지 못하게 한다.
	if (m_bOpen)
		return false;
	//파일을 열어준다.
	fopen_s(&m_pFile, pFileName, pMode);
	//파일이 열리지 않았다면 false를 반환
	if (!m_pFile)
		return false;

	//파일 커서를 가장 뒤로 이동시킨다.
	//fseek 함수는 파일커서를 원하는 위치로 이동시킬 수 있는 함수이다.
	//3번째 인자는 3종류가 있다.
	//SEEK_SET : 파일의 제일 처음을 의미
	//SEEK_CUR : 파일의 현재커서 위치
	//SEEK_END : 파일의 마지막
	//2번째 인자인 offset에 들어가는 바이트 수만큼 3번째 인자에서 지정한
	//위치로부터 이동하게 된다.
	fseek(m_pFile, 0, SEEK_END);
	//ftell : 파일커서의 위치를 얻어오는 함수이다. 위에서 파일커서를
	//가장 마지막으로 이동시켰기 때문에 ftell을 이용해서 파일커서의
	//위치가 곧 파일의 크기가 되도록 하였다.
	m_iFileSize = ftell(m_pFile);
	//다시 원위치
	fseek(m_pFile, 0, SEEK_SET);

	m_bOpen = true;

	return true;
}

bool CFileStream::Close()
{
	if (!m_bOpen)
		return false;

	m_bOpen = false;

	fclose(m_pFile);
	m_iFileSize = 0;
	m_pFile = NULL;

	return true;
}

void CFileStream::Read(void* pData, int iSize)
{
	//파일이 열려있지 않으면 기능 불가
	if (!m_bOpen)
		return;
	
	fread(pData, iSize, 1, m_pFile);
}

void CFileStream::ReadLine(void* pData, int& iSize)
{
	if (!m_bOpen)
		return;

	char cData;
	char* pChangeData = (char*)pData;
	iSize = 0;

	//feof함수는 파일커서가 파일의 끝에 도달했는지를 체크한다.
	//파일의 끝에 도달하지 않았을 경우 0을 리턴하고 끝일 경우
	//0이 아닌 수를 리턴한다.
	while (feof(m_pFile) == 0)
	{
		fread(&cData, 1, 1, m_pFile);
		//읽은 데이터가 개행이면 한 줄을 모두 읽었기 때문에 반복문을 종료한다.
		if (cData == '\n')
			break;

		//void형은 역참조가 불가능하기 때문에 형변환을 통해 바꿔준다.
		pChangeData[iSize] = cData;
		iSize++;
	}
}

void CFileStream::Write(void* pData, int iSize)
{
	if (!m_bOpen)
		return;

	fwrite(pData, iSize, 1, m_pFile);
}

void CFileStream::WriteLine(void* pData, int iSize)
{
	if (!m_bOpen)
		return;

	char* pBuffer = new char[iSize + 1];

	//버퍼의 끝은 개행문자
	*(pBuffer + iSize) = '\n';
	//버퍼에 데이터를 저장한다. 
	//pData에 저장했지만 pBuffer는 pData의 포인터이므로 
	//pData == pBuffer 이다.
	fwrite(pBuffer, iSize + 1 , 1, m_pFile);

	delete[] pBuffer;
}
