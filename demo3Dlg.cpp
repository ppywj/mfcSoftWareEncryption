
// demo3Dlg.cpp: 实现文件
//

#include "pch.h"
#include "framework.h"
#include "demo3.h"
#include "demo3Dlg.h"
#include "afxdialogex.h"
#include<iterator>
#include<sstream>
#include<iostream>
#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// 用于应用程序“关于”菜单项的 CAboutDlg 对话框

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_ABOUTBOX };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

// 实现
protected:
	DECLARE_MESSAGE_MAP()
public:
//	afx_msg void OnSize(UINT nType, int cx, int cy);
//	afx_msg void OnSize(UINT nType, int cx, int cy);
	afx_msg void OnNMClickList2(NMHDR* pNMHDR, LRESULT* pResult);
};

CAboutDlg::CAboutDlg() : CDialogEx(IDD_ABOUTBOX)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialogEx)
//	ON_WM_SIZE()
ON_WM_SIZE()
END_MESSAGE_MAP()


// Cdemo3Dlg 对话框



Cdemo3Dlg::Cdemo3Dlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_DEMO3_DIALOG, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void Cdemo3Dlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_LIST2, m_listCtrl);
}

std::vector<double> Cdemo3Dlg::getNums(CString str)
{
	std::string cString = std::string(str.GetString());
	std::stringstream ss(cString);
	double number;
	std::vector<double> vec;
	while (ss >> number) {
		vec.push_back(number);
		// 忽略掉\r\n
		ss.ignore(2, '\n');
	}
	return vec;
}



BEGIN_MESSAGE_MAP(Cdemo3Dlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_EN_CHANGE(IDC_EDIT4, &Cdemo3Dlg::OnEnChangeEdit4)
	ON_NOTIFY(NM_CLICK, IDC_LIST2, &Cdemo3Dlg::OnNMClickList2)
	ON_BN_CLICKED(IDC_BUTTON1, &Cdemo3Dlg::OnBnClickedButton1)
	ON_WM_SIZE()
END_MESSAGE_MAP()


// Cdemo3Dlg 消息处理程序

BOOL Cdemo3Dlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// 将“关于...”菜单项添加到系统菜单中。

	// IDM_ABOUTBOX 必须在系统命令范围内。
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	ShowWindow(SW_MAXIMIZE);//窗口默认显示最大///////////////////////////////////////////////////////////////

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != nullptr)
	{
		BOOL bNameValid;
		CString strAboutMenu;
		bNameValid = strAboutMenu.LoadString(IDS_ABOUTBOX);
		ASSERT(bNameValid);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}

	// 设置此对话框的图标。  当应用程序主窗口不是对话框时，框架将自动
	//  执行此操作
	SetIcon(m_hIcon, TRUE);			// 设置大图标
	SetIcon(m_hIcon, FALSE);		// 设置小图标


	m_listCtrl.SetBkColor(RGB(255, 255, 255));  // 设置背景颜色为白色
	m_listCtrl.SetTextBkColor(RGB(255, 255, 255));  // 设置文本背景颜色为白色
	m_listCtrl.SetExtendedStyle(m_listCtrl.GetExtendedStyle() | LVS_EX_GRIDLINES);  // 显示网格线

	// 自定义绘制
	m_listCtrl.SetExtendedStyle(m_listCtrl.GetExtendedStyle() | LVS_OWNERDRAWFIXED);

	// 添加虚拟列表风格
	m_listCtrl.SetExtendedStyle(m_listCtrl.GetExtendedStyle() | LVS_OWNERDATA);
	m_listCtrl.SetIconSpacing(CSize(50,50));


	// 创建自定义字体
	CFont font;
	LOGFONT lf;
	memset(&lf, 0, sizeof(LOGFONT));
	lf.lfHeight = -MulDiv(30, GetDeviceCaps(GetDC()->m_hDC, LOGPIXELSY), 72); // 设置字体高度为30像素
	_tcscpy_s(lf.lfFaceName, LF_FACESIZE, _T("Arial")); // 设置字体名称
	font.CreateFontIndirect(&lf);

	// 设置字体
	m_listCtrl.SetFont(&font);

	// 设置列表控件样式
	m_listCtrl.ModifyStyle(0, LVS_REPORT); // 设置为报表风格
	m_listCtrl.DeleteAllItems(); // 删除所有项，准备重新插入

	// 设置列表控件的列数为1
	m_listCtrl.DeleteColumn(0); // 先删除已有的列
	m_listCtrl.InsertColumn(0, _T("Buttons"), LVCFMT_LEFT, 200); // 插入一列

	const int itemCount = 12;
	for (int i = 0; i < itemCount; ++i)
	{
		CString itemText;
		itemText.Format(_T("Button%d"), i + 1);

		// 插入新的列表项
		int itemIndex = m_listCtrl.InsertItem(i, itemText);
	}

	// 调整列表控件的大小
	CRect listRect;
	m_listCtrl.GetClientRect(&listRect);
	m_listCtrl.SetColumnWidth(0, listRect.Width()); // 设置列宽与控件宽度一致
	m_listCtrl.SetWindowPos(NULL, 0, 0, listRect.Width(), listRect.Height(), SWP_NOMOVE | SWP_NOZORDER); // 设置控件大小
	// 启用垂直滚动条和网格线
	m_listCtrl.SetExtendedStyle(m_listCtrl.GetExtendedStyle() | LVS_EX_FULLROWSELECT | LVS_EX_GRIDLINES | LVS_EX_DOUBLEBUFFER | LVS_EX_HEADERDRAGDROP | LVS_EX_UNDERLINEHOT);

	CRect rc;
	m_listCtrl.GetClientRect(&rc);

	CPaintDC dc(&m_listCtrl);
	CBrush brush;
	brush.CreateStockObject(BLACK_BRUSH);
	CPen pen(PS_SOLID, 1, RGB(0, 0, 0));
	CPen* pOldPen = dc.SelectObject(&pen);
	CBrush* pOldBrush = dc.SelectObject(&brush);

	int nColumnCount = m_listCtrl.GetHeaderCtrl()->GetItemCount();
	for (int i = 1; i < nColumnCount; i++)
	{
		int xPos = m_listCtrl.GetHeaderCtrl()->GetItemRect(i, &rc);
		dc.MoveTo(xPos, rc.top);
		dc.LineTo(xPos, rc.bottom);
	}

	dc.SelectObject(pOldPen);
	dc.SelectObject(pOldBrush);

	CRect m_windowedRect;
	GetClientRect(&m_windowedRect);
	m_nOldCx = m_windowedRect.Width();
	m_nOldCy = m_windowedRect.Height();
	// 初始化完毕flag
	m_IsInitialized = TRUE;

	return TRUE;  // 除非将焦点设置到控件，否则返回 TRUE
}

void Cdemo3Dlg::ReSize(int cx, int cy)
{
	//计算窗口比率
	float fspx = (float)cx / m_nOldCx;
	float fspy = (float)cy / m_nOldCy;

	CRect rect;

	//获取子窗口（控件）
	CWnd* pWnd = this->GetWindow(GW_CHILD);
	while (pWnd != NULL)
	{
		pWnd->GetWindowRect(&rect);
		this->ScreenToClient(&rect);
		//重新计算控件位置和大小
		int nNewx = (int)(rect.left * fspx);
		int nNewy = (int)(rect.top * fspy);
		int nNewWidth = (int)(rect.Width() * fspx);
		int nNewHeight = (int)(rect.Height() * fspy);
		//调整控件
		pWnd->MoveWindow(nNewx, nNewy, nNewWidth, nNewHeight);

		//获取下一个子窗口（控件）
		pWnd = pWnd->GetWindow(GW_HWNDNEXT);
	}


}



void Cdemo3Dlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialogEx::OnSysCommand(nID, lParam);
	}
}

// 如果向对话框添加最小化按钮，则需要下面的代码
//  来绘制该图标。  对于使用文档/视图模型的 MFC 应用程序，
//  这将由框架自动完成。

void Cdemo3Dlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // 用于绘制的设备上下文

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// 使图标在工作区矩形中居中
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// 绘制图标
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}
}

//当用户拖动最小化窗口时系统调用此函数取得光标
//显示。
HCURSOR Cdemo3Dlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}








void Cdemo3Dlg::OnEnChangeEdit4()
{
	// TODO:  如果该控件是 RICHEDIT 控件，它将不
	// 发送此通知，除非重写 CDialogEx::OnInitDialog()
	// 函数并调用 CRichEditCtrl().SetEventMask()，
	// 同时将 ENM_CHANGE 标志“或”运算到掩码中。

	// TODO:  在此添加控件通知处理程序代码
}





void Cdemo3Dlg::OnNMClickList2(NMHDR* pNMHDR, LRESULT* pResult)
{
	LPNMITEMACTIVATE pNMItemActivate = reinterpret_cast<LPNMITEMACTIVATE>(pNMHDR);
	// 获取点击的项的文本
	CString selectedItemText;
	int selectedRow = pNMItemActivate->iItem;
	if (selectedRow >= 0)
	{
		selectedItemText = m_listCtrl.GetItemText(selectedRow, 0);
		// 使用 selectedItemText 进行你需要的操作
	}
	if (selectedItemText == "Button1")
	{
		//你要做的处理
		AfxMessageBox("点击了button1");
	}

	*pResult = 0;
}


void Cdemo3Dlg::OnBnClickedButton1()
{
	CString str;
	GetDlgItemText(IDC_EDIT4, str);
	std::vector<double>vec = getNums(str);
	
}


void Cdemo3Dlg::OnSize(UINT nType, int cx, int cy)
{
	CDialogEx::OnSize(nType, cx, cy);
	CWnd* pWnd;
	int id = 0;
	HWND  hwndChild = ::GetWindow(m_hWnd, GW_CHILD);
	if (!cx || !cy)
	{
		return;
	}
	else
	{
		while (hwndChild)
		{
			id = ::GetDlgCtrlID(hwndChild);//获得控件的ID
			pWnd = GetDlgItem(id); //获取ID为woc的空间的句柄			
			if (pWnd)
			{
				CRect rect;
				//获取当前控件大小
				pWnd->GetWindowRect(&rect);
				//将控件大小转换为在对话框中的区域坐标
				ScreenToClient(&rect);
				key = tar.find(id);
				end = tar.end();
				if (key == end)
				{
					vector<double> scale;
					scale.push_back((double)rect.left / m_rect.Width());//注意类型转换，不然保存成long型就直接为0了
					scale.push_back((double)rect.right / m_rect.Width());
					scale.push_back((double)rect.top / m_rect.Height());
					scale.push_back((double)rect.bottom / m_rect.Height());
					tar[id] = scale;
				}

				rect.left = tar[id][0] * cx;
				rect.right = tar[id][1] * cx;
				rect.top = tar[id][2] * cy;
				rect.bottom = tar[id][3] * cy;
				//设置控件大小
				pWnd->MoveWindow(rect);
			}
			hwndChild = ::GetWindow(hwndChild, GW_HWNDNEXT);
		}
		//将变化后的对话框大小设为旧大小
		GetClientRect(&m_rect);
	}

}
