#pragma once

#include "global.h"
#include "CGameControl.h"
#include "CGraph.h"

class CGameLogic
{
protected:
	Vertex m_avPath[4];		//�����ڽ��������ж�ʱ�������Ķ���
	int m_VexNum;			//������

public: 
	CGameLogic();
	void InitMap(CGraph& graph);
	bool IsLink(CGraph& graph, Vertex v1, Vertex v2);		//�ж�����ͼƬ�Ƿ������
	void Clear(CGraph& graph, Vertex v1, Vertex v2);		//���������򽫶���ֵ��Ϊ��
	int GetVexPath(Vertex avPath[4]);		//��ȡ�õ�·��avPath[4]����ͨ���������ظ����ú�����ͨ������ֵ���ض�����

protected:
	void PushVertex();		//���һ��·������
	void PopVertex();		//ȡ��һ������
	//bool LinkInRow(int anMap[][4], Vertex v1, Vertex v2);		//�жϺ����Ƿ���ͨ
	//bool LinkInCol(int anMap[][4], Vertex v1, Vertex v2);		//�ж������Ƿ���ͨ
	bool OneCornerLink(int anMap[][4], Vertex v1, Vertex v2);		//һ���յ���ͨ�ж�
	bool TwoCornerLink(int anMap[][4], Vertex v1, Vertex v2);		//�����յ���ͨ�ж�
	//bool LintY(int anMap[][4], int nRow1, int nRow2, int nCol);		//ֱ����ͨY��
	//bool LintX(int anMap[][4], int nRow, int nCol1, int nCol2);		//ֱ����ͨX��

};
