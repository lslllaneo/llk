#include "pch.h"
#include "CGraph.h"

CGraph::CGraph(void)
{
	m_nVexnum = MAX_VERTEX_NUM;
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


void CGraph::AddVertex(Vertex v)
{
	m_Vertices[v.row * MAX_COL + v.col] = v.info;
}

int CGraph::GetVertex(int nIndex)
{
	return m_Vertices[nIndex];
}

void CGraph::AddArc(int nV1Index, int nV2Index)
{
	m_AdjMatrix[nV1Index][nV2Index] = true;
	m_AdjMatrix[nV2Index][nV1Index] = true;
}

int CGraph::Vexnum()
{
	return m_nVexnum;
}

void CGraph::UpdateVertex(int nIndex, int nInfo)
{
	m_Vertices[nIndex] = nInfo;
}

bool CGraph::GetArc(int nV1Index, int nV2Index)
{
	return m_AdjMatrix[nV1Index][nV2Index];
}

void CGraph::ClearGraph()
{
	for (int i = 0; i < MAX_VERTEX_NUM; i++)
	{
		m_Vertices[i] = -1;		//初始化顶点
		for (int j = 0; j < MAX_VERTEX_NUM; j++)
			m_AdjMatrix[i][j] = false;		//初始化边
	}
}
