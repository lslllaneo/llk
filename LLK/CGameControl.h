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
	void SetFirstPoint(int nRow, int nCol);		//设置第一个点
	void SetSecPoint(int nRow, int nCol);		//设置第二个点
	bool Link(Vertex avPath[MAX_VERTEX_NUM], int& nVexnum);		//连接判断函数
	void GetFirstPoint(Vertex& v1);

protected:
	Flag m_flag;
	int nScore;
	CGraph m_graph;
	Vertex m_svSelFirst;		//选中的第一个点
	Vertex m_svSelSec;		//选中的第二个点
};

