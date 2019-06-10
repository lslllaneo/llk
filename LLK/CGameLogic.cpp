#include "afxdialogex.h"
#include "pch.h"
#include "CGameLogic.h"

CGameLogic::CGameLogic()
{
	m_nVexnum = 0;
	m_nCorner = 0;
}



void CGameLogic::InitMap(CGraph& graph)
{
	//游戏地图初始化，固定的值
	int anTemp[6][6] = { -1,-1,-1,-1,-1,-1,-1,2,0,1,3,-1,-1,2,2,1,3,-1,-1,2,1,0,0,-1,-1,1,3,0,3,-1,-1,-1,-1,-1,-1,-1 };
	for (int i = 0; i < 6; i++)
		for (int j = 0; j < 6; j++)
		{
			Vertex v;
			v.row = i;
			v.col = j;
			v.info = anTemp[i][j];
			graph.AddVertex(v);
		}
	for (int i = 0; i < 6; i++)
		for (int j = 0; j < 6; j++)
		{
			Vertex v;
			v.row = i;
			v.col = j;
			UpdateArc(graph, v);
		}
}

void CGameLogic::UpdateArc(CGraph& graph, Vertex v)
{
	int nV1Index = v.row * 6 + v.col;
	if (v.row > 0)
	{
		int nV2Index = nV1Index - 6;
		if (graph.GetVertex(nV1Index) == graph.GetVertex(nV2Index))
			graph.AddArc(nV1Index, nV2Index);
		if (graph.GetVertex(nV1Index) == BLANK)
			graph.AddArc(nV1Index, nV2Index);
	}
	if (v.col > 0)
	{
		int nV2Index = nV1Index - 1;
		if (graph.GetVertex(nV1Index) == graph.GetVertex(nV2Index))
			graph.AddArc(nV1Index, nV2Index);
		if (graph.GetVertex(nV1Index) == BLANK)
			graph.AddArc(nV1Index, nV2Index);
	}
	if (v.row < 5)
	{
		int nV2Index = nV1Index + 6;
		if (graph.GetVertex(nV1Index) == graph.GetVertex(nV2Index))
			graph.AddArc(nV1Index, nV2Index);
		if (graph.GetVertex(nV1Index) == BLANK)
			graph.AddArc(nV1Index, nV2Index);
	}
	if (v.col < 5)
	{
		int nV2Index = nV1Index + 1;
		if (graph.GetVertex(nV1Index) == graph.GetVertex(nV2Index))
			graph.AddArc(nV1Index, nV2Index);
		if (graph.GetVertex(nV1Index) == BLANK)
			graph.AddArc(nV1Index, nV2Index);
	}
}


bool CGameLogic::IsLink(CGraph& graph, Vertex v1, Vertex v2)
{
	
	int nV1 = v1.row * 6 + v1.col;
	int nV2 = v2.row * 6 + v2.col;
	PushVertex(nV1);
	return SearchPath(graph, nV1, nV2);
		

}


void CGameLogic::Clear(CGraph& graph, Vertex v1, Vertex v2)
{
	int nV1Index = v1.row * 6 + v1.col;
	int nV2Index = v2.row * 6 + v2.col;
	graph.UpdateVertex(nV1Index, BLANK);
	graph.UpdateVertex(nV2Index, BLANK);
	UpdateArc(graph, v1);
	UpdateArc(graph, v2);
}


int CGameLogic::GetVexPath(Vertex avPath[16])
{
	int i;
	for (i = 0; i < m_nVexnum; i++)
	{
		avPath[i].row = m_anPath[i] / 6;
		avPath[i].col = m_anPath[i] % 6;

	}
	m_nVexnum = 0;
	m_nCorner = 0;
	return i;
}

bool CGameLogic::IsBlank(CGraph& g)
{
	for (int i = 1; i < 5; i++)
		for (int j = 1; j < 5; j++)
		{
			int nIndex = i * 6 + j;
			if (g.GetVertex(nIndex) != -1)
				return false;
		}
	return true;
}


void CGameLogic::PushVertex(int n)
{
	m_anPath[m_nVexnum] = n;
	m_nVexnum++;
	
	if (IsCornor())
		m_nCorner++;
}

void CGameLogic::PopVertex()
{
	if (IsCornor())
		m_nCorner--;

	m_nVexnum--;
}



bool CGameLogic::SearchPath(CGraph graph, int nV1, int nV2)
{
	if ((graph.GetVertex(nV1) == BLANK) && (graph.GetVertex(nV2) == BLANK))
		return false;

	//得到顶点数
	int nVexnum = graph.Vexnum();

	//遍历图中nV1行，从0列到nVexnum列值为true的点
	int nVi;
	for (nVi = 0; nVi < nVexnum; nVi++)
	{
		if (graph.GetArc(nV1, nVi) && !IsExist(nVi))
		{
			PushVertex(nVi);
			
			if (m_nCorner > 2)
			{
				PopVertex();
				continue;
			}
							
			if (nVi != nV2)
			{
				//若中间顶点不为空
				if (graph.GetVertex(nVi) != BLANK)
				{
					PopVertex();
					continue;
				}
				//若nVi是一个已消除的顶点，则判断(nVi,nV2)是否连通
				if (SearchPath(graph, nVi, nV2))
				{
					return true;
				}
			}
			else //若nVi==nV2,表明已找到连通路径
			{
				return true;
			}
		}
	}
	PopVertex();
	return false;
}

bool CGameLogic::IsExist(int v)
{
	for (int i = 0; i < m_nVexnum; i++)
		if (m_anPath[i] == v)
			return true;
	return false;
}

bool CGameLogic::IsCornor()
{
	if (m_nVexnum < 3)
		return false;
	int v1 = m_anPath[m_nVexnum - 3];
	int v2 = m_anPath[m_nVexnum - 2];
	int v3 = m_anPath[m_nVexnum - 1];
	if (abs(v1 - v2) != abs(v2 - v3))
	{
		return true;
	}
	else 
		return false;
}

