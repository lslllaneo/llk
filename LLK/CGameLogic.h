#pragma once

#include "global.h"
#include "CGameControl.h"
#include "CGraph.h"

class CGameLogic
{
protected:
	Vertex m_avPath[4];		//保存在进行连接判断时所经过的顶点
	int m_VexNum;			//顶点数

public: 
	CGameLogic();
	void InitMap(CGraph& graph);
	bool IsLink(CGraph& graph, Vertex v1, Vertex v2);		//判断两个图片是否可连接
	void Clear(CGraph& graph, Vertex v1, Vertex v2);		//若可连接则将顶点值置为空
	int GetVexPath(Vertex avPath[4]);		//获取得到路径avPath[4]，并通过参数返回给调用函数，通过返回值返回顶点数

protected:
	void PushVertex();		//添加一个路径顶点
	void PopVertex();		//取出一个顶点
	//bool LinkInRow(int anMap[][4], Vertex v1, Vertex v2);		//判断横向是否连通
	//bool LinkInCol(int anMap[][4], Vertex v1, Vertex v2);		//判断纵向是否连通
	bool OneCornerLink(int anMap[][4], Vertex v1, Vertex v2);		//一个拐点连通判断
	bool TwoCornerLink(int anMap[][4], Vertex v1, Vertex v2);		//两个拐点连通判断
	//bool LintY(int anMap[][4], int nRow1, int nRow2, int nCol);		//直线连通Y轴
	//bool LintX(int anMap[][4], int nRow, int nCol1, int nCol2);		//直线连通X轴

};
