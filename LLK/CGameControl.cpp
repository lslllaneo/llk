#include "pch.h"
#include "CGameControl.h"

void CGameControl::StartGame()
{
	CGameLogic gamelogic;
	gamelogic.InitMap(m_graph);
}

int CGameControl::GetElement(int nRow, int nCol)
{
	int nInfo, nIndex;
	nIndex = 6 * nRow + nCol;
	nInfo = m_graph.GetVertex(nIndex);
	return nInfo;
}
void CGameControl::SetFirstPoint(int nRow, int nCol)
{
	m_svSelFirst.row = nRow;
	m_svSelFirst.col = nCol;
}

void CGameControl::SetSecPoint(int nRow, int nCol)
{
	m_svSelSec.row = nRow;
	m_svSelSec.col = nCol;
}
bool CGameControl::Link(Vertex avPath[36], int& nVexnum)
{
	//两点是否连通
	if ((m_svSelFirst.row == m_svSelSec.row) && (m_svSelFirst.col == m_svSelSec.col))		//判断是否是同一个顶点
		return false;

	int nV1Index = m_svSelFirst.row * 6 + m_svSelFirst.col;
	int nV2Index = m_svSelSec.row * 6 + m_svSelSec.col;

	if (m_graph.GetVertex(nV1Index) != m_graph.GetVertex(nV2Index))		//判断两点图形是否一致
		return false;

	CGameLogic gamelogic;
	if (gamelogic.IsLink(m_graph, m_svSelFirst, m_svSelSec))
	{ 
		nVexnum = gamelogic.GetVexPath(avPath);		
		gamelogic.Clear(m_graph, m_svSelFirst, m_svSelSec);
		return true;
	}
	return false;
}

void CGameControl::GetFirstPoint(Vertex& v1)
{
	v1.row = m_svSelFirst.row;
	v1.col = m_svSelFirst.col;
	v1.info = m_svSelFirst.info;
}

bool CGameControl::IsWin()
{
	CGameLogic gamelogic;
	if (gamelogic.IsBlank(m_graph))
	{
		m_graph.ClearGraph();
		return true;
	}
	else 
		return false;
}
