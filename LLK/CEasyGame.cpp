#include "pch.h"
#include "CEasyGame.h"

void CEasyGame::StartGame()
{
	CGameLogic gamelogic;
	gamelogic.InitMap(m_graph);
}

BOOL CEasyGame::IsWin(int nTime)
{
	CGameLogic gamelogic;
	if (nTime <= 0)
	{
		//Çå³ýÍ¼
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

bool CEasyGame::Help(Vertex avPath[36], int& nVexnum)
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

bool CEasyGame::ResetGraph()
{

	CGameLogic logic;
	logic.ResetGraph(m_graph);
	return true;
}