#pragma once

#include "global.h"
#include "CGraph.h"

class CGameLogic
{
protected:
	int m_anPath[36];						//������ͨ·���Ķ�������
	int m_nCorner;		//����·������m_anPath�еĹյ���
	int m_nVexnum;        

public: 
	CGameLogic();
	void InitMap(CGraph& graph);
	void UpdateArc(CGraph& graph, Vertex v);				//�ж�v�������ڶ����Ƿ��бߣ��б������
	bool IsLink(CGraph& graph, int nV1, int nV2);		//�ж�����ͼƬ�Ƿ������
	void Clear(CGraph& graph, Vertex v1, Vertex v2);		//���������򽫶���ֵ��Ϊ��
	int GetVexPath(Vertex avPath[MAX_VERTEX_NUM]);		//��ȡ�õ�·��avPath[4]����ͨ���������ظ����ú�����ͨ������ֵ���ض�����
	bool IsBlank(CGraph& g);
	bool SearchValidPath(CGraph& g);				//Ѱ�ҿ������ӵ�����
	void ResetGraph(CGraph& g);		//����

protected:
	void PushVertex(int n);		//���һ��·������,���ж���Ӻ��Ƿ��γ�һ���յ�
	void PopVertex();		//ȡ��һ������
	bool SearchPath(CGraph game, int nV1, int nV2);		//������������㷨�ж�v1��v2�Ƿ���ͨ
	bool IsExist(int v);		//�ж�����Ϊv�ĵ��Ƿ񱣴�����ͨ����m_avPath��
	bool IsCornor();		//�ж�·�������е������������Ƿ񹹳�һ���յ�
};
