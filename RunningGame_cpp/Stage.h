#pragma once

#include "value.h"

class CStage
{
public:
	CStage();
	~CStage();

public:
	// �� �Լ��� �׳� �ʱ�ȭ�� ������ �Լ��̴�.
	bool Init();

	// �� �Լ��� ���Ͽ��� ������ �о�ͼ� ������ ������ �Լ��̴�.
	bool Init(char* pFileName);
};

