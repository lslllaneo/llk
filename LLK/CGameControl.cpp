#include "pch.h"
#include "CGameControl.h"

void CGameControl::StartGame()
{
	CGameLogic gamelogic;
	gamelogic.InitMap(m_anMap);
}

int CGameControl::GetElement(int nRow, int nCol)
{

	return m_anMap[nRow][nCol];
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
	if ((m_svSelFirst.row == m_svSelSec.row) && (m_svSelFirst.col == m_svSelSec.col))
		return false;

	if (m_anMap[m_svSelFirst.row][m_svSelFirst.col] != m_anMap[m_svSelSec.row][m_svSelSec.col])
		return false;


	CGameLogic gamelogic;
	if (gamelogic.IsLink(m_anMap, m_svSelFirst, m_svSelSec))
	{
		nVexnum = gamelogic.GetVexPath(avPath);		
		gamelogic.Clear(m_anMap, m_svSelFirst, m_svSelSec);
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