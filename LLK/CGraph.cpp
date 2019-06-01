#include "pch.h"
#include "CGraph.h"

CGraph::CGraph(void)
{
}

CGraph::~CGraph(void)
{
}

void CGraph::InitGraph()
{
	for (int i = 0; i < MAX_VERTEX_NUM; i++)
	{
		m_Vertices[i] = -1;		//初始化顶点
		for (int j = 0; j < MAX_VERTEX_NUM; j++)
			m_AdjMatrix[i][j] = false;		//初始化边
	}
}

bool CGraph::GetVer(Vertex v1, Vertex v2)
{
	if (m_Vertices[v1.row * 4 + v1.col] == m_Vertices[v2.row * 4 + v2.col])
		return true;
	return false;
}

void CGraph::SetVertex(Vertex v)
{
	m_Vertices[v.row * 4 + v.col] = v.info;
}

void CGraph::GetInfo(Vertex& v)
{
	v.info = m_Vertices[v.row * 4 + v.col];
}
