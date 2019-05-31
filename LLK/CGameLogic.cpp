#include "afxdialogex.h"
#include "pch.h"
#include "CGameLogic.h"


void CGameLogic::InitMap(int anMap[][4])
{
	//��Ϸ��ͼ��ʼ�����̶���ֵ
	int anTemp[4][4] = { 2,0,1,3,2,2,1,3,2,1,0,0,1,3,0,3 };
	for (int i = 0; i < 4; i++)
		for (int j = 0; j < 4; j++)
			anMap[i][j] = anTemp[i][j];
}


bool CGameLogic::IsLink(int anMap[][4], Vertex v1, Vertex v2)
{
	//һ��ֱ����ͨ
	int nRow1 = v1.row;
	int nCol1 = v1.col;
	int nRow2 = v2.row;
	int nCol2 = v2.col;
	//�к���ͬʱ�Ƿ���ͨ
	if (nRow1 == nRow2)
	{
		if (LinkInRow(anMap, v1, v2))
			return true;
	}
	//�к���ͬʱ�Ƿ���ͨ
	if (nCol1 == nCol2)
	{
		if (LinkInCol(anMap, v1, v2))
			return true;
	}


	//����ֱ����ͨ
	if (OneCornerLink(anMap, v1, v2))
		return true;

	//����ֱ����ͨ
	if (TwoCornerLink(anMap, v1, v2))
		return true;

	return false;
}


void CGameLogic::Clear(int anMap[][4], Vertex v1, Vertex v2)
{
	anMap[v1.row][v1.col] = BLANK;
	anMap[v2.row][v2.col] = BLANK;


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
	int nRow = v1.row;
	int nCol1 = v1.col;
	int nCol2 = v2.col;

	//��֤nCol1С��nCol2
	if (nCol1 > nCol2)
	{
		int nTemp = nCol1;
		nCol1 = nCol2;
		nCol2 = nTemp;
	}

	//ֱͨ
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

	//��֤nRow1С��nRow2
	if (nRow1 > nRow2)
	{
		int nTemp = nRow1;
		nRow1 = nRow2;
		nRow2 = nTemp;
	}
	 
	//ֱͨ
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
				return true;
			else
				k = false;
		else
			k = false;

		if (LintY(anMap, nRow1, nRow2, nCol1) && anMap[nRow2][nCol1] == BLANK)
			if (LintX(anMap, nRow2, nCol1, nCol2))
				return true;
			else return false;
		return false;
	}
	else {
		if (LintY(anMap, nRow1, nRow2, nCol1) && anMap[nRow2][nCol1] == BLANK)
			if (LintX(anMap, nRow2, nCol2, nCol1))
				return true;
			else
				k = false;
		else
			k = false;

		if (LintX(anMap, nRow1, nCol2, nCol1) && anMap[nRow1][nCol2] == BLANK)
			if (LintY(anMap, nRow1, nRow2, nCol2))
				return true;
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
						return true;

		for (int i = nCol1 + 1; i < nCol2; i++)
			if (LintY(anMap, nRow1 - 1, nRow2 + 1, i))
				if (LintX(anMap, nRow1, nCol1, i))
					if (LintY(anMap, nRow2, i, nCol2))
						return true;

		for (int i = nRow1 - 1; i >= -1; i--)
		{
			if (i == -1)
				if (LintY(anMap, -1, nRow1, nCol1))
					if (LintY(anMap, -1, nRow2, nCol2))
						return true;

			if (LintX(anMap, i, nCol1 - 1, nCol2 + 1))
				if (LintY(anMap, i, nRow1, nCol1))
					if (LintY(anMap, i, nRow2, nCol2))
						return true;
		}

		for (int i = nRow2 + 1; i <= 4; i++)
		{
			if (i == 4)
				if (LintY(anMap, nRow1, 4, nCol1))
					if (LintY(anMap, nRow2, 4, nCol2))
						return true;

			if (LintX(anMap, i, nCol1 - 1, nCol2 + 1))
				if (LintY(anMap, nRow1, i, nCol1))
					if (LintY(anMap, nRow2, i, nCol2))
						return true;
		}

		for (int i = nCol1 - 1; i >= -1; i--)
		{
			if (i == -1)
				if (LintX(anMap, nRow1, -1, nCol1))
					if (LintX(anMap, nRow2, -1, nCol2))
						return true;

			if (LintY(anMap, nRow1 - 1, nRow2 + 1, i))
				if (LintX(anMap, nRow1, i, nCol1))
					if (LintX(anMap, nRow2, i, nCol2))
						return true;
		}

		for (int i = nCol2 + 1; i <= 4; i++)
		{
			if (i == 4)
				if (LintX(anMap, nRow1, nCol1, 4))
					if (LintX(anMap, nRow2, nCol2, 4))
						return true;

			if (LintY(anMap, nRow1 - 1, nRow2 + 1, i))
				if (LintX(anMap, nRow1, nCol1, i))
					if (LintX(anMap, nRow2, nCol2, i))
						return true;
		}
	}
	else
	{
		for (int i = nRow1 + 1; i < nRow2; i++)
			if (LintX(anMap, i, nCol2 - 1, nCol1 + 1))
				if (LintY(anMap, nRow1, i, nCol1))
					if (LintY(anMap, i, nRow2, nCol2))
						return true;

		for (int i = nCol2 + 1; i < nCol1; i++)
			if (LintY(anMap, nRow1 - 1, nRow2 + 1, i))
				if (LintX(anMap, nRow2, nCol2, i))
					if (LintY(anMap, nRow1, i, nCol1))
						return true;

		for (int i = nRow1 - 1; i >= -1; i--)
		{
			if (i == -1)
				if (LintY(anMap, -1, nRow1, nCol1))
					if (LintY(anMap, -1, nRow2, nCol2))
						return true;

			if (LintX(anMap, i, nCol2 - 1, nCol1 + 1))
				if (LintY(anMap, i, nRow1, nCol1))
					if (LintY(anMap, i, nRow2, nCol2))
						return true;

		}

		for (int i = nRow2 + 1; i <= 4; i++)
		{
			if (i == 4)
				if (LintY(anMap, nRow1, 4, nCol1))
					if (LintY(anMap, nRow2, 4, nCol2))
						return true;

			if (LintX(anMap, i, nCol2 - 1, nCol1 + 1))
				if (LintY(anMap, nRow1, i, nCol1))
					if (LintY(anMap, nRow2, i, nCol2))
						return true;
		}

		for (int i = nCol2 - 1; i >= -1; i--)
		{
			if (i == -1)
				if (LintX(anMap, nRow1, -1, nCol1))
					if (LintX(anMap, nRow2, -1, nCol2))
						return true;

			if (LintY(anMap, nRow1 - 1, nRow2 + 1, i))
				if (LintX(anMap, nRow1, i, nCol1))
					if (LintX(anMap, nRow2, i, nCol2))
						return true;
		}

		for (int i = nCol2 + 1; i <= 4; i++)
		{
			if (i == 4)
				if (LintX(anMap, nRow1, nCol1, 4))
					if (LintX(anMap, nRow2, nCol2, 4))
						return true;

			if (LintY(anMap, nRow1 - 1, nRow2 + 1, i))
				if (LintX(anMap, nRow1, nCol1, i))
					if (LintX(anMap, nRow2, nCol2, i))
						return true;
		}
	}


	return false;
}

bool CGameLogic::LintY(int anMap[][4], int nRow1, int nRow2, int nCol)
{
	//�ж�(nRow1,nCol)��(nRow2,nCol)�ܷ���ͨ
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
	//�ж�(nRow,nCol1)��(nRow,nCol2)�ܷ���ͨ
	for (int nCol = nCol1 + 1; nCol <= nCol2; nCol++)
	{
		if (nCol == nCol2)
			return true;

		if (anMap[nRow][nCol] != BLANK)
			break;
	}
	return false;
}
