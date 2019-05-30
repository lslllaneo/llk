#pragma once

#include "global.h"
#include "CGameLogic.h"

class CGameControl
{
protected:
	int m_anMap[4][4];		//��ʼ����Ϸ��ͼΪ4�С�4��
	Vertex m_svSelFirst;		//ѡ�еĵ�һ����
	Vertex m_svSelSec;		//ѡ�еĵڶ�����

public:
	void StartGame(void);
	int GetElement(int nRow, int nCol);
	void SetFirstPoint(int nRow, int nCol);		//���õ�һ����
	void SetSecPoint(int nRow, int nCol);		//���õڶ�����
	bool Link();		//�����жϺ���
	void GetFirstPoint(Vertex &v1);

};

