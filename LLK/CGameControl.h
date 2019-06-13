#pragma once

#include "global.h"
#include "CGameLogic.h"
#include "CGraph.h"

class CGameControl
{
protected:
	Vertex m_svSelFirst;		//选中的第一个点
	Vertex m_svSelSec;		//选中的第二个点
	CGraph m_graph;

public:
	void StartGame(void);
	int GetElement(int nRow, int nCol);
	void SetFirstPoint(int nRow, int nCol);		//设置第一个点
	void SetSecPoint(int nRow, int nCol);		//设置第二个点
	bool Link(Vertex avPath[MAX_VERTEX_NUM], int& nVexnum);		//连接判断函数
	void GetFirstPoint(Vertex &v1);
	BOOL IsWin(int nTime);
	bool Help(Vertex avPath[36], int& nVexnum);		//提示
	bool ResetGraph();			//重排游戏地图
};

