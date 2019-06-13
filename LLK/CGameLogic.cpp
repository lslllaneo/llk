#include "afxdialogex.h"
#include "pch.h"
#include "CGameLogic.h"
#include <cmath>

CGameLogic::CGameLogic()
{
	m_nVexnum = 0;
	m_nCorner = 0;
}



void CGameLogic::InitMap(CGraph& graph)
{
	//游戏地图初始化，固定的值
	int anTemp[MAX_VERTEX_NUM];
	for (int i = 0; i < MAX_VERTEX_NUM; i++)
		anTemp[i] = BLANK;

	srand((int)time(NULL));

	//多少花色
	for (int i = 1; i <= MAX_PIC_NUM; i++)
	{
		//每种花色的重复数
		for (int j = 1; j <= REPEAT_NUM; j++)
		{
			anTemp[i * MAX_COL + j] = i - 1;
		}
	}

	for (int i = 1; i <= MAX_PIC_NUM; i++)
	{
		//每种花色的重复数
		for (int j = 1; j <= REPEAT_NUM; j++)
		{
			int nIndex1;
			int nIndex2;

			while (true)
			{
				nIndex1 = rand() % MAX_VERTEX_NUM;
				int row, col;
				row = nIndex1 / MAX_COL;
				col = nIndex1 % MAX_COL;
				if ((row == 0 || row == MAX_ROW - 1))
					continue;
				if ((col == 0 || col == MAX_COL - 1))
					continue;
				break;
			}

			while (true)
			{
				nIndex2 = rand() % MAX_VERTEX_NUM;
				int row, col;
				row = nIndex2 / MAX_COL;
				col = nIndex2 % MAX_COL;
				if ((row == 0 )||( row == MAX_ROW - 1))
					continue;
				if ((col == 0) || (col == MAX_COL - 1))
					continue;
				break;
			}

			int nTemp = anTemp[nIndex1];
			anTemp[nIndex1] = anTemp[nIndex2];
			anTemp[nIndex2] = nTemp;
		}
	}

	for (int i = 0; i < MAX_ROW; i++)
		for (int j = 0; j < MAX_COL; j++)
		{
			Vertex v;
			v.row = i;
			v.col = j;
			v.info = anTemp[i * MAX_COL + j];
			graph.AddVertex(v);
		}
	for (int i = 0; i < MAX_ROW; i++)
		for (int j = 0; j < MAX_COL; j++)
		{
			Vertex v;
			v.row = i;
			v.col = j;
			UpdateArc(graph, v);
		}
}

void CGameLogic::ResetGraph(CGraph& g)
{
	srand((int)time(NULL));

	for (int j = 1; j <= 100; j++)
	{
		int nIndex1;
		int nIndex2;

		while (true)
		{
			nIndex1 = rand() % MAX_VERTEX_NUM;
			int row, col;
			row = nIndex1 / MAX_COL;
			col = nIndex1 % MAX_COL;
			if ((row == 0 || row == MAX_ROW - 1))
				continue;
			if ((col == 0 || col == MAX_COL - 1))
				continue;
			break;
		}

		while (true)
		{
			nIndex2 = rand() % MAX_VERTEX_NUM;
			int row, col;
			row = nIndex2 / MAX_COL;
			col = nIndex2 % MAX_COL;
			if ((row == 0) || (row == MAX_ROW - 1))
				continue;
			if ((col == 0) || (col == MAX_COL - 1))
				continue;
			break;
		}

		int nTemp = g.GetVertex(nIndex1);
		Vertex v;
		v.row = nIndex1 / MAX_COL;
		v.col = nIndex1 % MAX_COL;
		v.info = g.GetVertex(nIndex2);
		g.AddVertex(v);
		v.row = nIndex2 / MAX_COL;
		v.col = nIndex2 % MAX_COL;
		v.info = nTemp;
		g.AddVertex(v);
		}

}

void CGameLogic::UpdateArc(CGraph& graph, Vertex v)
{
	int nV1Index = v.row * MAX_COL + v.col;
	if (v.row > 0)
	{
		int nV2Index = nV1Index - MAX_COL;
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
	if (v.row < MAX_ROW - 1)
	{
		int nV2Index = nV1Index + MAX_COL;
		if (graph.GetVertex(nV1Index) == graph.GetVertex(nV2Index))
			graph.AddArc(nV1Index, nV2Index);
		if (graph.GetVertex(nV1Index) == BLANK)
			graph.AddArc(nV1Index, nV2Index);
	}
	if (v.col < MAX_COL - 1)
	{
		int nV2Index = nV1Index + 1;
		if (graph.GetVertex(nV1Index) == graph.GetVertex(nV2Index))
			graph.AddArc(nV1Index, nV2Index);
		if (graph.GetVertex(nV1Index) == BLANK)
			graph.AddArc(nV1Index, nV2Index);
	}
}


bool CGameLogic::IsLink(CGraph& graph, int nV1, int nV2)
{
	
	PushVertex(nV1);
	return SearchPath(graph, nV1, nV2);
		

}


void CGameLogic::Clear(CGraph& graph, Vertex v1, Vertex v2)
{
	int nV1Index = v1.row * MAX_COL + v1.col;
	int nV2Index = v2.row * MAX_COL + v2.col;
	graph.UpdateVertex(nV1Index, BLANK);
	graph.UpdateVertex(nV2Index, BLANK);
	UpdateArc(graph, v1);
	UpdateArc(graph, v2);
}


int CGameLogic::GetVexPath(Vertex avPath[MAX_VERTEX_NUM])
{
	int i;
	for (i = 0; i < m_nVexnum; i++)
	{
		avPath[i].row = m_anPath[i] / MAX_COL;
		avPath[i].col = m_anPath[i] % MAX_COL;

	}
	m_nVexnum = 0;
	m_nCorner = 0;
	return i;
}

bool CGameLogic::IsBlank(CGraph& g)
{
	for (int i = 1; i < MAX_ROW - 1; i++)
		for (int j = 1; j < MAX_COL - 1; j++)
		{
			int nIndex = i * MAX_COL + j;
			if (g.GetVertex(nIndex) != -1)
				return false;
		}
	return true;
}

bool CGameLogic::SearchValidPath(CGraph& g)
{
	int nVexnum = g.Vexnum();
	for (int i = 0; i < nVexnum; i++)
	{
		if (g.GetVertex(i) == BLANK)	continue;
		for (int j = i + 1; j < nVexnum; j++)
		{
			if (g.GetVertex(j) == BLANK)	continue;
			if (g.GetVertex(j) == g.GetVertex(i))
			{
				if (IsLink(g, i, j))
					return true;
			}
		}
	}
	return false;
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

