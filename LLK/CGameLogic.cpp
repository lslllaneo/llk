#include "afxdialogex.h"
#include "pch.h"
#include "CGameLogic.h"

CGameLogic::CGameLogic()
{
	m_VexNum = 0;
}



void CGameLogic::InitMap(CGraph& graph)
{
	//游戏地图初始化，固定的值
	int anTemp[4][4] = { 2,0,1,3,2,2,1,3,2,1,0,0,1,3,0,3 };
	/*for (int i = 0; i < 4; i++)
		for (int j = 0; j < 4; j++)
			anMap[i][j] = anTemp[i][j];*/
}


bool CGameLogic::IsLink(CGraph& graph, Vertex v1, Vertex v2)
{
	/*
	//一条直线连通
	int nRow1 = v1.row;
	int nCol1 = v1.col;
	int nRow2 = v2.row;
	int nCol2 = v2.col;
	//行号相同时是否连通
	if (nRow1 == nRow2)
	{
		if (LinkInRow(anMap, v1, v2))
		{
			m_VexNum = 2;
			m_avPath[0] = v1;
			m_avPath[1] = v2;
			return true;
		}
	}
	//列号相同时是否连通
	if (nCol1 == nCol2)
	{
		if (LinkInCol(anMap, v1, v2))
		{
			m_VexNum = 2;
			m_avPath[0] = v1;
			m_avPath[1] = v2;
			return true;
		}
	}


	//两条直线连通
	if (OneCornerLink(anMap, v1, v2))
	{
		m_VexNum = 3;
		m_avPath[0] = v1;
		m_avPath[2] = v2;
		return true;
	}
		

	//三条直线连通
	if (TwoCornerLink(anMap, v1, v2))
	{
		m_VexNum = 4;
		if (v2.row >= v1.row)
		{
			m_avPath[0] = v1;
			m_avPath[3] = v2;
		}
		else
		{
			m_avPath[3] = v1;
			m_avPath[0] = v2;
		}
		return true;
	}*/

		

	return false;
}


void CGameLogic::Clear(CGraph& graph, Vertex v1, Vertex v2)
{
	
}

int CGameLogic::GetVexPath(Vertex avPath[4])
{
	for (int i = 0; i < m_VexNum; i++)
		avPath[i] = m_avPath[i];
	return m_VexNum;
}

void CGameLogic::PushVertex()
{
}

void CGameLogic::PopVertex()
{
}

bool CGameLogic::LinkInRow(int anMap[][4], Vertex v1, Vertex v2)
{
	int nRow = v1.row;
	int nCol1 = v1.col;
	int nCol2 = v2.col;

	//保证nCol1小于nCol2
	if (nCol1 > nCol2)
	{
		int nTemp = nCol1;
		nCol1 = nCol2;
		nCol2 = nTemp;
	}

	//直通
	for (int i = nCol1 + 1; i <= nCol2; i++)
	{
		if (i == nCol2)
			return true;
		if (anMap[nRow][i] != BLANK)
			break;
	}

	return false;
}

bool CGameLogic::LinkInCol(int anMap[][4], Vertex v1, Vertex v2)
{
	int nRow1 = v1.row;
	int nCol = v1.col;
	int nRow2 = v2.row;

	//保证nRow1小于nRow2
	if (nRow1 > nRow2)
	{
		int nTemp = nRow1;
		nRow1 = nRow2;
		nRow2 = nTemp;
	}
	 
	//直通
	for (int i = nRow1 + 1; i <= nRow2; i++)
	{
		if (i == nRow2)
			return true;
		if (anMap[i][nCol] != BLANK)
			break;
	}

	return false;
}

bool CGameLogic::OneCornerLink(int anMap[][4], Vertex v1, Vertex v2)
{
	int nRow1;
	int nCol1;
	int nRow2;
	int nCol2;
	bool k = false;
	
	if (v2.row >= v1.row)
	{
		nRow1 = v1.row;
		nCol1 = v1.col;
		nRow2 = v2.row;
		nCol2 = v2.col;
	}
	else
	{
		nRow1 = v2.row;
		nCol1 = v2.col;
		nRow2 = v1.row;
		nCol2 = v1.col;
	}

	if (nCol2 >= nCol1)
	{
		if (LintX(anMap, nRow1, nCol1, nCol2) && anMap[nRow1][nCol2] == BLANK)
			if (LintY(anMap, nRow1, nRow2, nCol2))
			{
				m_VexNum = 3;				
				m_avPath[1].col = nCol2;
				m_avPath[1].row = nRow1;
				return true;
			}
				
			else
				k = false;
		else
			k = false;

		if (LintY(anMap, nRow1, nRow2, nCol1) && anMap[nRow2][nCol1] == BLANK)
			if (LintX(anMap, nRow2, nCol1, nCol2))
			{
				m_VexNum = 3;
				m_avPath[1].row = nRow2;
				m_avPath[1].col = nCol1;
				return true;
			}
			else return false;
		return false;
	}
	else {
		if (LintY(anMap, nRow1, nRow2, nCol1) && anMap[nRow2][nCol1] == BLANK)
			if (LintX(anMap, nRow2, nCol2, nCol1))
			{
				m_VexNum = 3;
				m_avPath[1].row = nRow2;
				m_avPath[1].col = nCol1;
				return true;
			}
			else
				k = false;
		else
			k = false;

		if (LintX(anMap, nRow1, nCol2, nCol1) && anMap[nRow1][nCol2] == BLANK)
			if (LintY(anMap, nRow1, nRow2, nCol2))
			{
				m_VexNum = 3;
				m_avPath[1].col = nCol2;
				m_avPath[1].row = nRow1;
				return true;
			}
			else 
				return false;
		return false;
	}

	return false;
}

bool CGameLogic::TwoCornerLink(int anMap[][4], Vertex v1, Vertex v2)
{
	int nRow1;
	int nCol1;
	int nRow2;
	int nCol2;
	bool k = false;

	if (v2.row >= v1.row)
	{
		nRow1 = v1.row;
		nCol1 = v1.col;
		nRow2 = v2.row;
		nCol2 = v2.col;
	}
	else
	{
		nRow1 = v2.row;
		nCol1 = v2.col;
		nRow2 = v1.row;
		nCol2 = v1.col;
	}

	if (nCol2 > nCol1)
	{
		for (int i = nRow1 + 1; i < nRow2; i++)
			if (LintX(anMap, i, nCol1 - 1, nCol2 + 1))
				if (LintY(anMap, nRow1, i, nCol1))
					if (LintY(anMap, i, nRow2, nCol2))
					{
						m_avPath[1].col = nCol1;
						m_avPath[1].row = i;
						m_avPath[2].col = nCol2;
						m_avPath[2].row = i;
						return true;
					}

		for (int i = nCol1 + 1; i < nCol2; i++)
			if (LintY(anMap, nRow1 - 1, nRow2 + 1, i))
				if (LintX(anMap, nRow1, nCol1, i))
					if (LintY(anMap, nRow2, i, nCol2))
					{
						m_avPath[1].col = i;
						m_avPath[1].row = nRow1;
						m_avPath[2].col = i;
						m_avPath[2].row = nRow2;
						return true;
					}

		for (int i = nRow1 - 1; i >= -1; i--)
		{
			if (i == -1)
				if (LintY(anMap, -1, nRow1, nCol1))
					if (LintY(anMap, -1, nRow2, nCol2))
					{
						m_avPath[1].col = nCol1;
						m_avPath[1].row = -1;
						m_avPath[2].col = nCol2;
						m_avPath[2].row = -1;
						return true;
					}

			if (LintX(anMap, i, nCol1 - 1, nCol2 + 1))
				if (LintY(anMap, i, nRow1, nCol1))
					if (LintY(anMap, i, nRow2, nCol2))
					{
						m_avPath[1].col = nCol1;
						m_avPath[1].row = i;
						m_avPath[2].col = nCol2;
						m_avPath[2].row = i;
						return true;
					}
		}

		for (int i = nRow2 + 1; i <= 4; i++)
		{
			if (i == 4)
				if (LintY(anMap, nRow1, 4, nCol1))
					if (LintY(anMap, nRow2, 4, nCol2))
					{
						m_avPath[1].col = nCol1;
						m_avPath[1].row = 4;
						m_avPath[2].col = nCol2;
						m_avPath[2].row = 4;
						return true;
					}

			if (LintX(anMap, i, nCol1 - 1, nCol2 + 1))
				if (LintY(anMap, nRow1, i, nCol1))
					if (LintY(anMap, nRow2, i, nCol2))
					{
						m_avPath[1].col = nCol1;
						m_avPath[1].row = i;
						m_avPath[2].col = nCol2;
						m_avPath[2].row = i;
						return true;
					}
		}

		for (int i = nCol1 - 1; i >= -1; i--)
		{
			if (i == -1)
				if (LintX(anMap, nRow1, -1, nCol1))
					if (LintX(anMap, nRow2, -1, nCol2))
					{
						m_avPath[1].col = -1;
						m_avPath[1].row = nRow1;
						m_avPath[2].col = -1;
						m_avPath[2].row = nRow2;
						return true;
					}

			if (LintY(anMap, nRow1 - 1, nRow2 + 1, i))
				if (LintX(anMap, nRow1, i, nCol1))
					if (LintX(anMap, nRow2, i, nCol2))
					{
						m_avPath[1].col = i;
						m_avPath[1].row = nRow1;
						m_avPath[2].col = i;
						m_avPath[2].row = nRow2;
						return true;
					}
		}

		for (int i = nCol2 + 1; i <= 4; i++)
		{
			if (i == 4)
				if (LintX(anMap, nRow1, nCol1, 4))
					if (LintX(anMap, nRow2, nCol2, 4))
					{
						m_avPath[1].col = 4;
						m_avPath[1].row = nRow1;
						m_avPath[2].col = 4;
						m_avPath[2].row = nRow2;
						return true;
					}

			if (LintY(anMap, nRow1 - 1, nRow2 + 1, i))
				if (LintX(anMap, nRow1, nCol1, i))
					if (LintX(anMap, nRow2, nCol2, i))
					{
						m_avPath[1].col = i;
						m_avPath[1].row = nRow1;
						m_avPath[2].col = i;
						m_avPath[2].row = nRow2;
						return true;
					}
		}
	}
	else
	{
		for (int i = nRow1 + 1; i < nRow2; i++)
			if (LintX(anMap, i, nCol2 - 1, nCol1 + 1))
				if (LintY(anMap, nRow1, i, nCol1))
					if (LintY(anMap, i, nRow2, nCol2))
					{
						m_avPath[1].col = nCol1;
						m_avPath[1].row = i;
						m_avPath[2].col = nCol2;
						m_avPath[2].row = i;
						return true;
					}

		for (int i = nCol2 + 1; i < nCol1; i++)
			if (LintY(anMap, nRow1 - 1, nRow2 + 1, i))
				if (LintX(anMap, nRow2, nCol2, i))
					if (LintY(anMap, nRow1, i, nCol1))
					{
						m_avPath[1].col = i;
						m_avPath[1].row = nRow1;
						m_avPath[2].col = i;
						m_avPath[2].row = nRow2;
						return true;
					}

		for (int i = nRow1 - 1; i >= -1; i--)
		{
			if (i == -1)
				if (LintY(anMap, -1, nRow1, nCol1))
					if (LintY(anMap, -1, nRow2, nCol2))
					{
						m_avPath[1].col = nCol1;
						m_avPath[1].row = -1;
						m_avPath[2].col = nCol2;
						m_avPath[2].row = -1;
						return true;
					}

			if (LintX(anMap, i, nCol2 - 1, nCol1 + 1))
				if (LintY(anMap, i, nRow1, nCol1))
					if (LintY(anMap, i, nRow2, nCol2))
					{
						m_avPath[1].col = nCol1;
						m_avPath[1].row = i;
						m_avPath[2].col = nCol2;
						m_avPath[2].row = i;
						return true;
					}

		}

		for (int i = nRow2 + 1; i <= 4; i++)
		{
			if (i == 4)
				if (LintY(anMap, nRow1, 4, nCol1))
					if (LintY(anMap, nRow2, 4, nCol2))
					{
						m_avPath[1].col = nCol1;
						m_avPath[1].row = 4;
						m_avPath[2].col = nCol2;
						m_avPath[2].row = 4;
						return true;
					}

			if (LintX(anMap, i, nCol2 - 1, nCol1 + 1))
				if (LintY(anMap, nRow1, i, nCol1))
					if (LintY(anMap, nRow2, i, nCol2))
					{
						m_avPath[1].col = nCol1;
						m_avPath[1].row = i;
						m_avPath[2].col = nCol2;
						m_avPath[2].row = i;
						return true;
					}
		}

		for (int i = nCol2 - 1; i >= -1; i--)
		{
			if (i == -1)
				if (LintX(anMap, nRow1, -1, nCol1))
					if (LintX(anMap, nRow2, -1, nCol2))
					{
						m_avPath[1].col = -1;
						m_avPath[1].row = nRow1;
						m_avPath[2].col = -1;
						m_avPath[2].row = nRow2;
						return true;
					}

			if (LintY(anMap, nRow1 - 1, nRow2 + 1, i))
				if (LintX(anMap, nRow1, i, nCol1))
					if (LintX(anMap, nRow2, i, nCol2))
					{
						m_avPath[1].col = i;
						m_avPath[1].row = nRow1;
						m_avPath[2].col = i;
						m_avPath[2].row = nRow2;
						return true;
					}
		}

		for (int i = nCol2 + 1; i <= 4; i++)
		{
			if (i == 4)
				if (LintX(anMap, nRow1, nCol1, 4))
					if (LintX(anMap, nRow2, nCol2, 4))
					{
						m_avPath[1].col = 4;
						m_avPath[1].row = nRow1;
						m_avPath[2].col = 4;
						m_avPath[2].row = nRow2;
						return true;
					}

			if (LintY(anMap, nRow1 - 1, nRow2 + 1, i))
				if (LintX(anMap, nRow1, nCol1, i))
					if (LintX(anMap, nRow2, nCol2, i))
					{
						m_avPath[1].col = i;
						m_avPath[1].row = nRow1;
						m_avPath[2].col = i;
						m_avPath[2].row = nRow2;
						return true;
					}
		}
	}


	return false;
}

bool CGameLogic::LintY(int anMap[][4], int nRow1, int nRow2, int nCol)
{
	//判断(nRow1,nCol)到(nRow2,nCol)能否连通
	for (int nRow = nRow1 + 1; nRow <= nRow2; nRow++)
	{
		if (nRow == nRow2)
			return true;

		if (anMap[nRow][nCol] != BLANK)
			break;
	}
	return false;
}

bool CGameLogic::LintX(int anMap[][4], int nRow, int nCol1, int nCol2)
{
	//判断(nRow,nCol1)到(nRow,nCol2)能否连通
	for (int nCol = nCol1 + 1; nCol <= nCol2; nCol++)
	{
		if (nCol == nCol2)
			return true;

		if (anMap[nRow][nCol] != BLANK)
			break;
	}
	return false;
}
