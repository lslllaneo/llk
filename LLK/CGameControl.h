#pragma once

#include "global.h"
#include "CGameLogic.h"

class CGameControl
{
protected:
	int m_anMap[4][4];		//初始化游戏地图为4行、4列
	Vertex m_svSelFirst;		//选中的第一个点
	Vertex m_svSelSec;		//选中的第二个点

public:
	void StartGame(void);
	int GetElement(int nRow, int nCol);
	void SetFirstPoint(int nRow, int nCol);		//设置第一个点
	void SetSecPoint(int nRow, int nCol);		//设置第二个点
	bool Link();		//连接判断函数
	void GetFirstPoint(Vertex &v1);

};

