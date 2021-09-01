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
	// ������ �̹� ������ ����ϰ� �ִٸ� �ٽ� ���� ���ϰ� �Ѵ�.
	if (m_bOpen)
		return false;
	//������ �����ش�.
	fopen_s(&m_pFile, pFileName, pMode);
	//������ ������ �ʾҴٸ� false�� ��ȯ
	if (!m_pFile)
		return false;

	//���� Ŀ���� ���� �ڷ� �̵���Ų��.
	//fseek �Լ��� ����Ŀ���� ���ϴ� ��ġ�� �̵���ų �� �ִ� �Լ��̴�.
	//3��° ���ڴ� 3������ �ִ�.
	//SEEK_SET : ������ ���� ó���� �ǹ�
	//SEEK_CUR : ������ ����Ŀ�� ��ġ
	//SEEK_END : ������ ������
	//2��° ������ offset�� ���� ����Ʈ ����ŭ 3��° ���ڿ��� ������
	//��ġ�κ��� �̵��ϰ� �ȴ�.
	fseek(m_pFile, 0, SEEK_END);
	//ftell : ����Ŀ���� ��ġ�� ������ �Լ��̴�. ������ ����Ŀ����
	//���� ���������� �̵����ױ� ������ ftell�� �̿��ؼ� ����Ŀ����
	//��ġ�� �� ������ ũ�Ⱑ �ǵ��� �Ͽ���.
	m_iFileSize = ftell(m_pFile);
	//�ٽ� ����ġ
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
	//������ �������� ������ ��� �Ұ�
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

	//feof�Լ��� ����Ŀ���� ������ ���� �����ߴ����� üũ�Ѵ�.
	//������ ���� �������� �ʾ��� ��� 0�� �����ϰ� ���� ���
	//0�� �ƴ� ���� �����Ѵ�.
	while (feof(m_pFile) == 0)
	{
		fread(&cData, 1, 1, m_pFile);
		//���� �����Ͱ� �����̸� �� ���� ��� �о��� ������ �ݺ����� �����Ѵ�.
		if (cData == '\n')
			break;

		//void���� �������� �Ұ����ϱ� ������ ����ȯ�� ���� �ٲ��ش�.
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

	//������ ���� ���๮��
	*(pBuffer + iSize) = '\n';
	//���ۿ� �����͸� �����Ѵ�. 
	//pData�� ���������� pBuffer�� pData�� �������̹Ƿ� 
	//pData == pBuffer �̴�.
	fwrite(pBuffer, iSize + 1 , 1, m_pFile);

	delete[] pBuffer;
}
