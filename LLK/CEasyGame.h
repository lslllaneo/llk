#pragma once
#include "CGameControl.h"

class CEasyGame :
	public CGameControl
{
	void StartGame();
	BOOL IsWin(int nTime);
	bool Help(Vertex avPath[36], int& nVexnum);
	bool ResetGraph();
};

