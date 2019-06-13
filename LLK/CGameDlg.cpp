// CGameDlg.cpp: 实现文件
//

#include "pch.h"
#include "LLK.h"
#include "CGameDlg.h"
#include "afxdialogex.h"


// CGameDlg 对话框

IMPLEMENT_DYNAMIC(CGameDlg, CDialogEx)

CGameDlg::CGameDlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_GAME_DIALOG, pParent)
{
	//加载系统图标
	m_hIcon = AfxGetApp()->LoadIconW(IDR_MAINFRAME);


	m_sizeElem.cx = PIC_WIDTH;
	m_sizeElem.cy = PIC_HEIGHT;

	m_ptGameTop.x = MAP_LETF;
	m_ptGameTop.y = MAP_TOP;

	m_bFirstPoint = true;
	m_bPlaying = false;

	//初始化游戏更新区域
	m_rtGameRect.top = m_ptGameTop.y;
	m_rtGameRect.left = m_ptGameTop.x;
	m_rtGameRect.right = m_rtGameRect.left + m_sizeElem.cx * MAX_COL + 100;
	m_rtGameRect.bottom = m_rtGameRect.top + m_sizeElem.cy * MAX_ROW + 100;
}

CGameDlg::~CGameDlg()
{
}

void CGameDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_GAME_TIME, m_GameProcess);
}


BEGIN_MESSAGE_MAP(CGameDlg, CDialogEx)
	ON_WM_PAINT()
	ON_BN_CLICKED(IDC_BTN_BEGIN, &CGameDlg::OnClickedBtnBegin)
	ON_WM_LBUTTONUP()
	ON_BN_CLICKED(IDC_BTN_TIP, &CGameDlg::OnClickedBtnTip)
	ON_BN_CLICKED(IDC_BTN_RESET, &CGameDlg::OnClickedBtnReset)
	ON_BN_CLICKED(IDC_BTN_PAUSE, &CGameDlg::OnClickedBtnPause)
	ON_WM_TIMER()
	//ON_EN_CHANGE(IDC_LEFT_TIME, &CGameDlg::OnEnChangeLeftTime)
END_MESSAGE_MAP()


// CGameDlg 消息处理程序


void CGameDlg::InitBackground()
{
	// 获得当前对话框的视频内容
	CClientDC dc(this);

	//加载BMP图片资源
	HANDLE hBmpBG = ::LoadImage(NULL, _T("theme\\pictures\\bg.bmp"), IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE);

	//创建与视频内存兼容的内存DC
	m_dcBG.CreateCompatibleDC(&dc);

	//将位图资源进入DC
	m_dcBG.SelectObject(hBmpBG);

	//初始化内存DC
	m_dcMem.CreateCompatibleDC(&dc);
	CBitmap bmpMem;
	bmpMem.CreateCompatibleBitmap(&dc, 800, 600);
	m_dcMem.SelectObject(&bmpMem);

	//绘制背景到内存DC中
	m_dcMem.BitBlt(0, 0, 800, 600, &m_dcBG, 0, 0, SRCCOPY);

	UpdateWindow();

}

void CGameDlg::DrawGameTime()
{
	CPaintDC dc(this);

	//创建字体
	int time = m_GameProcess.GetPos();

	CString strText;
	strText.Format(_T("%d"), time);
	SetDlgItemText(IDC_LEFT_TIME, strText);
	//dc.SelectObject(oldFont);
}


BOOL CGameDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();


	// TODO:  在此添加额外的初始化

	InitBackground();
	InitElement();

	return TRUE;  // return TRUE unless you set the focus to a control
				  // 异常: OCX 属性页应返回 FALSE
}


void CGameDlg::OnPaint()
{
	CPaintDC dc(this); // device context for painting
					   // TODO: 在此处添加消息处理程序代码
					   // 不为绘图消息调用 CDialogEx::OnPaint()
	dc.BitBlt(0, 0, 800, 600, &m_dcMem, 0, 0, SRCCOPY);

}

void CGameDlg::InitElement()
{
	CClientDC dc(this);

	HANDLE hBmpBG = ::LoadImage(NULL, _T("theme\\pictures\\fruit_element.bmp"), IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE);

	m_dcElement.CreateCompatibleDC(&dc);
	m_dcElement.SelectObject(hBmpBG); 

	HANDLE hMask = ::LoadImage(NULL, _T("theme\\pictures\\fruit_mask.bmp"), IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE);

	m_dcMask.CreateCompatibleDC(&dc);
	m_dcMask.SelectObject(hMask);
}




void CGameDlg::OnClickedBtnBegin()
{
	// 初始化游戏地图
	gamecontrol.StartGame();
	m_bPlaying = true;
	this->GetDlgItem(IDC_BTN_BEGIN)->EnableWindow(FALSE);

	//更新窗口
	UpdateMap();

	//游戏表示设为true
	m_bPlaying = true;
	//初始化进度条
	this->GetDlgItem(IDC_GAME_TIME)->ShowWindow(TRUE);
	this->GetDlgItem(IDC_LEFT_TIME)->ShowWindow(TRUE);
	m_GameProcess.SetRange(0, 60 * 5);
	m_GameProcess.SetStep(-1);
	m_GameProcess.SetPos(60 * 5);
	//启动定时器
	this->SetTimer(PLAY_TIMER_ID, 1000, NULL);


	//更新窗口
	InvalidateRect(m_rtGameRect, FALSE);
}


void CGameDlg::UpdateMap()
{
	// TODO: 在此处添加实现代码.
	int nLeft = m_ptGameTop.x;
	int nTop = m_ptGameTop.y;
	int nElemW = m_sizeElem.cx;
	int nElemH = m_sizeElem.cy;
	
	m_dcMem.BitBlt(m_rtGameRect.left, m_rtGameRect.top,
		m_rtGameRect.Width(), m_rtGameRect.Height(), &m_dcBG, m_rtGameRect.left, m_rtGameRect.top, SRCCOPY);
	for (int i = 1; i < MAX_ROW; i++)
		for (int j = 1; j < MAX_COL; j++)
		{
			int nInfo = gamecontrol.GetElement(i, j);
			//将背景与掩码相或，边保留，图像区域为1
			m_dcMem.BitBlt(nLeft + j * nElemW, nTop + i * nElemH, nElemW, nElemH, &m_dcMask, 0, nInfo * nElemH, SRCPAINT);

			//和元素图片想与，边保留，图像区域为元素图片
			m_dcMem.BitBlt(nLeft + j * nElemW, nTop + i * nElemH, nElemW, nElemH, &m_dcElement, 0, nInfo * nElemH, SRCAND);
		}
}


void CGameDlg::UpdateWindow()
{
	// TODO: 在此处添加实现代码.
	CRect rtWin;
	CRect rtCilent;
	this->GetWindowRect(rtWin);
	this->GetClientRect(rtCilent);

	int nSpanWidth = rtWin.Width() - rtCilent.Width();
	int nSpanHeight = rtWin.Height() - rtCilent.Height();

	MoveWindow(0, 0, 800 + nSpanWidth, 600 + nSpanHeight);

	CenterWindow();
}


void CGameDlg::OnLButtonUp(UINT nFlags, CPoint point)
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值
	if ((point.x < m_ptGameTop.x) || (point.y < m_ptGameTop.y))
		return CDialogEx::OnLButtonUp(nFlags, point);

	int nRow = (point.y - m_ptGameTop.y) / m_sizeElem.cy;
	int nCol = (point.x - m_ptGameTop.x) / m_sizeElem.cx;
	if (nRow > MAX_ROW - 1 || nCol > MAX_COL - 1)
	{
		return CDialogEx::OnLButtonUp(nFlags, point);
	}


	if (m_bFirstPoint)
	{
		DrawTipFrame(nRow, nCol);

		gamecontrol.SetFirstPoint(nRow, nCol);
	}
	else
	{
		Vertex avPath[MAX_VERTEX_NUM];
		gamecontrol.GetFirstPoint(avPath[0]);

		DrawTipFrame(nRow, nCol);

		avPath[1].row = nRow;
		avPath[1].col = nCol;
		gamecontrol.SetSecPoint(nRow, nCol);

		//判断是否是相同图片
		int nVexnum = 0;
		if (gamecontrol.Link(avPath, nVexnum))
		{
			DrawTipLine(avPath, nVexnum);
			UpdateMap();
		}

		Sleep(200);
		InvalidateRect(m_rtGameRect, FALSE);
	}

	m_bFirstPoint = !m_bFirstPoint;

	JudgeWin();

	//CDialogEx::OnLButtonUp(nFlags, point);
}


void CGameDlg::DrawTipFrame(int nRow, int nCol)
{
	// TODO: 在此处添加实现代码.
	CClientDC dc(this);
	CBrush brush(RGB(233, 43, 43));
	CRect rtTipFrame;
	rtTipFrame.left = m_ptGameTop.x + nCol * m_sizeElem.cx;
	rtTipFrame.top = m_ptGameTop.y + nRow * m_sizeElem.cy;
	rtTipFrame.right = rtTipFrame.left + m_sizeElem.cx;
	rtTipFrame.bottom = rtTipFrame.top + m_sizeElem.cy;
	dc.FrameRect(rtTipFrame, &brush);
}



void CGameDlg::DrawTipLine(Vertex avPath[], int nVexnum)
{
	// TODO: 在此处添加实现代码.
	CClientDC dc(this);

	CPen penLine(PS_SOLID, 2, RGB(0, 255, 0));
	CPen* pOldPen = dc.SelectObject(&penLine);

	for (int i = 0; i < nVexnum - 1; i++)
	{
		dc.MoveTo(m_ptGameTop.x + avPath[i].col * m_sizeElem.cx + m_sizeElem.cx / 2,
			m_ptGameTop.y + avPath[i].row * m_sizeElem.cy + m_sizeElem.cy / 2);
		dc.LineTo(m_ptGameTop.x + avPath[i + 1].col * m_sizeElem.cx + m_sizeElem.cx / 2,
			m_ptGameTop.y + avPath[i + 1].row * m_sizeElem.cy + m_sizeElem.cy / 2);
	}

	dc.SelectObject(pOldPen);
}

void CGameDlg::JudgeWin()
{
	BOOL bGameStatus = gamecontrol.IsWin(m_GameProcess.GetPos());

	if (bGameStatus == GAME_PLAY)
		return;
	else
	{
		m_bPlaying = false;
		KillTimer(PLAY_TIMER_ID);
		CString strTitle;
		this->GetWindowTextW(strTitle);
		if (bGameStatus == GAME_SUCCESS)
		{
			MessageBox(_T("恭喜获胜"), strTitle);
		}
		else
		{
			MessageBox(_T("很遗憾，时间到了!"), strTitle);
		}
		this->GetDlgItem(IDC_BTN_BEGIN)->EnableWindow(TRUE);
		this->GetDlgItem(IDC_GAME_TIME)->ShowWindow(FALSE);
		this->GetDlgItem(IDC_LEFT_TIME)->ShowWindow(FALSE);
	}
}



void CGameDlg::OnClickedBtnTip()
{
	// TODO: 在此添加控件通知处理程序代码
	Vertex avPath[MAX_VERTEX_NUM];
	int nVexnum = 0;
	if (gamecontrol.Help(avPath, nVexnum))
	{
		DrawTipLine(avPath, nVexnum);
		UpdateMap();
	}
	JudgeWin();
	Sleep(200);
	InvalidateRect(m_rtGameRect, FALSE);
}


void CGameDlg::OnClickedBtnReset()
{
	if (gamecontrol.ResetGraph())
	{
		UpdateMap();
	}
	Sleep(200);
	InvalidateRect(m_rtGameRect, FALSE);
	// TODO: 在此添加控件通知处理程序代码
}


void CGameDlg::OnClickedBtnPause()
{
	// TODO: 在此添加控件通知处理程序代码
	if (!m_bPlaying)
		return;
	if (!m_bPause)
	{
		m_bPause = true;
		this->GetDlgItem(IDC_BTN_PAUSE)->SetWindowTextW(_T("继续"));
		
		CClientDC dc(this);

		//加载BMP图片资源
		HANDLE hBmpBG = ::LoadImage(NULL, _T("theme\\pictures\\bg.bmp"), IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE);

		//创建与视频内存兼容的内存DC
		m_dcCache.CreateCompatibleDC(&dc);

		//将位图资源进入DC
		m_dcCache.SelectObject(hBmpBG);

		m_dcMem.BitBlt(0, 0, 800, 600, &m_dcBG, 0, 0, SRCCOPY);

		InvalidateRect(m_rtGameRect, false);
	}
	else
	{
		m_bPause = false;
		this->GetDlgItem(IDC_BTN_PAUSE)->SetWindowTextW(_T("暂停"));
		UpdateMap();
		InvalidateRect(m_rtGameRect, FALSE);
	}
}


void CGameDlg::OnTimer(UINT_PTR nIDEvent)
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值
	if (nIDEvent == PLAY_TIMER_ID && m_bPlaying && !m_bPause)
	{
		//游戏时间减少一秒
		
		m_GameProcess.StepIt();
		int time = m_GameProcess.GetPos();
		DrawGameTime();
	}
	CDialogEx::OnTimer(nIDEvent);
}



void CGameDlg::OnEnChangeLeftTime()
{
	// TODO:  如果该控件是 RICHEDIT 控件，它将不
	// 发送此通知，除非重写 CDialogEx::OnInitDialog()
	// 函数并调用 CRichEditCtrl().SetEventMask()，
	// 同时将 ENM_CHANGE 标志“或”运算到掩码中。

	// TODO:  在此添加控件通知处理程序代码
}
