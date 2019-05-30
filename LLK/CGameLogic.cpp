#include "afxdialogex.h"
#include "pch.h"
#include "CGameLogic.h"


void CGameLogic::InitMap(int anMap[][4])
{
	//游戏地图初始化，固定的值
	int anTemp[4][4] = { 2,0,1,3,2,2,1,3,2,1,0,0,1,3,0,3 };
	for (int i = 0; i < 4; i++)
		for (int j = 0; j < 4; j++)
			anMap[i][j] = anTemp[i][j];
}


bool CGameLogic::IsLink(int anMap[][4], Vertex v1, Vertex v2)
{
	int nRow1 = v1.row;
	int nCol1 = v1.col;
	int nRow2 = v2.row;
	int nCol2 = v2.col;
	if (anMap[nRow1][nCol1] == anMap[nRow2][nCol2])
	{
		return true;
	}

	return false;
}


void CGameLogic::Clear(int anMap[][4], Vertex v1, Vertex v2)
{
	int nRow1 = v1.row;
	int nCol1 = v1.col;
	int nRow2 = v2.row;
	int nCol2 = v2.col;
	anMap[nRow1][nCol1] = BLANK;
	anMap[nRow2][nCol2] = BLANK;


}

int CGameLogic::GetVexPath(Vertex avPath[4])
{
	return 0;
}

void CGameLogic::PushVertex()
{
}

void CGameLogic::PopVertex()
{
}

bool CGameLogic::LinkInRow(int anMap[][4], Vertex v1, Vertex v2)
{
	return false;
}

bool CGameLogic::LinkInCol(int anMap[][4], Vertex v1, Vertex v2)
{
	return false;
}

bool CGameLogic::OneCornerLink(int anMap[][4], Vertex v1, Vertex v2)
{
	return false;
}

bool CGameLogic::LintY(int anMap[][4], int nRow1, int nRow2, int nCol)
{
	return false;
}

bool CGameLogic::LintX(int anMap[][4], int nRow, int nCol1, int nCol2)
{
	return false;
}
