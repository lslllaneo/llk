#pragma once

#include "CGameControl.h"

class CBasicGame : 
	public CGameControl
{
protected:


public:
	void StartGame(void);

	BOOL IsWin(int nTime);

	bool Help(Vertex avPath[36], int& nVexnum);

	bool ResetGraph();

};

