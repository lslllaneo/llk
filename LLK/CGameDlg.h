﻿#pragma once

#include "global.h"
#include "CGameLogic.h"
#include "CGameControl.h"

// CGameDlg 对话框

class CGameDlg : public CDialogEx
{
	DECLARE_DYNAMIC(CGameDlg)

public:
	CGameDlg(CWnd* pParent = nullptr);   // 标准构造函数
	virtual ~CGameDlg();

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_GAME_DIALOG };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持
	void InitElement();
	HICON m_hIcon;
	CDC m_dcMem;
	CDC m_dcBG;
	CDC m_dcElement;
	CDC m_dcMask;


	CSize m_sizeElem;		//元素图片大小
	bool m_bFirstPoint;		//选中的图片是否第一次选中，true表示是，false表示不是


	CPoint m_ptGameTop;		//游戏区起始点
	CRect m_rtGameRect;		//游戏区域大小

	CGameControl gamecontrol;

	DECLARE_MESSAGE_MAP()
public:
	void InitBackground();


	virtual BOOL OnInitDialog();
	afx_msg void OnPaint();
	afx_msg void OnClickedBtnBegin();
	void UpdateMap();
	void UpdateWindow();
	afx_msg void OnLButtonUp(UINT nFlags, CPoint point);
protected:
	void DrawTipFrame(int nRow, int nCol);
	void DrawTipLine(Vertex avPath[], int nVexnum);
};
