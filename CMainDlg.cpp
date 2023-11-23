// CMainDlg.cpp: 实现文件
//

#include "pch.h"
#include "demo3.h"
#include "CMainDlg.h"
#include "afxdialogex.h"


// CMainDlg 对话框

IMPLEMENT_DYNAMIC(CMainDlg, CDialogEx)

void CMainDlg::resize()
{
}

CMainDlg::CMainDlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_DIALOG2, pParent)
{

}

CMainDlg::~CMainDlg()
{
}

void CMainDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

std::vector<double> CMainDlg::getNums(CString str)
{
	return std::vector<double>();
}


BEGIN_MESSAGE_MAP(CMainDlg, CDialogEx)
END_MESSAGE_MAP()


// CMainDlg 消息处理程序
