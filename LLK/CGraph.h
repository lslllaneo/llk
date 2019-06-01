#pragma once
#include "global.h"

class CGraph
{
public:
	CGraph(void);
	~CGraph(void);

#define MAX_VERTEX_NUM 16
	typedef int Vertices[MAX_VERTEX_NUM];
	typedef bool AdjMatrix[MAX_VERTEX_NUM][MAX_VERTEX_NUM];
	void InitGraph();
	bool GetVer(Vertex v1, Vertex v2);
	void SetVertex(Vertex v);
	void GetInfo(Vertex& v);

protected:
	Vertices m_Vertices;
	AdjMatrix m_AdjMatrix;
	int m_nVexnum;
	int m_nArcnum;

};

