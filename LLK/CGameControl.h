#pragma once

#include "global.h"
#include "CGameLogic.h"
#include "CGraph.h"

class CGameControl
{
public:
	CGameControl();
	~CGameControl();
	virtual BOOL IsWin(int nTime);
	virtual bool Help(Vertex avPath[36], int& nVexnum);
	virtual bool ResetGraph();
	void SetGameFlag(Flag flag);
	Flag GetGameFlag();
	virtual void StartGame() = 0;
	int GetElement(int nRow, int nCol);
	void SetFirstPoint(int nRow, int nCol);		//���õ�һ����
	void SetSecPoint(int nRow, int nCol);		//���õڶ�����
	bool Link(Vertex avPath[MAX_VERTEX_NUM], int& nVexnum);		//�����жϺ���
	void GetFirstPoint(Vertex& v1);

protected:
	Flag m_flag;
	int nScore;
	CGraph m_graph;
	Vertex m_svSelFirst;		//ѡ�еĵ�һ����
	Vertex m_svSelSec;		//ѡ�еĵڶ�����
};

