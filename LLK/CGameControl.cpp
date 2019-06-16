#include "pch.h"
#include "CGameControl.h"

CGameControl::CGameControl()
{
}

CGameControl::~CGameControl()
{
}

BOOL CGameControl::IsWin(int nTime)
{
	CGameLogic gamelogic;
	if (nTime <= 0)
	{
		//清除图
		m_graph.ClearGraph();
		return GAME_LOSE;
	}

	if (gamelogic.IsBlank(m_graph))
	{
		m_graph.ClearGraph();
		return GAME_SUCCESS;
	}
	else
		return GAME_PLAY;
}

bool CGameControl::Help(Vertex avPath[36], int& nVexnum)
{
	CGameLogic gamelogic;
	if (gamelogic.IsBlank(m_graph))
		return false;

	if (gamelogic.SearchValidPath(m_graph))
	{
		nVexnum = gamelogic.GetVexPath(avPath);
		Vertex v1, v2;
		v1.row = avPath[0].row;
		v1.col = avPath[0].col;
		v2.row = avPath[nVexnum - 1].row;
		v2.col = avPath[nVexnum - 1].col;
		gamelogic.Clear(m_graph, v1, v2);
		return true;
	}
	return false;
}

bool CGameControl::ResetGraph()
{

	CGameLogic logic;
	logic.ResetGraph(m_graph);
	return true;
}

int CGameControl::GetElement(int nRow, int nCol)
{
	int nInfo, nIndex;
	nIndex = MAX_COL * nRow + nCol;
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
bool CGameControl::Link(Vertex avPath[MAX_VERTEX_NUM], int& nVexnum)
{
	//两点是否连通
	if ((m_svSelFirst.row == m_svSelSec.row) && (m_svSelFirst.col == m_svSelSec.col))		//判断是否是同一个顶点
		return false;

	int nV1Index = m_svSelFirst.row * MAX_COL + m_svSelFirst.col;
	int nV2Index = m_svSelSec.row * MAX_COL + m_svSelSec.col;

	if (m_graph.GetVertex(nV1Index) != m_graph.GetVertex(nV2Index))		//判断两点图形是否一致
		return false;

	CGameLogic gamelogic;

	if (gamelogic.IsLink(m_graph, nV1Index, nV2Index))
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

void CGameControl::SetGameFlag(Flag flag)
{
	m_flag = flag;
}

Flag CGameControl::GetGameFlag()
{
	return m_flag;
}


