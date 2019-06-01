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


	m_sizeElem.cx = 40;
	m_sizeElem.cy = 40;

	m_ptGameTop.x = 50;
	m_ptGameTop.y = 50;

	m_bFirstPoint = true;

	//初始化游戏更新区域
	m_rtGameRect.top = m_ptGameTop.y - 50;
	m_rtGameRect.left = m_ptGameTop.x - 50;
	m_rtGameRect.right = m_rtGameRect.left + m_sizeElem.cx * 5 + 50;
	m_rtGameRect.bottom = m_rtGameRect.top + m_sizeElem.cy * 5 + 50;
}

CGameDlg::~CGameDlg()
{
}

void CGameDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(CGameDlg, CDialogEx)
	ON_WM_PAINT()
	ON_BN_CLICKED(IDC_BTN_BEGIN, &CGameDlg::OnClickedBtnBegin)
	ON_WM_LBUTTONUP()
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

	UpdateMap();

	Invalidate(FALSE);
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
	for (int i = 0; i < 4; i++)
		for (int j = 0; j < 4; j++)
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
	if (nRow > 3 || nCol > 3)
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
		Vertex avPath[4];
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
