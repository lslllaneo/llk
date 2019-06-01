#pragma once

#include "global.h"
#include "CGameLogic.h"
#include "CGraph.h"

class CGameControl
{
protected:
	Vertex m_svSelFirst;		//ѡ�еĵ�һ����
	Vertex m_svSelSec;		//ѡ�еĵڶ�����
	CGraph m_graph;

public:
	void StartGame(void);
	int GetElement(int nRow, int nCol);
	void SetFirstPoint(int nRow, int nCol);		//���õ�һ����
	void SetSecPoint(int nRow, int nCol);		//���õڶ�����
	bool Link(Vertex avPath[4], int& nVexnum);		//�����жϺ���
	void GetFirstPoint(Vertex &v1);

};

