#pragma once

#include "global.h"
#include "CGraph.h"

class CGameLogic
{
protected:
	int m_anPath[36];						//保存连通路径的顶点索引
	int m_nCorner;		//保存路径数组m_anPath中的拐点数
	int m_nVexnum;        

public: 
	CGameLogic();
	void InitMap(CGraph& graph);
	void UpdateArc(CGraph& graph, Vertex v);				//判断v与其相邻顶点是否有边，有边则更新
	bool IsLink(CGraph& graph, int nV1, int nV2);		//判断两个图片是否可连接
	void Clear(CGraph& graph, Vertex v1, Vertex v2);		//若可连接则将顶点值置为空
	int GetVexPath(Vertex avPath[MAX_VERTEX_NUM]);		//获取得到路径avPath[4]，并通过参数返回给调用函数，通过返回值返回顶点数
	bool IsBlank(CGraph& g);
	bool SearchValidPath(CGraph& g);				//寻找可以连接的两点
	void ResetGraph(CGraph& g);		//重排

protected:
	void PushVertex(int n);		//添加一个路径顶点,并判断添加后是否形成一个拐点
	void PopVertex();		//取出一个顶点
	bool SearchPath(CGraph game, int nV1, int nV2);		//采用深度优先算法判断v1、v2是否连通
	bool IsExist(int v);		//判断索引为v的点是否保存在连通数组m_avPath中
	bool IsCornor();		//判断路径数组中的相邻三个点是否构成一个拐点
};
