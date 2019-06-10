#pragma once
#include "global.h"

class CGraph
{
public:
	CGraph(void);
	~CGraph(void);

#define MAX_VERTEX_NUM 36
	typedef int Vertices[MAX_VERTEX_NUM];
	typedef bool AdjMatrix[MAX_VERTEX_NUM][MAX_VERTEX_NUM];
	void InitGraph();
	void AddVertex(Vertex v);					//���ö��������Ӧλ�õ�Ԫ����Ϣ
	int GetVertex(int nIndex);					//���ض���Ԫ����Ϣ
	void AddArc(int nV1Index, int nV2Index);		//��v1��v2֮�����ӣ����ñ߹�ϵ������Ӧλ��Ϊtrue
	int Vexnum();
	void UpdateVertex(int nIndex, int nInfo);
	bool GetArc(int nV1Index, int nV2Index);		
	void ClearGraph();

protected:
	Vertices m_Vertices;
	AdjMatrix m_AdjMatrix;
	int m_nVexnum;
	int m_nArcnum;

};

