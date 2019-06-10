#pragma once
#include "global.h"

class CGraph
{
public:
	CGraph(void);
	~CGraph(void);

#define MAX_VERTEX_NUM 36
	typedef int Vertices[MAX_VERTEX_NUM];
	typedef bool AdjMatrix[MAX_VERTEX_NUM][MAX_VERTEX_NUM];
	void InitGraph();
	void AddVertex(Vertex v);					//设置顶点数组对应位置的元素信息
	int GetVertex(int nIndex);					//返回顶点元素信息
	void AddArc(int nV1Index, int nV2Index);		//若v1和v2之间连接，则置边关系矩阵相应位置为true
	int Vexnum();
	void UpdateVertex(int nIndex, int nInfo);
	bool GetArc(int nV1Index, int nV2Index);		
	void ClearGraph();

protected:
	Vertices m_Vertices;
	AdjMatrix m_AdjMatrix;
	int m_nVexnum;
	int m_nArcnum;

};

