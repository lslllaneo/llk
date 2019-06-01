#include "pch.h"
#include "CGameControl.h"

void CGameControl::StartGame()
{
	CGameLogic gamelogic;
	gamelogic.InitMap(m_graph);
}

int CGameControl::GetElement(int nRow, int nCol)
{
	Vertex v;
	v.row = nRow;
	v.col = nCol;
	m_graph.GetInfo(v);
	return v.info;
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
bool CGameControl::Link(Vertex avPath[4], int &nVexnum)
{
	//两点是否连通
	if ((m_svSelFirst.row == m_svSelSec.row) && (m_svSelFirst.col == m_svSelSec.col))		//判断是否是同一个顶点
		return false;

	if (m_graph.GetVer(m_svSelFirst, m_svSelSec))		//判断两点图形是否一致
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