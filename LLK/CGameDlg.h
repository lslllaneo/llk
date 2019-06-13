#pragma once

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
	CDC m_dcCache;
	CDC m_dcPause;


	CSize m_sizeElem;		//元素图片大小
	bool m_bFirstPoint;		//选中的图片是否第一次选中，true表示是，false表示不是


	CPoint m_ptGameTop;		//游戏区起始点
	CRect m_rtGameRect;		//游戏区域大小

	CGameControl gamecontrol;
	bool m_bPlaying;		//表示是否正在游戏
	bool m_bPause;		//表示游戏是否暂停
	CProgressCtrl m_GameProcess;


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
	void JudgeWin();
	void DrawGameTime();		//绘制游戏时间

public:
	afx_msg void OnClickedBtnTip();
	afx_msg void OnClickedBtnReset();
	afx_msg void OnClickedBtnPause();
	afx_msg void OnTimer(UINT_PTR nIDEvent);
	afx_msg void OnEnChangeLeftTime();
};
